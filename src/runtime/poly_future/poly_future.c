
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
#include "poly_future.h"
#include "../libponyrt/actor/messageq.h"
#include "../libponyrt/sched/scheduler.h"

#define GET 0
#define AWAIT 1
#define CHAIN 2
#define TREIBER_STACK 1
#define BLOCK    pthread_mutex_lock(&fut->lock);
#define UNBLOCK  pthread_mutex_unlock(&fut->lock);
#define perr(m)  // fprintf(stderr, "%s\n", m);

static void poly_future_finalizer(poly_future_t *fut);
static inline void poly_future_gc_send_value(pony_ctx_t *ctx, poly_future_t *fut);
static inline void poly_future_gc_recv_value(pony_ctx_t *ctx, poly_future_t *fut);

extern void encore_future_gc_acquireactor(pony_ctx_t* ctx, pony_actor_t* actor);
extern void encore_future_gc_acquireobject(pony_ctx_t* ctx, void* p,
    pony_type_t *t, int mutability);
static void encore_gc_acquire(pony_ctx_t* ctx)
{
  assert(ctx->stack == NULL);
  ctx->trace_object = encore_future_gc_acquireobject;
  ctx->trace_actor = encore_future_gc_acquireactor;
}

typedef struct actor_entry actor_entry_t;
typedef struct closure_entry closure_entry_t;
typedef struct message_entry message_entry_t;

// Terminology:
// Producer -- the actor responsible for fulfilling a future
// Consumer -- an non-producer actor using a future

typedef enum responsibility_t
{
  // A closure that should be run by the producer
  DETACHED_CLOSURE,
  // A message blocked on this future
  BLOCKED_MESSAGE
} responsibility_t;

struct closure_entry
{
  // The consumer that created closure
  pony_actor_t *actor;
  // The future where the result of the closure should be stored
  future_t     *future;
  // The closure to be run on fulfilment of the future
  closure_t    *closure;

  closure_entry_t *next;

};

struct message_entry
{
  // The consumer that created closure
  pony_actor_t *actor;
  // FIXME: add context
};

struct actor_entry
{
  responsibility_t type;
  union
  {
    closure_entry_t closure;
    message_entry_t message;
  };
};


static inline void poly_future_gc_trace_value(pony_ctx_t *ctx, poly_future_t *fut)
{
  assert(fut);
  if (fut->type == ENCORE_ACTIVE) {
    encore_trace_actor(ctx, fut->value.p);
  } else if (fut->type != ENCORE_PRIMITIVE) {
    encore_trace_object(ctx, fut->value.p, fut->type->trace);
  }
}

static void poly_future_finalizer(poly_future_t *fut)
{
  pony_ctx_t* cctx = pony_ctx();
  poly_future_gc_recv_value(cctx, fut);
  ENC_DTRACE2(FUTURE_DESTROY, (uintptr_t) cctx, (uintptr_t) fut);
}

static inline void poly_future_gc_send_value(pony_ctx_t *ctx, poly_future_t *fut)
{
  pony_gc_send(ctx);
  poly_future_gc_trace_value(ctx, fut);
  pony_send_done(ctx);
}

static inline void poly_future_gc_recv_value(pony_ctx_t *ctx, poly_future_t *fut)
{
  pony_gc_recv(ctx);
  poly_future_gc_trace_value(ctx, fut);
  // note the asymmetry with send
  ponyint_gc_handlestack(ctx);
}

    /* UNCHAINED MONO FUTURES */ 

typedef struct pony_actor_node {
  pony_actor_t * actor;
  ucontext_t *awaited_uctx;
  int futop;
  struct pony_actor_node * next;
} pony_actor_node_t;

pony_actor_node_t * blocking_actor_stack_push(pony_ctx_t **ctx, pony_actor_node_t *head, pony_actor_t* pa);
pony_actor_t * blocking_actor_stack_pop(pony_ctx_t **ctx, pony_actor_node_t **head);
void poly_future_discharge(pony_ctx_t **ctx, poly_future_t *fut);
static void poly_future_block_actor(pony_ctx_t **ctx, poly_future_t *fut);

/**

Treiber stack implementation

**/

void treiber_stack_push(pony_actor_node_t **head, pony_actor_t* a, ucontext_t *awaited_uctx, int futop) {
  pony_actor_node_t * newhead = POOL_ALLOC(pony_actor_node_t);  //encore_alloc(cctx, sizeof(pony_actor_node_t));
  pony_actor_node_t * oldhead = __atomic_load_n(head, __ATOMIC_SEQ_CST); 
  newhead->actor = a;
  newhead->awaited_uctx = awaited_uctx;
  newhead->futop = futop;
  newhead->next = oldhead;

  while (!__sync_bool_compare_and_swap(head, oldhead, newhead) ) {
    oldhead = __atomic_load_n(head, __ATOMIC_SEQ_CST); 
    newhead->next = oldhead;
  } 
}

pony_actor_node_t * treiber_stack_pop(pony_actor_node_t **head) {
  pony_actor_node_t * newhead;
  pony_actor_node_t * oldhead = __atomic_load_n(head, __ATOMIC_SEQ_CST); 
  if (oldhead == NULL) {
    return NULL;  
  }
  newhead = oldhead->next;
  while (!__sync_bool_compare_and_swap(head, oldhead, newhead)) {
    oldhead = __atomic_load_n(head, __ATOMIC_SEQ_CST); 
    if (oldhead == NULL) {
         return NULL;  
      }   
      newhead = oldhead->next;
  }

  return oldhead;
}

/**

poly future methods

**/

poly_future_t *poly_future_mk(pony_ctx_t **ctx, pony_type_t *type)
{
  pony_ctx_t *cctx = *ctx;
  assert(cctx->current);

  poly_future_t *fut = pony_alloc_final(cctx, sizeof(poly_future_t),
          (void *)&poly_future_finalizer);
  *fut = (poly_future_t) { .type = type, .blocking_stack = NULL };

  #if !TREIBER_STACK
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&fut->lock, &attr);
  #endif

  ENC_DTRACE3(FUTURE_CREATE, (uintptr_t) ctx, (uintptr_t) fut, (uintptr_t) type);
  return fut;
} 

void poly_future_fulfil(pony_ctx_t **ctx, poly_future_t *fut, encore_arg_t value) 
{
  assert(fut->fulfilled == false);
  ENC_DTRACE2(FUTURE_FULFIL_START, (uintptr_t) *ctx, (uintptr_t) fut);
  fut->value = value;
  __atomic_store_n(&(fut->fulfilled), true, __ATOMIC_SEQ_CST);

  poly_future_gc_send_value(*ctx, fut);

  poly_future_discharge(ctx, fut);

  ENC_DTRACE2(FUTURE_FULFIL_END, (uintptr_t) *ctx, (uintptr_t) fut);
}

encore_arg_t poly_future_get_actor(pony_ctx_t **ctx, poly_future_t *fut)
{
  if (!__atomic_load_n(&(fut->fulfilled), __ATOMIC_SEQ_CST)) {
    ENC_DTRACE2(FUTURE_BLOCK, (uintptr_t) *ctx, (uintptr_t) fut);
    poly_future_block_actor(ctx, fut);
    ENC_DTRACE2(FUTURE_UNBLOCK, (uintptr_t) *ctx, (uintptr_t) fut);
  }

  ENC_DTRACE2(FUTURE_GET, (uintptr_t) *ctx, (uintptr_t) fut);
  return fut->value;
}

/*
poly_future_t *poly_future_chain_actor(pony_ctx_t **ctx, poly_future_t *fut, pony_type_t *type,
        closure_t *c)
{
  ENC_DTRACE3(FUTURE_CHAINING, (uintptr_t) *ctx, (uintptr_t) fut, (uintptr_t) type);
  future_t *r = future_mk(ctx, type);
  perr("future_chain_actor");
  BLOCK;

  if (fut->fulfilled) {
    acquire_future_value(ctx, fut);
    value_t result = run_closure(ctx, c, fut->value);
    future_fulfil(ctx, r, result);
    UNBLOCK;
    return r;
  }

  pony_ctx_t* cctx = *ctx;
  closure_entry_t *entry = encore_alloc(cctx, sizeof *entry);
  entry->actor = (cctx)->current;
  entry->future = r;
  entry->closure = c;
  entry->next = fut->children;
  fut->children = entry;

  pony_gc_send(cctx);
  trace_closure_entry(cctx, entry);
  pony_send_done(cctx);

  UNBLOCK;

  r->parent = fut;

  return r;
}

// Similar to `future_chain_actor` except that it returns void, avoiding the
// creation of a new future. This is used in the ParTs library and is an
// optimisation over the `future_chain_actor`.
void future_register_callback(pony_ctx_t **ctx,
                              future_t *fut,
                              closure_t *c)
{
  ENC_DTRACE2(FUTURE_REGISTER_CALLBACK, (uintptr_t) *ctx, (uintptr_t) fut);
  perr("future_chain_actor");
  BLOCK;

  if (fut->fulfilled) {
    acquire_future_value(ctx, fut);

    // the closure is in charge of fulfilling the promise that it contains.
    // if this is not the case, a deadlock situation may happen.
    run_closure(ctx, c, fut->value);
    UNBLOCK;
    return ;
  }

  pony_ctx_t* cctx = *ctx;
  closure_entry_t *entry = encore_alloc(cctx, sizeof *entry);
  entry->actor = (cctx)->current;
  entry->future = NULL;
  entry->closure = c;
  entry->next = fut->children;
  fut->children = entry;

  pony_gc_send(cctx);
  trace_closure_entry(cctx, entry);
  pony_send_done(cctx);

  UNBLOCK;
}

*/

static void poly_future_block_actor(pony_ctx_t **ctx, poly_future_t *fut)
{
  perr("poly_future_block_actor");
  if (__atomic_load_n(&(fut->fulfilled), __ATOMIC_SEQ_CST)) {
    return;
  }

  // perform blocking procedure
  pony_ctx_t* cctx = *ctx;
  pony_actor_t *a = cctx->current;
  pony_unschedule(cctx, a);
  encore_actor_t *actor = (encore_actor_t*) a;
  
  pony_actor_node_info_t * pony_node = POOL_ALLOC(pony_actor_node_info_t);
  pony_node->fut = fut;
  pony_node->awaited_uctx = NULL;
  pony_node->futop = GET;
  actor_block(ctx, actor, (void *)pony_node);          // longjump back into scheduler
}

void poly_future_await(pony_ctx_t **ctx, poly_future_t *fut)
{
  if (__atomic_load_n(&(fut->fulfilled), __ATOMIC_SEQ_CST)) {
    return;
  }
  ucontext_t uctx;
  
  pony_actor_node_info_t * pony_node = POOL_ALLOC(pony_actor_node_info_t);
  pony_node->fut = fut;
  pony_node->futop = AWAIT;
  pony_node->awaited_uctx = &uctx;

  actor_await(ctx, &uctx, (void *)pony_node);
}

void poly_future_discharge(pony_ctx_t **ctx, poly_future_t *fut) {
  pony_actor_node_t * a = NULL;
  pony_ctx_t * cctx = * ctx;
  encore_actor_t * ea;

  a = treiber_stack_pop(&fut->blocking_stack);
  while (a!=NULL) {
      //printf("Unblocking\n");
      if (a->futop == GET) {
        ea = (encore_actor_t *)a->actor; 
        perr("Unblocking");
        actor_set_resume(ea);
        pony_schedule(cctx, a->actor);
      } else if (a->futop == AWAIT) {
        pony_sendp(cctx, a->actor, _ENC__MSG_RESUME_AWAIT, a->awaited_uctx);
      }  

      POOL_FREE(pony_actor_node_t, a);
      a = treiber_stack_pop(&fut->blocking_stack);
  } 
}