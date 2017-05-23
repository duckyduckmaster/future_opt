#ifndef __future_using_actors_h
#define __future_using_actors_h

#include <pony.h>
#include <closure.h>
#include "/Users/Kattas/encore_future_opt/encore/src/runtime/pony/libponyrt/sched/mpmcq.h"

typedef struct pony_actor_node pony_actor_node_t;

typedef struct closure_entry closure_entry_t;

typedef enum future_class {
  FUTURE,
  VANILLA_FUTURE,
  POLY_VANILLA_FUTURE,
  SINGLE_CHAIN_FUTURE
} future_class_t ;

typedef struct pony_actor_node_class_info {
  future_class_t fclass;
} pony_actor_node_class_info_t;

/* TREIBER STACK API */

void treiber_stack_push(pony_actor_node_t **head, pony_actor_t* a, ucontext_t *awaited_uctx, int futop);
pony_actor_node_t * treiber_stack_pop(pony_actor_node_t **head);

/* STANDARD FUTURE API  */

typedef struct future {
  ucontext_t *uctx;
  pony_actor_node_t *blocking_stack;
  closure_entry_t *chain_stack;
  pony_type_t  *type;
  encore_arg_t value;
  bool fulfilled;
} future_t;

typedef struct vanilla_future {
  pony_type_t *type;
  pony_actor_t *actor;
  encore_arg_t value;
  bool fulfilled;
  bool on_stack;
} vanilla_future_t;

typedef struct single_chain_future {
  pony_type_t *type;
  pony_actor_t *actor;
  mpmcq_t *closure_queue;
  encore_arg_t value;
  bool fulfilled;
  bool on_stack;
} single_chain_future_t;

typedef struct poly_vanilla_future {
  pony_actor_node_t *blocking_stack;
  pony_type_t  *type;
  encore_arg_t value;
  bool fulfilled;
} poly_vanilla_future_t;

void future_trace(pony_ctx_t *ctx, void* p);

typedef struct future future_t;

extern pony_type_t future_type;
void future_trace(pony_ctx_t *ctx, void* p);

/*
 * Get the value type of the future
 */
pony_type_t *future_get_type(future_t *fut);

// ===============================================================
// Create, inspect and fulfil
// ===============================================================

/*
 * Create a new future
 */
future_t *future_mk(pony_ctx_t **ctx, pony_type_t *type);

/** Check if the future is already fulfilled
 *
 * (this operation may be blocking until the future is fulfilled)
 */
bool future_fulfilled  (future_t *fut);

/*
 * Fulfil the future with the given value
 */
void future_fulfil(pony_ctx_t **ctx, future_t *fut, encore_arg_t value);

// ===============================================================
// Means for actors to get, block and chain
// ===============================================================

/** Gets the value from the future
 *
 * This functions extracts the value of the future. If the future is not
 * fulfilled by the time this function is called, the actor will be blocked
 * and unable to process messages until the future is fulfilled. When the future
 * is fulfilled, this operation just extracts the value contained in the future.
 */
encore_arg_t future_get_actor(pony_ctx_t **ctx, future_t *fut);

/*
 * Chains a callback to a future returning a new future (placeholder)
 * with the result of the callback function
 */
future_t *future_chain_actor(pony_ctx_t **ctx, future_t *fut, pony_type_t *type,
        closure_t *c);

/** Registers a callback and returns void
 *
 *
 * This function attaches a callback on future `fut`. The void return value
 * makes this function useful for effectful computations with less overhead
 * than `future_chain_actor`.
 */
void future_register_callback(pony_ctx_t **ctx,
                              future_t *fut,
                              closure_t *c);

// ===============================================================
// Possibly these functions do not belong in the future library
// ===============================================================

/** Await on future until it is fulfilled
 *
 * This operation awaits on the future until it is fulfilled. In contrast to
 * `future_get_actor`, this operation does not block the current actor and just
 * puts on hold the processing of this message.
 */
void future_await(pony_ctx_t **ctx, future_t *fut);

typedef struct pony_actor_node_info {
  //single chain future
  single_chain_future_t *scfut;
  //poly_vanilla_future
  poly_vanilla_future_t *pvfut;
  //vanilla future
  bool * fulfilled;
  bool * on_stack;
  vanilla_future_t *vfut;
  //future
  ucontext_t * awaited_uctx;
  future_class_t fclass;
  future_t *fut;
  int futop;
} pony_actor_node_info_t;

extern pony_type_t future_type;

void future_discharge(pony_ctx_t **ctx, future_t *fut);

/* VANILLA FUTURE API */

void vanilla_future_discharge_consumer(pony_ctx_t **ctx, bool * on_stack, encore_actor_t *actor);
encore_arg_t vanilla_future_get_actor(pony_ctx_t **ctx, vanilla_future_t *fut);
void vanilla_future_fulfil(pony_ctx_t **ctx, vanilla_future_t *fut, encore_arg_t value);
vanilla_future_t *vanilla_future_mk(pony_ctx_t **ctx, pony_type_t *type); 

/* SINGLE CHAIN FUTURE API */
single_chain_future_t *single_chain_future_mk(pony_ctx_t **ctx, pony_type_t *type);
void single_chain_future_discharge_consumer(pony_ctx_t **ctx, single_chain_future_t *fut);
void single_chain_future_register_callback(pony_ctx_t **ctx,
                              single_chain_future_t *fut,
                              closure_t *c);
single_chain_future_t *single_chain_future_chain_actor(pony_ctx_t **ctx, single_chain_future_t *fut, 
        closure_t *c);
encore_arg_t single_chain_future_get_actor(pony_ctx_t **ctx, single_chain_future_t *fut);
void single_chain_future_fulfil(pony_ctx_t **ctx, single_chain_future_t *fut, encore_arg_t value);

/* POLY VANILLA FUTURE API */
void poly_vanilla_future_discharge(pony_ctx_t **ctx, poly_vanilla_future_t *fut);
encore_arg_t poly_vanilla_future_get_actor(pony_ctx_t **ctx, poly_vanilla_future_t *fut);
void poly_vanilla_future_fulfil(pony_ctx_t **ctx, poly_vanilla_future_t *fut, encore_arg_t value);
poly_vanilla_future_t *poly_vanilla_future_mk(pony_ctx_t **ctx, pony_type_t *type); 

#endif
