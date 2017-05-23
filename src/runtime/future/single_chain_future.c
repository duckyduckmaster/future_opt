#define _XOPEN_SOURCE 800
#include <ucontext.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <assert.h>
#include <pthread.h>
#include <pony.h>
#include <dtrace_encore.h>

#include "encore.h"
#include "future.h"
#include "../libponyrt/actor/messageq.h"
#include "../libponyrt/sched/scheduler.h"

#define perr(m)  // fprintf(stderr, "%s\n", m);

static inline void single_chain_future_gc_send_value(pony_ctx_t *ctx, single_chain_future_t *fut);
static inline void single_chain_future_gc_recv_value(pony_ctx_t *ctx, single_chain_future_t *fut);
static void single_chain_future_discharge_producer(pony_ctx_t **ctx, single_chain_future_t * fut);
static void single_chain_future_block_actor(pony_ctx_t **ctx, single_chain_future_t *fut);
static void single_chain_future_finalizer(single_chain_future_t *fut);

extern void encore_future_gc_acquireactor(pony_ctx_t* ctx, pony_actor_t* actor);
extern void encore_future_gc_acquireobject(pony_ctx_t* ctx, void* p,
    pony_type_t *t, int mutability);

typedef struct actor_entry actor_entry_t;

// Terminology:
// Producer -- the actor responsible for fulfilling a future
// Consumer -- an non-producer actor using a future

// ===============================================================
// Create, inspect and fulfil
// ===============================================================


static inline encore_arg_t run_closure(pony_ctx_t **ctx, closure_t *c, encore_arg_t value)
{
  return closure_call(ctx, c, (value_t[1]) { value });
}

static inline void single_chain_future_gc_trace_value(pony_ctx_t *ctx, single_chain_future_t *fut)
{
  assert(fut);
  if (fut->type == ENCORE_ACTIVE) {
    encore_trace_actor(ctx, fut->value.p);
  } else if (fut->type != ENCORE_PRIMITIVE) {
    encore_trace_object(ctx, fut->value.p, fut->type->trace);
  }
}

static void single_chain_future_finalizer(single_chain_future_t *fut)
{
  pony_ctx_t* cctx = pony_ctx();
  single_chain_future_gc_recv_value(cctx, fut);
  ENC_DTRACE2(FUTURE_DESTROY, (uintptr_t) cctx, (uintptr_t) fut);
}

static inline void single_chain_future_gc_send_value(pony_ctx_t *ctx, single_chain_future_t *fut)
{
  pony_gc_send(ctx);
  single_chain_future_gc_trace_value(ctx, fut);
  pony_send_done(ctx);
}

static inline void single_chain_future_gc_recv_value(pony_ctx_t *ctx, single_chain_future_t *fut)
{
  pony_gc_recv(ctx);
  single_chain_future_gc_trace_value(ctx, fut);
  // note the asymmetry with send
  ponyint_gc_handlestack(ctx);
}

/**

poly future methods

**/

single_chain_future_t *single_chain_future_mk(pony_ctx_t **ctx, pony_type_t *type)
{
  pony_ctx_t *cctx = *ctx;
  assert(cctx->current);

  single_chain_future_t *fut = pony_alloc_final(cctx, sizeof(single_chain_future_t),
          (void *)&single_chain_future_finalizer);
  *fut = (single_chain_future_t) { .type = type };

  fut->closure_queue = POOL_ALLOC(mpmcq_t);
  ponyint_mpmcq_init(fut->closure_queue);

  ENC_DTRACE3(FUTURE_CREATE, (uintptr_t) ctx, (uintptr_t) fut, (uintptr_t) type);
  return fut;
} 

void single_chain_future_fulfil(pony_ctx_t **ctx, single_chain_future_t *fut, encore_arg_t value) 
{
  assert(fut->fulfilled == false);
  ENC_DTRACE2(FUTURE_FULFIL_START, (uintptr_t) *ctx, (uintptr_t) fut);
  fut->value = value;

  void * popped_closure = ponyint_mpmcq_pop_bailout_immediate(fut->closure_queue);
  while (popped_closure != NULL) {
    value_t result = run_closure(ctx, (closure_t *)popped_closure, fut->value);
    fut->value = result;
    popped_closure = ponyint_mpmcq_pop_bailout_immediate(fut->closure_queue);
  }

  __atomic_store_n(&(fut->fulfilled), true, __ATOMIC_SEQ_CST);
  single_chain_future_gc_send_value(*ctx, fut);
  single_chain_future_discharge_producer(ctx, fut);

  ENC_DTRACE2(FUTURE_FULFIL_END, (uintptr_t) *ctx, (uintptr_t) fut);
}

encore_arg_t single_chain_future_get_actor(pony_ctx_t **ctx, single_chain_future_t *fut)
{
  if (!__atomic_load_n(&(fut->fulfilled), __ATOMIC_SEQ_CST)) {
    ENC_DTRACE2(FUTURE_BLOCK, (uintptr_t) *ctx, (uintptr_t) fut);
    single_chain_future_block_actor(ctx, fut);
    ENC_DTRACE2(FUTURE_UNBLOCK, (uintptr_t) *ctx, (uintptr_t) fut);
  }

  ENC_DTRACE2(FUTURE_GET, (uintptr_t) *ctx, (uintptr_t) fut);
  return fut->value;
}


single_chain_future_t *single_chain_future_chain_actor(pony_ctx_t **ctx, single_chain_future_t *fut,
        closure_t *c)
{
  ENC_DTRACE2(FUTURE_CHAINING, (uintptr_t) *ctx, (uintptr_t) fut );
  perr("future_chain_actor");

  // if future is fulfilled by P, check if P missed any closures added late.
  if (__atomic_load_n(&(fut->fulfilled), __ATOMIC_SEQ_CST)) {
    if (fut->closure_queue != NULL) {

      void * popped_closure = ponyint_mpmcq_pop_bailout_immediate(fut->closure_queue);
      while (popped_closure != NULL) {
        value_t result = run_closure(ctx, (closure_t *)popped_closure, fut->value);
        fut->value = result;
        popped_closure = ponyint_mpmcq_pop_bailout_immediate(fut->closure_queue);
      }
      ponyint_mpmcq_destroy(fut->closure_queue);
      fut->closure_queue = NULL;

    } 
    value_t result = run_closure(ctx, c, fut->value);
    fut->value = result;
    return fut;
  }


  ponyint_mpmcq_push(fut->closure_queue, (void *)c);
  return fut;
}


// Similar to `future_chain_actor` except that it returns void, avoiding the
// creation of a new future. This is used in the ParTs library and is an
// optimisation over the `future_chain_actor`.
void single_chain_future_register_callback(pony_ctx_t **ctx,
                              single_chain_future_t *fut,
                              closure_t *c)
{
  ENC_DTRACE2(FUTURE_REGISTER_CALLBACK, (uintptr_t) *ctx, (uintptr_t) fut);
  perr("future_chain_actor");

  if (__atomic_load_n(&(fut->fulfilled), __ATOMIC_SEQ_CST)) {
    if (fut->closure_queue != NULL) {

      void * popped_closure = ponyint_mpmcq_pop_bailout_immediate(fut->closure_queue);
      while (popped_closure != NULL) {
        value_t result = run_closure(ctx, (closure_t *)popped_closure, fut->value);
        fut->value = result;
        popped_closure = ponyint_mpmcq_pop_bailout_immediate(fut->closure_queue);
      }
      ponyint_mpmcq_destroy(fut->closure_queue);
      fut->closure_queue = NULL;

    } 
    value_t result = run_closure(ctx, c, fut->value);
    fut->value = result;
    return;
  }

  ponyint_mpmcq_push(fut->closure_queue, (void *)c);
  return;
}


static void single_chain_future_block_actor(pony_ctx_t **ctx, single_chain_future_t *fut)
{
  perr("future_block_actor");
  if (__atomic_load_n(&(fut->fulfilled), __ATOMIC_SEQ_CST)) {
    if (fut->closure_queue != NULL) {

      void * popped_closure = ponyint_mpmcq_pop_bailout_immediate(fut->closure_queue);
      while (popped_closure != NULL) {
        value_t result = run_closure(ctx, (closure_t *)popped_closure, fut->value);
        fut->value = result;
        popped_closure = ponyint_mpmcq_pop_bailout_immediate(fut->closure_queue);
      }
      ponyint_mpmcq_destroy(fut->closure_queue);
      fut->closure_queue = NULL;

    } 
    return;
  }

  pony_ctx_t* cctx = *ctx;
  pony_actor_t *a = cctx->current;
  pony_unschedule(cctx, a);
  encore_actor_t *actor = (encore_actor_t*) a;
  
  pony_actor_node_info_t * pony_node = POOL_ALLOC(pony_actor_node_info_t);
  pony_node->on_stack = &fut->on_stack;
  pony_node->scfut = fut;
  pony_node->fclass = SINGLE_CHAIN_FUTURE;
  pony_node->fulfilled = &fut->fulfilled;
  actor_block(ctx, actor, (void *)pony_node);          
}

void single_chain_future_discharge_producer(pony_ctx_t **ctx, single_chain_future_t *fut) {
  if (__sync_bool_compare_and_swap(&(fut->on_stack), true, false)) { 
     perr("Unblocking");
     actor_set_resume((encore_actor_t *)fut->actor);
     pony_schedule(*ctx, fut->actor);
  }   
}

void single_chain_future_discharge_consumer(pony_ctx_t **ctx, single_chain_future_t *fut) {
  if (__sync_bool_compare_and_swap(&(fut->on_stack), true, false)) { 

     if (fut->closure_queue != NULL) {

       void * popped_closure = ponyint_mpmcq_pop_bailout_immediate(fut->closure_queue);
       while (popped_closure != NULL) {
         value_t result = run_closure(ctx, (closure_t *)popped_closure, fut->value);
         fut->value = result;
         popped_closure = ponyint_mpmcq_pop_bailout_immediate(fut->closure_queue);
       }
       ponyint_mpmcq_destroy(fut->closure_queue);
       POOL_FREE(mpmcq_t, fut->closure_queue);
       fut->closure_queue = NULL;

     } 
     perr("Unblocking");
     actor_set_resume((encore_actor_t *)fut->actor);
     pony_schedule(*ctx, fut->actor);
  }
}


