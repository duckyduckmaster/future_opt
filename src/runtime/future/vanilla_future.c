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

/*
      The most minified future API possible in encore.

*/

static void vanilla_future_finalizer(vanilla_future_t *fut);
static inline void vanilla_future_gc_send_value(pony_ctx_t *ctx, vanilla_future_t *fut);
static inline void vanilla_future_gc_recv_value(pony_ctx_t *ctx, vanilla_future_t *fut);

static void vanilla_future_block_actor(pony_ctx_t **ctx, vanilla_future_t *fut);

extern void encore_future_gc_acquireactor(pony_ctx_t* ctx, pony_actor_t* actor);
extern void encore_future_gc_acquireobject(pony_ctx_t* ctx, void* p,
    pony_type_t *t, int mutability);

static void vanilla_future_finalizer(vanilla_future_t *fut)
{
  pony_ctx_t* cctx = pony_ctx();
  vanilla_future_gc_recv_value(cctx, fut);
  ENC_DTRACE2(FUTURE_DESTROY, (uintptr_t) cctx, (uintptr_t) fut);
}

pony_type_t *vanilla_future_get_type(vanilla_future_t *fut){
  return fut->type;
}

bool vanilla_future_fulfilled(vanilla_future_t *fut)
{
  perr("future_fulfilled");
  bool r;
  r = __atomic_load_n(&fut->fulfilled, __ATOMIC_SEQ_CST);
  return r;
}

static inline void vanilla_future_gc_trace_value(pony_ctx_t *ctx, vanilla_future_t *fut)
{
  assert(fut);
  if (fut->type == ENCORE_ACTIVE) {
    encore_trace_actor(ctx, fut->value.p);
  } else if (fut->type != ENCORE_PRIMITIVE) {
    encore_trace_object(ctx, fut->value.p, fut->type->trace);
  }
}

static inline void vanilla_future_gc_send_value(pony_ctx_t *ctx, vanilla_future_t *fut)
{
  pony_gc_send(ctx);
  vanilla_future_gc_trace_value(ctx, fut);
  pony_send_done(ctx);
}

static inline void vanilla_future_gc_recv_value(pony_ctx_t *ctx, vanilla_future_t *fut)
{
  pony_gc_recv(ctx);
  vanilla_future_gc_trace_value(ctx, fut);
  ponyint_gc_handlestack(ctx);
}

static inline void vanilla_future_discharge_producer(pony_ctx_t **ctx, vanilla_future_t *fut);
void vanilla_future_discharge_consumer(pony_ctx_t **ctx, bool * on_stack, encore_actor_t *actor);

/**

poly future methods

**/

vanilla_future_t *vanilla_future_mk(pony_ctx_t **ctx, pony_type_t *type)
{
  pony_ctx_t *cctx = *ctx;
  assert(cctx->current);

  vanilla_future_t *fut = pony_alloc_final(cctx, sizeof(future_t),
          (void *)&vanilla_future_finalizer);
  *fut = (vanilla_future_t) { .type = type, .on_stack = false };

  ENC_DTRACE3(FUTURE_CREATE, (uintptr_t) ctx, (uintptr_t) fut, (uintptr_t) type);
  return fut;
} 

void vanilla_future_fulfil(pony_ctx_t **ctx, vanilla_future_t *fut, encore_arg_t value) 
{
  assert(fut->fulfilled == false);
  ENC_DTRACE2(FUTURE_FULFIL_START, (uintptr_t) *ctx, (uintptr_t) fut);

  fut->value = value;
  __atomic_store_n(&(fut->fulfilled), true, __ATOMIC_SEQ_CST);

  vanilla_future_gc_send_value(*ctx, fut);

  vanilla_future_discharge_producer(ctx, fut);

  ENC_DTRACE2(FUTURE_FULFIL_END, (uintptr_t) *ctx, (uintptr_t) fut);
}

encore_arg_t vanilla_future_get_actor(pony_ctx_t **ctx, vanilla_future_t *fut)
{
  if (!__atomic_load_n(&(fut->fulfilled), __ATOMIC_SEQ_CST)) {
    ENC_DTRACE2(FUTURE_BLOCK, (uintptr_t) *ctx, (uintptr_t) fut);
    vanilla_future_block_actor(ctx, fut);
    ENC_DTRACE2(FUTURE_UNBLOCK, (uintptr_t) *ctx, (uintptr_t) fut);
  }

  ENC_DTRACE2(FUTURE_GET, (uintptr_t) *ctx, (uintptr_t) fut);
  return fut->value;
}

static void vanilla_future_block_actor(pony_ctx_t **ctx, vanilla_future_t *fut)
{
  perr("future_block_actor");
  if (__atomic_load_n(&(fut->fulfilled), __ATOMIC_SEQ_CST)) {
    return;
  }

  pony_ctx_t* cctx = *ctx;
  pony_actor_t *a = cctx->current;
  pony_unschedule(cctx, a);
  encore_actor_t *actor = (encore_actor_t*) a;
  
  pony_actor_node_info_t * pony_node = POOL_ALLOC(pony_actor_node_info_t);
  pony_node->on_stack = &fut->on_stack;
  pony_node->fulfilled = &fut->fulfilled;
  pony_node->fclass = VANILLA_FUTURE;
  pony_node->vfut = fut;

  actor_block(ctx, actor, (void *)pony_node);          
}

void vanilla_future_discharge_producer(pony_ctx_t **ctx, vanilla_future_t *fut) {
  if (__sync_bool_compare_and_swap(&(fut->on_stack), true, false)) { 
     perr("Unblocking");
     actor_set_resume((encore_actor_t *)fut->actor);
     pony_schedule(*ctx, fut->actor);
  }   
}

void vanilla_future_discharge_consumer(pony_ctx_t **ctx, bool * on_stack, encore_actor_t *actor) {
  if (__sync_bool_compare_and_swap(on_stack, true, false)) { 
     perr("Unblocking");
     actor_set_resume(actor);
     pony_schedule(*ctx, (pony_actor_t *)actor);
  }
}
