#ifndef __future_using_actors_h
#define __future_using_actors_h

#include <pony.h>
#include "closure.h"

typedef struct pony_actor_node pony_actor_node_t;

typedef struct poly_future {
  ucontext_t *uctx;
  pony_actor_node_t *blocking_stack;
  pony_type_t  *type;
  encore_arg_t value;
  bool fulfilled;
} poly_future_t;

typedef struct pony_actor_node_info {
  ucontext_t *awaited_uctx;
  poly_future_t *fut;
  int futop;
} pony_actor_node_info_t;

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
poly_future_t *poly_future_mk(pony_ctx_t **ctx, pony_type_t *type);

/** Check if the future is already fulfilled
 *
 * (this operation may be blocking until the future is fulfilled)
 */
bool future_fulfilled  (future_t *fut);

/*
 * Fulfil the future with the given value
 */
void poly_future_fulfil(pony_ctx_t **ctx, poly_future_t *fut, encore_arg_t value) ;

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
encore_arg_t poly_future_get_actor(pony_ctx_t **ctx, poly_future_t *fut);

/*
 * Chains a callback to a future returning a new future (placeholder)
 * with the result of the callback function
 */


//poly_future_t *poly_future_chain_actor(pony_ctx_t **ctx, poly_future_t *fut, pony_type_t *type,
//        closure_t *c);

/** Registers a callback and returns void
 *
 *
 * This function attaches a callback on future `fut`. The void return value
 * makes this function useful for effectful computations with less overhead
 * than `future_chain_actor`.
 */

/*
void future_register_callback(pony_ctx_t **ctx,
                              future_t *fut,
                              closure_t *c);
*/

void poly_future_await(pony_ctx_t **ctx, poly_future_t *fut);

void poly_future_discharge(pony_ctx_t **ctx, poly_future_t *fut);

void treiber_stack_push(pony_actor_node_t **head, pony_actor_t* a, ucontext_t *awaited_uctx, int futop);
pony_actor_node_t * treiber_stack_pop(pony_actor_node_t **head);
#endif