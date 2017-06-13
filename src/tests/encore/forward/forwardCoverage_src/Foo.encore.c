#include "header.h"


static void* trait_method_selector(int id)
{
  switch (id)
  {
    default:
    {
      printf("error, got invalid id: %d", id);
    }
  };
  return NULL;
}


struct _enc__class__forwardCoverage_Foo_t
{
  encore_actor_t _enc__actor;
};


void _enc__type_init__forwardCoverage_Foo(_enc__class__forwardCoverage_Foo_t* _this, ... )
{
  va_list params;
  va_start(params, _this);
  va_end(params);
}


void _enc__trace__forwardCoverage_Foo(pony_ctx_t* _ctx_arg, void* p)
{
  pony_ctx_t** _ctx = (&(_ctx_arg));
  _enc__class__forwardCoverage_Foo_t* _this = p;
}


_enc__class__forwardCoverage_Foo_t* _enc__constructor__forwardCoverage_Foo(pony_ctx_t** _ctx, pony_type_t** runtimeType)
{
  _enc__class__forwardCoverage_Foo_t* _this = ((_enc__class__forwardCoverage_Foo_t*) encore_create((*_ctx), (&(_enc__class__forwardCoverage_Foo_type))));
  return _this;
}


void* _enc__method__forwardCoverage_Foo_await(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "await");
  pony_type_t* _enc__type__t = (runtimeType[0]);
  future_await(_ctx, _enc__arg_f);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "await");
  return UNIT;
}


future_t* _enc__method__forwardCoverage_Foo_await_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_await_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_await_t)), _ENC__FUT_MSG__forwardCoverage_Foo_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Foo_await_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f, future_t* _fut)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_await_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_await_t)), _ENC__FUT_MSG__forwardCoverage_Foo_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Foo_await_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Foo_await_t* msg = ((_enc__oneway_msg__forwardCoverage_Foo_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Foo_await_t)), _ENC__ONEWAY_MSG__forwardCoverage_Foo_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


void* _enc__method__forwardCoverage_Foo_suspend(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "suspend");
  actor_suspend(_ctx);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "suspend");
  return UNIT;
}


future_t* _enc__method__forwardCoverage_Foo_suspend_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_suspend_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_suspend_t)), _ENC__FUT_MSG__forwardCoverage_Foo_suspend));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Foo_suspend_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_suspend_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_suspend_t)), _ENC__FUT_MSG__forwardCoverage_Foo_suspend));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Foo_suspend_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Foo_suspend_t* msg = ((_enc__oneway_msg__forwardCoverage_Foo_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Foo_suspend_t)), _ENC__ONEWAY_MSG__forwardCoverage_Foo_suspend));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


int64_t _enc__method__forwardCoverage_Foo_foo(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "foo");
  int64_t _literal_0 = 42;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "foo");
  return ((int64_t) _literal_0);
}


future_t* _enc__method__forwardCoverage_Foo_foo_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_foo_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_foo_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_foo_t)), _ENC__FUT_MSG__forwardCoverage_Foo_foo));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Foo_foo_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_foo_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_foo_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_foo_t)), _ENC__FUT_MSG__forwardCoverage_Foo_foo));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Foo_foo_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Foo_foo_t* msg = ((_enc__oneway_msg__forwardCoverage_Foo_foo_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Foo_foo_t)), _ENC__ONEWAY_MSG__forwardCoverage_Foo_foo));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


struct _enc__env_closure0
{
};


static void _enc__trace_closure0(pony_ctx_t* _ctx_arg, void* p)
{
  pony_ctx_t** _ctx = (&(_ctx_arg));
  struct _enc__env_closure0* _env = p;
}


static value_t _enc__closure_fun_closure0(pony_ctx_t** _ctx, pony_type_t** runtimeType, value_t _args[], void* _env)
{
  ENC_DTRACE1(CLOSURE_ENTRY, (uintptr_t)*_ctx);
  int64_t _enc__arg_x = (_args[0]).i;
  int64_t _binop_1 = (({ _enc__arg_x;}) + ({int64_t _literal_0 = 1; _literal_0;}));
  ENC_DTRACE1(CLOSURE_EXIT, (uintptr_t)*_ctx);
  return ((encore_arg_t) {.i = _binop_1});
}


int64_t _enc__method__forwardCoverage_Foo_multiChainWithMethodCall(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithMethodCall");
  /* val f = fun (x : int) => x + 1 */;
  /* f = fun (x : int) => x + 1 */;
  struct _enc__env_closure0* _enc__env_closure0 = encore_alloc((*_ctx), sizeof(struct _enc__env_closure0));
  closure_t* _tmp_0 = closure_mk(_ctx, _enc__closure_fun_closure0, _enc__env_closure0, _enc__trace_closure0, NULL);
  closure_t* _f_2 = _tmp_0;
  /* forward((new Foo)!foo() ~~> f ~~> f ~~> f ~~> f ~~> f) */;
  _enc__class__forwardCoverage_Foo_t* _new_3 = _enc__constructor__forwardCoverage_Foo(_ctx, NULL);
  pony_type_t* _tmp_4[] = {};
  _enc__type_init__forwardCoverage_Foo(_new_3);
  _enc__method__forwardCoverage_Foo_init_one_way(_ctx, _new_3, NULL);
  check_receiver(_new_3, " ! ", "new Foo()", "foo", "\"forwardCoverage.enc\" (line 19, column 24)");
  pony_type_t* _tmp_5[] = {};
  future_t* _fut_6 = _enc__method__forwardCoverage_Foo_foo_future(_ctx, _new_3, NULL);
  future_t* _tmp_7 = future_chain_actor(_ctx, _fut_6, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_8 = future_chain_actor(_ctx, _tmp_7, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_9 = future_chain_actor(_ctx, _tmp_8, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_10 = future_chain_actor(_ctx, _tmp_9, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_12 = future_chain_actor(_ctx, _tmp_10, ENCORE_PRIMITIVE, _f_2);
  int64_t _tmp_11 = future_get_actor(_ctx, _tmp_12).i;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithMethodCall");
  return ((int64_t) _tmp_11);
}


void _enc__method__forwardCoverage_Foo_multiChainWithMethodCall_async(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithMethodCall");
  /* val f = fun (x : int) => x + 1 */;
  /* f = fun (x : int) => x + 1 */;
  struct _enc__env_closure0* _enc__env_closure0 = encore_alloc((*_ctx), sizeof(struct _enc__env_closure0));
  closure_t* _tmp_0 = closure_mk(_ctx, _enc__closure_fun_closure0, _enc__env_closure0, _enc__trace_closure0, NULL);
  closure_t* _f_2 = _tmp_0;
  /* forward((new Foo)!foo() ~~> f ~~> f ~~> f ~~> f ~~> f) */;
  _enc__class__forwardCoverage_Foo_t* _new_3 = _enc__constructor__forwardCoverage_Foo(_ctx, NULL);
  pony_type_t* _tmp_4[] = {};
  _enc__type_init__forwardCoverage_Foo(_new_3);
  _enc__method__forwardCoverage_Foo_init_one_way(_ctx, _new_3, NULL);
  check_receiver(_new_3, " ! ", "new Foo()", "foo", "\"forwardCoverage.enc\" (line 19, column 24)");
  pony_type_t* _tmp_5[] = {};
  future_t* _fut_6 = _enc__method__forwardCoverage_Foo_foo_future(_ctx, _new_3, NULL);
  future_t* _tmp_7 = future_chain_actor(_ctx, _fut_6, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_8 = future_chain_actor(_ctx, _tmp_7, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_9 = future_chain_actor(_ctx, _tmp_8, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_10 = future_chain_actor(_ctx, _tmp_9, ENCORE_PRIMITIVE, _f_2);
  future_chain_forward(_ctx, _tmp_10, ENCORE_PRIMITIVE, _f_2, _fut);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithMethodCall");
  return;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithMethodCall");
  if (_fut)
  {
    future_fulfil(_ctx, _fut, ((encore_arg_t) {.i = ((int64_t) UNIT)}));
  }
  else
  {
  };
}


future_t* _enc__method__forwardCoverage_Foo_multiChainWithMethodCall_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_multiChainWithMethodCall_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_multiChainWithMethodCall_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_multiChainWithMethodCall_t)), _ENC__FUT_MSG__forwardCoverage_Foo_multiChainWithMethodCall));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Foo_multiChainWithMethodCall_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_multiChainWithMethodCall_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_multiChainWithMethodCall_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_multiChainWithMethodCall_t)), _ENC__FUT_MSG__forwardCoverage_Foo_multiChainWithMethodCall));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Foo_multiChainWithMethodCall_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Foo_multiChainWithMethodCall_t* msg = ((_enc__oneway_msg__forwardCoverage_Foo_multiChainWithMethodCall_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Foo_multiChainWithMethodCall_t)), _ENC__ONEWAY_MSG__forwardCoverage_Foo_multiChainWithMethodCall));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


struct _enc__env_closure1
{
};


static void _enc__trace_closure1(pony_ctx_t* _ctx_arg, void* p)
{
  pony_ctx_t** _ctx = (&(_ctx_arg));
  struct _enc__env_closure1* _env = p;
}


static value_t _enc__closure_fun_closure1(pony_ctx_t** _ctx, pony_type_t** runtimeType, value_t _args[], void* _env)
{
  ENC_DTRACE1(CLOSURE_ENTRY, (uintptr_t)*_ctx);
  int64_t _enc__arg_x = (_args[0]).i;
  int64_t _binop_1 = (({ _enc__arg_x;}) + ({int64_t _literal_0 = 1; _literal_0;}));
  ENC_DTRACE1(CLOSURE_EXIT, (uintptr_t)*_ctx);
  return ((encore_arg_t) {.i = _binop_1});
}


int64_t _enc__method__forwardCoverage_Foo_multiChainWithId(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithId");
  /* val f = fun (x : int) => x + 1 */;
  /* f = fun (x : int) => x + 1 */;
  struct _enc__env_closure1* _enc__env_closure1 = encore_alloc((*_ctx), sizeof(struct _enc__env_closure1));
  closure_t* _tmp_0 = closure_mk(_ctx, _enc__closure_fun_closure1, _enc__env_closure1, _enc__trace_closure1, NULL);
  closure_t* _f_2 = _tmp_0;
  /* forward(id(arg ~~> f) ~~> f ~~> f ~~> f ~~> f) */;
  future_t* _tmp_3 = future_chain_actor(_ctx, _enc__arg_arg, ENCORE_PRIMITIVE, _f_2);
  ENC_DTRACE2(FUNCTION_CALL, (uintptr_t)*_ctx, "id");
  pony_type_t* _tmp_4[] = {(&(future_type))};
  future_t* _fun_call_5 = _enc__global_fun__forwardCoverageid(_ctx, _tmp_4, ((encore_arg_t) {.p = _tmp_3})).p;
  future_t* _tmp_6 = future_chain_actor(_ctx, _fun_call_5, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_7 = future_chain_actor(_ctx, _tmp_6, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_8 = future_chain_actor(_ctx, _tmp_7, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_10 = future_chain_actor(_ctx, _tmp_8, ENCORE_PRIMITIVE, _f_2);
  int64_t _tmp_9 = future_get_actor(_ctx, _tmp_10).i;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithId");
  return ((int64_t) _tmp_9);
}


void _enc__method__forwardCoverage_Foo_multiChainWithId_async(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg, future_t* _fut)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithId");
  /* val f = fun (x : int) => x + 1 */;
  /* f = fun (x : int) => x + 1 */;
  struct _enc__env_closure1* _enc__env_closure1 = encore_alloc((*_ctx), sizeof(struct _enc__env_closure1));
  closure_t* _tmp_0 = closure_mk(_ctx, _enc__closure_fun_closure1, _enc__env_closure1, _enc__trace_closure1, NULL);
  closure_t* _f_2 = _tmp_0;
  /* forward(id(arg ~~> f) ~~> f ~~> f ~~> f ~~> f) */;
  future_t* _tmp_3 = future_chain_actor(_ctx, _enc__arg_arg, ENCORE_PRIMITIVE, _f_2);
  ENC_DTRACE2(FUNCTION_CALL, (uintptr_t)*_ctx, "id");
  pony_type_t* _tmp_4[] = {(&(future_type))};
  future_t* _fun_call_5 = _enc__global_fun__forwardCoverageid(_ctx, _tmp_4, ((encore_arg_t) {.p = _tmp_3})).p;
  future_t* _tmp_6 = future_chain_actor(_ctx, _fun_call_5, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_7 = future_chain_actor(_ctx, _tmp_6, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_8 = future_chain_actor(_ctx, _tmp_7, ENCORE_PRIMITIVE, _f_2);
  future_chain_forward(_ctx, _tmp_8, ENCORE_PRIMITIVE, _f_2, _fut);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithId");
  return;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithId");
  if (_fut)
  {
    future_fulfil(_ctx, _fut, ((encore_arg_t) {.i = ((int64_t) UNIT)}));
  }
  else
  {
  };
}


future_t* _enc__method__forwardCoverage_Foo_multiChainWithId_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_multiChainWithId_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_multiChainWithId_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_multiChainWithId_t)), _ENC__FUT_MSG__forwardCoverage_Foo_multiChainWithId));
  msg->f1 = _enc__arg_arg;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Foo_multiChainWithId_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_multiChainWithId_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_multiChainWithId_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_multiChainWithId_t)), _ENC__FUT_MSG__forwardCoverage_Foo_multiChainWithId));
  msg->f1 = _enc__arg_arg;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Foo_multiChainWithId_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Foo_multiChainWithId_t* msg = ((_enc__oneway_msg__forwardCoverage_Foo_multiChainWithId_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Foo_multiChainWithId_t)), _ENC__ONEWAY_MSG__forwardCoverage_Foo_multiChainWithId));
  msg->f1 = _enc__arg_arg;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


struct _enc__env_closure2
{
};


static void _enc__trace_closure2(pony_ctx_t* _ctx_arg, void* p)
{
  pony_ctx_t** _ctx = (&(_ctx_arg));
  struct _enc__env_closure2* _env = p;
}


static value_t _enc__closure_fun_closure2(pony_ctx_t** _ctx, pony_type_t** runtimeType, value_t _args[], void* _env)
{
  ENC_DTRACE1(CLOSURE_ENTRY, (uintptr_t)*_ctx);
  int64_t _enc__arg_x = (_args[0]).i;
  int64_t _binop_1 = (({ _enc__arg_x;}) + ({int64_t _literal_0 = 1; _literal_0;}));
  ENC_DTRACE1(CLOSURE_EXIT, (uintptr_t)*_ctx);
  return ((encore_arg_t) {.i = _binop_1});
}


int64_t _enc__method__forwardCoverage_Foo_multiChainWithExistingFuture(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithExistingFuture");
  /* val f = fun (x : int) => x + 1 */;
  /* f = fun (x : int) => x + 1 */;
  struct _enc__env_closure2* _enc__env_closure2 = encore_alloc((*_ctx), sizeof(struct _enc__env_closure2));
  closure_t* _tmp_0 = closure_mk(_ctx, _enc__closure_fun_closure2, _enc__env_closure2, _enc__trace_closure2, NULL);
  closure_t* _f_2 = _tmp_0;
  /* forward(arg ~~> f ~~> f ~~> f ~~> f ~~> f) */;
  future_t* _tmp_3 = future_chain_actor(_ctx, _enc__arg_arg, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_4 = future_chain_actor(_ctx, _tmp_3, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_5 = future_chain_actor(_ctx, _tmp_4, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_6 = future_chain_actor(_ctx, _tmp_5, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_8 = future_chain_actor(_ctx, _tmp_6, ENCORE_PRIMITIVE, _f_2);
  int64_t _tmp_7 = future_get_actor(_ctx, _tmp_8).i;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithExistingFuture");
  return ((int64_t) _tmp_7);
}


void _enc__method__forwardCoverage_Foo_multiChainWithExistingFuture_async(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg, future_t* _fut)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithExistingFuture");
  /* val f = fun (x : int) => x + 1 */;
  /* f = fun (x : int) => x + 1 */;
  struct _enc__env_closure2* _enc__env_closure2 = encore_alloc((*_ctx), sizeof(struct _enc__env_closure2));
  closure_t* _tmp_0 = closure_mk(_ctx, _enc__closure_fun_closure2, _enc__env_closure2, _enc__trace_closure2, NULL);
  closure_t* _f_2 = _tmp_0;
  /* forward(arg ~~> f ~~> f ~~> f ~~> f ~~> f) */;
  future_t* _tmp_3 = future_chain_actor(_ctx, _enc__arg_arg, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_4 = future_chain_actor(_ctx, _tmp_3, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_5 = future_chain_actor(_ctx, _tmp_4, ENCORE_PRIMITIVE, _f_2);
  future_t* _tmp_6 = future_chain_actor(_ctx, _tmp_5, ENCORE_PRIMITIVE, _f_2);
  future_chain_forward(_ctx, _tmp_6, ENCORE_PRIMITIVE, _f_2, _fut);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithExistingFuture");
  return;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "multiChainWithExistingFuture");
  if (_fut)
  {
    future_fulfil(_ctx, _fut, ((encore_arg_t) {.i = ((int64_t) UNIT)}));
  }
  else
  {
  };
}


future_t* _enc__method__forwardCoverage_Foo_multiChainWithExistingFuture_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t)), _ENC__FUT_MSG__forwardCoverage_Foo_multiChainWithExistingFuture));
  msg->f1 = _enc__arg_arg;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Foo_multiChainWithExistingFuture_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t)), _ENC__FUT_MSG__forwardCoverage_Foo_multiChainWithExistingFuture));
  msg->f1 = _enc__arg_arg;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Foo_multiChainWithExistingFuture_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t* msg = ((_enc__oneway_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t)), _ENC__ONEWAY_MSG__forwardCoverage_Foo_multiChainWithExistingFuture));
  msg->f1 = _enc__arg_arg;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


void* _enc__method__forwardCoverage_Foo_init(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "init");
  /* () */;
  UNIT;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "init");
  return UNIT;
}


future_t* _enc__method__forwardCoverage_Foo_init_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_init_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_init_t)), _ENC__FUT_MSG__forwardCoverage_Foo_init));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Foo_init_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Foo_init_t* msg = ((_enc__fut_msg__forwardCoverage_Foo_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Foo_init_t)), _ENC__FUT_MSG__forwardCoverage_Foo_init));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Foo_init_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Foo_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Foo_init_t* msg = ((_enc__oneway_msg__forwardCoverage_Foo_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Foo_init_t)), _ENC__ONEWAY_MSG__forwardCoverage_Foo_init));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


static void _enc__dispatch__forwardCoverage_Foo(pony_ctx_t** _ctx, pony_actor_t* _a, pony_msg_t* _m)
{
  _enc__class__forwardCoverage_Foo_t* _this = ((_enc__class__forwardCoverage_Foo_t*) _a);
  switch (_m->id)
  {
    case _ENC__FUT_MSG__forwardCoverage_Foo_await:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      pony_type_t* _enc__type__t = ((_enc__fut_msg__forwardCoverage_Foo_await_t*) _m)->_enc__type__t;
      future_t* _enc__arg_f = ((_enc__fut_msg__forwardCoverage_Foo_await_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_f, future_trace);
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {_enc__type__t};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__forwardCoverage_Foo_await(_ctx, _this, methodTypeVars, _enc__arg_f)}));
      break;
    }
    case _ENC__ONEWAY_MSG__forwardCoverage_Foo_await:
    {
      pony_type_t* _enc__type__t = ((_enc__oneway_msg__forwardCoverage_Foo_await_t*) _m)->_enc__type__t;
      future_t* _enc__arg_f = ((_enc__oneway_msg__forwardCoverage_Foo_await_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_f, future_trace);
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {_enc__type__t};
      _enc__method__forwardCoverage_Foo_await(_ctx, _this, methodTypeVars, _enc__arg_f);
      break;
    }
    case _ENC__FUT_MSG__forwardCoverage_Foo_suspend:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__forwardCoverage_Foo_suspend(_ctx, _this, methodTypeVars)}));
      break;
    }
    case _ENC__ONEWAY_MSG__forwardCoverage_Foo_suspend:
    {
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Foo_suspend(_ctx, _this, methodTypeVars);
      break;
    }
    case _ENC__FUT_MSG__forwardCoverage_Foo_foo:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.i = _enc__method__forwardCoverage_Foo_foo(_ctx, _this, methodTypeVars)}));
      break;
    }
    case _ENC__ONEWAY_MSG__forwardCoverage_Foo_foo:
    {
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Foo_foo(_ctx, _this, methodTypeVars);
      break;
    }
    case _ENC__FUT_MSG__forwardCoverage_Foo_multiChainWithMethodCall:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Foo_multiChainWithMethodCall_async(_ctx, _this, methodTypeVars, _fut);
      break;
    }
    case _ENC__ONEWAY_MSG__forwardCoverage_Foo_multiChainWithMethodCall:
    {
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Foo_multiChainWithMethodCall_async(_ctx, _this, methodTypeVars, NULL);
      break;
    }
    case _ENC__FUT_MSG__forwardCoverage_Foo_multiChainWithId:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      future_t* _enc__arg_arg = ((_enc__fut_msg__forwardCoverage_Foo_multiChainWithId_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Foo_multiChainWithId_async(_ctx, _this, methodTypeVars, _enc__arg_arg, _fut);
      break;
    }
    case _ENC__ONEWAY_MSG__forwardCoverage_Foo_multiChainWithId:
    {
      future_t* _enc__arg_arg = ((_enc__oneway_msg__forwardCoverage_Foo_multiChainWithId_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Foo_multiChainWithId_async(_ctx, _this, methodTypeVars, _enc__arg_arg, NULL);
      break;
    }
    case _ENC__FUT_MSG__forwardCoverage_Foo_multiChainWithExistingFuture:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      future_t* _enc__arg_arg = ((_enc__fut_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Foo_multiChainWithExistingFuture_async(_ctx, _this, methodTypeVars, _enc__arg_arg, _fut);
      break;
    }
    case _ENC__ONEWAY_MSG__forwardCoverage_Foo_multiChainWithExistingFuture:
    {
      future_t* _enc__arg_arg = ((_enc__oneway_msg__forwardCoverage_Foo_multiChainWithExistingFuture_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Foo_multiChainWithExistingFuture_async(_ctx, _this, methodTypeVars, _enc__arg_arg, NULL);
      break;
    }
    case _ENC__FUT_MSG__forwardCoverage_Foo_init:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__forwardCoverage_Foo_init(_ctx, _this, methodTypeVars)}));
      break;
    }
    case _ENC__ONEWAY_MSG__forwardCoverage_Foo_init:
    {
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Foo_init(_ctx, _this, methodTypeVars);
      break;
    }
    default:
    {
      printf("error, got invalid id: %zd", _m->id);
    }
  };
}


pony_type_t _enc__class__forwardCoverage_Foo_type = {.id=_ENC__ID__forwardCoverage_Foo, .size=sizeof(_enc__class__forwardCoverage_Foo_t), .trace=_enc__trace__forwardCoverage_Foo, .dispatch=_enc__dispatch__forwardCoverage_Foo, .vtable=trait_method_selector};
