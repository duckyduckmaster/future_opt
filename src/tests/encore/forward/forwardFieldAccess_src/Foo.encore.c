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


struct _enc__class__forwardFieldAccess_Foo_t
{
  encore_actor_t _enc__actor;
  future_t* _enc__field_result;
};


void _enc__type_init__forwardFieldAccess_Foo(_enc__class__forwardFieldAccess_Foo_t* _this, ... )
{
  va_list params;
  va_start(params, _this);
  va_end(params);
}


void _enc__trace__forwardFieldAccess_Foo(pony_ctx_t* _ctx_arg, void* p)
{
  pony_ctx_t** _ctx = (&(_ctx_arg));
  _enc__class__forwardFieldAccess_Foo_t* _this = p;
  future_t* _enc__field_result = _this->_enc__field_result;
  encore_trace_object((*_ctx), _enc__field_result, future_trace);
}


_enc__class__forwardFieldAccess_Foo_t* _enc__constructor__forwardFieldAccess_Foo(pony_ctx_t** _ctx, pony_type_t** runtimeType)
{
  _enc__class__forwardFieldAccess_Foo_t* _this = ((_enc__class__forwardFieldAccess_Foo_t*) encore_create((*_ctx), (&(_enc__class__forwardFieldAccess_Foo_type))));
  return _this;
}


void* _enc__method__forwardFieldAccess_Foo_await(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "await");
  pony_type_t* _enc__type__t = (runtimeType[0]);
  future_await(_ctx, _enc__arg_f);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "await");
  return UNIT;
}


future_t* _enc__method__forwardFieldAccess_Foo_await_future(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardFieldAccess_Foo_await_t* msg = ((_enc__fut_msg__forwardFieldAccess_Foo_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardFieldAccess_Foo_await_t)), _ENC__FUT_MSG__forwardFieldAccess_Foo_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardFieldAccess_Foo_await_forward(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f, future_t* _fut)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardFieldAccess_Foo_await_t* msg = ((_enc__fut_msg__forwardFieldAccess_Foo_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardFieldAccess_Foo_await_t)), _ENC__FUT_MSG__forwardFieldAccess_Foo_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardFieldAccess_Foo_await_one_way(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardFieldAccess_Foo_await_t* msg = ((_enc__oneway_msg__forwardFieldAccess_Foo_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardFieldAccess_Foo_await_t)), _ENC__ONEWAY_MSG__forwardFieldAccess_Foo_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


void* _enc__method__forwardFieldAccess_Foo_suspend(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "suspend");
  actor_suspend(_ctx);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "suspend");
  return UNIT;
}


future_t* _enc__method__forwardFieldAccess_Foo_suspend_future(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardFieldAccess_Foo_suspend_t* msg = ((_enc__fut_msg__forwardFieldAccess_Foo_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardFieldAccess_Foo_suspend_t)), _ENC__FUT_MSG__forwardFieldAccess_Foo_suspend));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardFieldAccess_Foo_suspend_forward(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardFieldAccess_Foo_suspend_t* msg = ((_enc__fut_msg__forwardFieldAccess_Foo_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardFieldAccess_Foo_suspend_t)), _ENC__FUT_MSG__forwardFieldAccess_Foo_suspend));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardFieldAccess_Foo_suspend_one_way(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardFieldAccess_Foo_suspend_t* msg = ((_enc__oneway_msg__forwardFieldAccess_Foo_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardFieldAccess_Foo_suspend_t)), _ENC__ONEWAY_MSG__forwardFieldAccess_Foo_suspend));
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
  int64_t _enc__arg__id_fun_tmp = (_args[0]).i;
  ENC_DTRACE1(CLOSURE_EXIT, (uintptr_t)*_ctx);
  return ((encore_arg_t) {.i = _enc__arg__id_fun_tmp});
}


int64_t _enc__method__forwardFieldAccess_Foo_foo_arg(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "foo_arg");
  ENC_DTRACE3(FIELD_ACCESS, (uintptr_t)*_ctx, (uintptr_t)_this, "result");
  future_t* _fieldacc_0 = (*_this)._enc__field_result;
  struct _enc__env_closure0* _enc__env_closure0 = encore_alloc((*_ctx), sizeof(struct _enc__env_closure0));
  closure_t* _tmp_1 = closure_mk(_ctx, _enc__closure_fun_closure0, _enc__env_closure0, _enc__trace_closure0, NULL);
  future_t* _tmp_3 = future_chain_actor(_ctx, _fieldacc_0, ENCORE_PRIMITIVE, _tmp_1);
  int64_t _tmp_2 = future_get_actor(_ctx, _tmp_3).i;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "foo_arg");
  return ((int64_t) _tmp_2);
}


void _enc__method__forwardFieldAccess_Foo_foo_arg_async(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "foo_arg");
  ENC_DTRACE3(FIELD_ACCESS, (uintptr_t)*_ctx, (uintptr_t)_this, "result");
  future_t* _fieldacc_0 = (*_this)._enc__field_result;
  struct _enc__env_closure0* _enc__env_closure0 = encore_alloc((*_ctx), sizeof(struct _enc__env_closure0));
  closure_t* _tmp_1 = closure_mk(_ctx, _enc__closure_fun_closure0, _enc__env_closure0, _enc__trace_closure0, NULL);
  future_chain_forward(_ctx, _fieldacc_0, ENCORE_PRIMITIVE, _tmp_1, _fut);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "foo_arg");
  return;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "foo_arg");
  if (_fut)
  {
    future_fulfil(_ctx, _fut, ((encore_arg_t) {.i = ((int64_t) UNIT)}));
  }
  else
  {
  };
}


future_t* _enc__method__forwardFieldAccess_Foo_foo_arg_future(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardFieldAccess_Foo_foo_arg_t* msg = ((_enc__fut_msg__forwardFieldAccess_Foo_foo_arg_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardFieldAccess_Foo_foo_arg_t)), _ENC__FUT_MSG__forwardFieldAccess_Foo_foo_arg));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardFieldAccess_Foo_foo_arg_forward(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardFieldAccess_Foo_foo_arg_t* msg = ((_enc__fut_msg__forwardFieldAccess_Foo_foo_arg_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardFieldAccess_Foo_foo_arg_t)), _ENC__FUT_MSG__forwardFieldAccess_Foo_foo_arg));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardFieldAccess_Foo_foo_arg_one_way(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardFieldAccess_Foo_foo_arg_t* msg = ((_enc__oneway_msg__forwardFieldAccess_Foo_foo_arg_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardFieldAccess_Foo_foo_arg_t)), _ENC__ONEWAY_MSG__forwardFieldAccess_Foo_foo_arg));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


void* _enc__method__forwardFieldAccess_Foo_init(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "init");
  /* this.result = arg */;
  (*({ENC_DTRACE3(FIELD_WRITE, (uintptr_t)*_ctx, (uintptr_t)_this, "result"); _this;}))._enc__field_result = _enc__arg_arg;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "init");
  return UNIT;
}


future_t* _enc__method__forwardFieldAccess_Foo_init_future(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardFieldAccess_Foo_init_t* msg = ((_enc__fut_msg__forwardFieldAccess_Foo_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardFieldAccess_Foo_init_t)), _ENC__FUT_MSG__forwardFieldAccess_Foo_init));
  msg->f1 = _enc__arg_arg;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__forwardFieldAccess_Foo_init_forward(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__forwardFieldAccess_Foo_init_t* msg = ((_enc__fut_msg__forwardFieldAccess_Foo_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__forwardFieldAccess_Foo_init_t)), _ENC__FUT_MSG__forwardFieldAccess_Foo_init));
  msg->f1 = _enc__arg_arg;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__forwardFieldAccess_Foo_init_one_way(pony_ctx_t** _ctx, _enc__class__forwardFieldAccess_Foo_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_arg)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__forwardFieldAccess_Foo_init_t* msg = ((_enc__oneway_msg__forwardFieldAccess_Foo_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__forwardFieldAccess_Foo_init_t)), _ENC__ONEWAY_MSG__forwardFieldAccess_Foo_init));
  msg->f1 = _enc__arg_arg;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


static void _enc__dispatch__forwardFieldAccess_Foo(pony_ctx_t** _ctx, pony_actor_t* _a, pony_msg_t* _m)
{
  _enc__class__forwardFieldAccess_Foo_t* _this = ((_enc__class__forwardFieldAccess_Foo_t*) _a);
  switch (_m->id)
  {
    case _ENC__FUT_MSG__forwardFieldAccess_Foo_await:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      pony_type_t* _enc__type__t = ((_enc__fut_msg__forwardFieldAccess_Foo_await_t*) _m)->_enc__type__t;
      future_t* _enc__arg_f = ((_enc__fut_msg__forwardFieldAccess_Foo_await_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_f, future_trace);
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {_enc__type__t};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__forwardFieldAccess_Foo_await(_ctx, _this, methodTypeVars, _enc__arg_f)}));
      break;
    }
    case _ENC__ONEWAY_MSG__forwardFieldAccess_Foo_await:
    {
      pony_type_t* _enc__type__t = ((_enc__oneway_msg__forwardFieldAccess_Foo_await_t*) _m)->_enc__type__t;
      future_t* _enc__arg_f = ((_enc__oneway_msg__forwardFieldAccess_Foo_await_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_f, future_trace);
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {_enc__type__t};
      _enc__method__forwardFieldAccess_Foo_await(_ctx, _this, methodTypeVars, _enc__arg_f);
      break;
    }
    case _ENC__FUT_MSG__forwardFieldAccess_Foo_suspend:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__forwardFieldAccess_Foo_suspend(_ctx, _this, methodTypeVars)}));
      break;
    }
    case _ENC__ONEWAY_MSG__forwardFieldAccess_Foo_suspend:
    {
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardFieldAccess_Foo_suspend(_ctx, _this, methodTypeVars);
      break;
    }
    case _ENC__FUT_MSG__forwardFieldAccess_Foo_foo_arg:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardFieldAccess_Foo_foo_arg_async(_ctx, _this, methodTypeVars, _fut);
      break;
    }
    case _ENC__ONEWAY_MSG__forwardFieldAccess_Foo_foo_arg:
    {
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardFieldAccess_Foo_foo_arg_async(_ctx, _this, methodTypeVars, NULL);
      break;
    }
    case _ENC__FUT_MSG__forwardFieldAccess_Foo_init:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      future_t* _enc__arg_arg = ((_enc__fut_msg__forwardFieldAccess_Foo_init_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__forwardFieldAccess_Foo_init(_ctx, _this, methodTypeVars, _enc__arg_arg)}));
      break;
    }
    case _ENC__ONEWAY_MSG__forwardFieldAccess_Foo_init:
    {
      future_t* _enc__arg_arg = ((_enc__oneway_msg__forwardFieldAccess_Foo_init_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_arg, future_trace);
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__forwardFieldAccess_Foo_init(_ctx, _this, methodTypeVars, _enc__arg_arg);
      break;
    }
    default:
    {
      printf("error, got invalid id: %zd", _m->id);
    }
  };
}


pony_type_t _enc__class__forwardFieldAccess_Foo_type = {.id=_ENC__ID__forwardFieldAccess_Foo, .size=sizeof(_enc__class__forwardFieldAccess_Foo_t), .trace=_enc__trace__forwardFieldAccess_Foo, .dispatch=_enc__dispatch__forwardFieldAccess_Foo, .vtable=trait_method_selector};
