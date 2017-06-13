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


struct _enc__class__forwardCoverage_Main_t
{
  encore_actor_t _enc__actor;
};


void _enc__type_init__forwardCoverage_Main(_enc__class__forwardCoverage_Main_t* _this, ... )
{
  va_list params;
  va_start(params, _this);
  va_end(params);
}


void _enc__trace__forwardCoverage_Main(pony_ctx_t* _ctx_arg, void* p)
{
  pony_ctx_t** _ctx = (&(_ctx_arg));
  _enc__class__forwardCoverage_Main_t* _this = p;
}


_enc__class__forwardCoverage_Main_t* _enc__constructor__forwardCoverage_Main(pony_ctx_t** _ctx, pony_type_t** runtimeType)
{
  _enc__class__forwardCoverage_Main_t* _this = ((_enc__class__forwardCoverage_Main_t*) encore_create((*_ctx), (&(_enc__class__forwardCoverage_Main_type))));
  return _this;
}


void* _enc__method__forwardCoverage_Main_await(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "await");
  pony_type_t* _enc__type__t = (runtimeType[0]);
  future_await(_ctx, _enc__arg_f);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "await");
  return UNIT;
}


future_t* _enc__method__forwardCoverage_Main_await_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Main_await_t* msg = ((_enc__fut_msg__forwardCoverage_Main_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Main_await_t)), _ENC__FUT_MSG__forwardCoverage_Main_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Main_await_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f, future_t* _fut)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Main_await_t* msg = ((_enc__fut_msg__forwardCoverage_Main_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Main_await_t)), _ENC__FUT_MSG__forwardCoverage_Main_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Main_await_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Main_await_t* msg = ((_enc__oneway_msg__forwardCoverage_Main_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Main_await_t)), _ENC__ONEWAY_MSG__forwardCoverage_Main_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


void* _enc__method__forwardCoverage_Main_suspend(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "suspend");
  actor_suspend(_ctx);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "suspend");
  return UNIT;
}


future_t* _enc__method__forwardCoverage_Main_suspend_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Main_suspend_t* msg = ((_enc__fut_msg__forwardCoverage_Main_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Main_suspend_t)), _ENC__FUT_MSG__forwardCoverage_Main_suspend));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Main_suspend_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Main_suspend_t* msg = ((_enc__fut_msg__forwardCoverage_Main_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Main_suspend_t)), _ENC__FUT_MSG__forwardCoverage_Main_suspend));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Main_suspend_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Main_suspend_t* msg = ((_enc__oneway_msg__forwardCoverage_Main_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Main_suspend_t)), _ENC__ONEWAY_MSG__forwardCoverage_Main_suspend));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


void* _enc__method__forwardCoverage_Main_main(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType, array_t* _argv)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "main");
  /* do
  val foo = (new Foo)!foo()
  println("{}", get((new Foo)!multiChainWithExistingFuture(foo)))
  println("{}", get((new Foo)!multiChainWithId(foo)))
  println("{}", get((new Foo)!multiChainWithMethodCall()))
end */;
  check_receiver(_this, ".", "this", "init", "\"forwardCoverage.enc\" (line 32, column 5)");
  pony_type_t* _tmp_1[] = {};
  void* _sync_method_call_0 = _enc__method__forwardCoverage_Main_init(_ctx, _this, NULL);
  /* do
  val foo = (new Foo)!foo()
  println("{}", get((new Foo)!multiChainWithExistingFuture(foo)))
  println("{}", get((new Foo)!multiChainWithId(foo)))
  println("{}", get((new Foo)!multiChainWithMethodCall()))
end */;
  /* val foo = (new Foo)!foo() */;
  /* foo = (new Foo)!foo() */;
  _enc__class__forwardCoverage_Foo_t* _new_2 = _enc__constructor__forwardCoverage_Foo(_ctx, NULL);
  pony_type_t* _tmp_3[] = {};
  printf("HEY \n");
  _enc__type_init__forwardCoverage_Foo(_new_2);
  _enc__method__forwardCoverage_Foo_init_one_way(_ctx, _new_2, NULL);
  check_receiver(_new_2, " ! ", "new Foo()", "foo", "\"forwardCoverage.enc\" (line 29, column 25)");
  pony_type_t* _tmp_4[] = {};
  future_t* _fut_5 = _enc__method__forwardCoverage_Foo_foo_future(_ctx, _new_2, NULL);
  future_t* _foo_7 = _fut_5;
  /* println("{}", get((new Foo)!multiChainWithExistingFuture(foo))) */;
  printf("HEY \n");
  _enc__class__forwardCoverage_Foo_t* _new_8 = _enc__constructor__forwardCoverage_Foo(_ctx, NULL);
  pony_type_t* _tmp_9[] = {};
  _enc__type_init__forwardCoverage_Foo(_new_8);
  _enc__method__forwardCoverage_Foo_init_one_way(_ctx, _new_8, NULL);
  check_receiver(_new_8, " ! ", "new Foo()", "multiChainWithExistingFuture", "\"forwardCoverage.enc\" (line 30, column 33)");
  printf("HEY \n");
  pony_type_t* _tmp_10[] = {};
  future_t* _fut_11 = _enc__method__forwardCoverage_Foo_multiChainWithExistingFuture_future(_ctx, _new_8, NULL, _foo_7);
  printf("%d\n", _fut_11!=NULL);
  printf("%d\n",_fut_11->value.i);
  printf("%d\n",_fut_11->fulfilled);
  int64_t _tmp_12 = future_get_actor(_ctx, _fut_11).i;
  fprintf(stdout, "%lli\n", _tmp_12);
  printf("188\n");
  /* println("{}", get((new Foo)!multiChainWithId(foo))) */;
  _enc__class__forwardCoverage_Foo_t* _new_13 = _enc__constructor__forwardCoverage_Foo(_ctx, NULL);
  pony_type_t* _tmp_14[] = {};
  _enc__type_init__forwardCoverage_Foo(_new_13);
  printf("HEY \n");
  _enc__method__forwardCoverage_Foo_init_one_way(_ctx, _new_13, NULL);
  check_receiver(_new_13, " ! ", "new Foo()", "multiChainWithId", "\"forwardCoverage.enc\" (line 31, column 33)");
  pony_type_t* _tmp_15[] = {};
  future_t* _fut_16 = _enc__method__forwardCoverage_Foo_multiChainWithId_future(_ctx, _new_13, NULL, _foo_7);
  int64_t _tmp_17 = future_get_actor(_ctx, _fut_16).i;
  fprintf(stdout, "%lli\n", _tmp_17);
  /* println("{}", get((new Foo)!multiChainWithMethodCall())) */;
  printf("HEY \n");
  _enc__class__forwardCoverage_Foo_t* _new_18 = _enc__constructor__forwardCoverage_Foo(_ctx, NULL);
  pony_type_t* _tmp_19[] = {};
  _enc__type_init__forwardCoverage_Foo(_new_18);
  _enc__method__forwardCoverage_Foo_init_one_way(_ctx, _new_18, NULL);
  check_receiver(_new_18, " ! ", "new Foo()", "multiChainWithMethodCall", "\"forwardCoverage.enc\" (line 32, column 33)");
  pony_type_t* _tmp_20[] = {};
  future_t* _fut_21 = _enc__method__forwardCoverage_Foo_multiChainWithMethodCall_future(_ctx, _new_18, NULL);
  int64_t _tmp_22 = future_get_actor(_ctx, _fut_21).i;
  fprintf(stdout, "%lli\n", _tmp_22);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "main");
  return UNIT;
}


future_t* _enc__method__forwardCoverage_Main_main_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Main_main_t* msg = ((_enc__fut_msg__forwardCoverage_Main_main_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Main_main_t)), _ENC__FUT_MSG__forwardCoverage_Main_main));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Main_main_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Main_main_t* msg = ((_enc__fut_msg__forwardCoverage_Main_main_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Main_main_t)), _ENC__FUT_MSG__forwardCoverage_Main_main));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Main_main_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Main_main_t* msg = ((_enc__oneway_msg__forwardCoverage_Main_main_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Main_main_t)), _ENC__ONEWAY_MSG__forwardCoverage_Main_main));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


void* _enc__method__forwardCoverage_Main_init(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "init");
  /* () */;
  UNIT;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "init");
  return UNIT;
}


future_t* _enc__method__forwardCoverage_Main_init_future(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Main_init_t* msg = ((_enc__fut_msg__forwardCoverage_Main_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Main_init_t)), _ENC__FUT_MSG__forwardCoverage_Main_init));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardCoverage_Main_init_forward(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardCoverage_Main_init_t* msg = ((_enc__fut_msg__forwardCoverage_Main_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardCoverage_Main_init_t)), _ENC__FUT_MSG__forwardCoverage_Main_init));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardCoverage_Main_init_one_way(pony_ctx_t** _ctx, _enc__class__forwardCoverage_Main_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardCoverage_Main_init_t* msg = ((_enc__oneway_msg__forwardCoverage_Main_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardCoverage_Main_init_t)), _ENC__ONEWAY_MSG__forwardCoverage_Main_init));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


static void _enc__dispatch__forwardCoverage_Main(pony_ctx_t** _ctx, pony_actor_t* _a, pony_msg_t* _m)
{
  _enc__class__forwardCoverage_Main_t* _this = ((_enc__class__forwardCoverage_Main_t*) _a);
  switch (_m->id)
  {
    case _ENC__MSG_MAIN:
    {
      pony_main_msg_t* msg = ((pony_main_msg_t*) _m);
      _enc__method__forwardCoverage_Main_main(_ctx, ((_enc__class__forwardCoverage_Main_t*) _a), NULL, _init_argv(_ctx, msg->argc, msg->argv));
      break;
    }
    case _ENC__FUT_MSG__forwardCoverage_Main_await:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      pony_type_t* _enc__type__t = ((_enc__fut_msg__forwardCoverage_Main_await_t*) _m)->_enc__type__t;
      future_t* _enc__arg_f = ((_enc__fut_msg__forwardCoverage_Main_await_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_f, future_trace);
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {_enc__type__t};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__forwardCoverage_Main_await(_ctx, _this, methodTypeVars, _enc__arg_f)}));
      break;
    }
    case _ENC__ONEWAY_MSG__forwardCoverage_Main_await:
    {
      pony_type_t* _enc__type__t = ((_enc__oneway_msg__forwardCoverage_Main_await_t*) _m)->_enc__type__t;
      future_t* _enc__arg_f = ((_enc__oneway_msg__forwardCoverage_Main_await_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_f, future_trace);
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {_enc__type__t};
      _enc__method__forwardCoverage_Main_await(_ctx, _this, methodTypeVars, _enc__arg_f);
      break;
    }
    case _ENC__FUT_MSG__forwardCoverage_Main_suspend:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__forwardCoverage_Main_suspend(_ctx, _this, methodTypeVars)}));
      break;
    }
    case _ENC__ONEWAY_MSG__forwardCoverage_Main_suspend:
    {
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Main_suspend(_ctx, _this, methodTypeVars);
      break;
    }
    case _ENC__FUT_MSG__forwardCoverage_Main_init:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__forwardCoverage_Main_init(_ctx, _this, methodTypeVars)}));
      break;
    }
    case _ENC__ONEWAY_MSG__forwardCoverage_Main_init:
    {
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardCoverage_Main_init(_ctx, _this, methodTypeVars);
      break;
    }
    default:
    {
      printf("error, got invalid id: %zd", _m->id);
    }
  };
}


pony_type_t _enc__class__forwardCoverage_Main_type = {.id=_ENC__ID__forwardCoverage_Main, .size=sizeof(_enc__class__forwardCoverage_Main_t), .trace=_enc__trace__forwardCoverage_Main, .dispatch=_enc__dispatch__forwardCoverage_Main, .vtable=trait_method_selector};
