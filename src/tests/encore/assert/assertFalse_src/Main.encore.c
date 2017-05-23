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


struct _enc__active__assertFalse_Main_t
{
  encore_actor_t _enc__actor;
};


void _enc__type_init__assertFalse_Main(_enc__active__assertFalse_Main_t* _this, ... )
{
  va_list params;
  va_start(params, _this);
  va_end(params);
}


void _enc__trace__assertFalse_Main(pony_ctx_t* _ctx_arg, void* p)
{
  pony_ctx_t** _ctx = (&(_ctx_arg));
  _enc__active__assertFalse_Main_t* _this = p;
}


_enc__active__assertFalse_Main_t* _enc__constructor__assertFalse_Main(pony_ctx_t** _ctx, pony_type_t** runtimeType)
{
  _enc__active__assertFalse_Main_t* _this = ((_enc__active__assertFalse_Main_t*) encore_create((*_ctx), (&(_enc__active__assertFalse_Main_type))));
  return _this;
}


void* _enc__method__assertFalse_Main_init(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "init");
  UNIT;
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "init");
  return UNIT;
}


future_t* _enc__method__assertFalse_Main_init_future(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__assertFalse_Main_init_t* msg = ((_enc__fut_msg__assertFalse_Main_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__assertFalse_Main_init_t)), _ENC__FUT_MSG__assertFalse_Main_init));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__assertFalse_Main_init_forward(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__assertFalse_Main_init_t* msg = ((_enc__fut_msg__assertFalse_Main_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__assertFalse_Main_init_t)), _ENC__FUT_MSG__assertFalse_Main_init));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__assertFalse_Main_init_one_way(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__assertFalse_Main_init_t* msg = ((_enc__oneway_msg__assertFalse_Main_init_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__assertFalse_Main_init_t)), _ENC__ONEWAY_MSG__assertFalse_Main_init));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


void* _enc__method__assertFalse_Main_await(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "await");
  pony_type_t* _enc__type__t = (runtimeType[0]);
  future_await(_ctx, _enc__arg_f);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "await");
  return UNIT;
}


future_t* _enc__method__assertFalse_Main_await_future(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__assertFalse_Main_await_t* msg = ((_enc__fut_msg__assertFalse_Main_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__assertFalse_Main_await_t)), _ENC__FUT_MSG__assertFalse_Main_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__assertFalse_Main_await_forward(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f, future_t* _fut)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__assertFalse_Main_await_t* msg = ((_enc__fut_msg__assertFalse_Main_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__assertFalse_Main_await_t)), _ENC__FUT_MSG__assertFalse_Main_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__assertFalse_Main_await_one_way(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType, future_t* _enc__arg_f)
{
  pony_type_t* _enc__type__t = (runtimeType[0]);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _enc__arg_f, future_trace);
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__assertFalse_Main_await_t* msg = ((_enc__oneway_msg__assertFalse_Main_await_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__assertFalse_Main_await_t)), _ENC__ONEWAY_MSG__assertFalse_Main_await));
  msg->f1 = _enc__arg_f;
  msg->_enc__type__t = _enc__type__t;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


void* _enc__method__assertFalse_Main_suspend(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "suspend");
  actor_suspend(_ctx);
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "suspend");
  return UNIT;
}


future_t* _enc__method__assertFalse_Main_suspend_future(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__assertFalse_Main_suspend_t* msg = ((_enc__fut_msg__assertFalse_Main_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__assertFalse_Main_suspend_t)), _ENC__FUT_MSG__assertFalse_Main_suspend));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__assertFalse_Main_suspend_forward(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__assertFalse_Main_suspend_t* msg = ((_enc__fut_msg__assertFalse_Main_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__assertFalse_Main_suspend_t)), _ENC__FUT_MSG__assertFalse_Main_suspend));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__assertFalse_Main_suspend_one_way(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__assertFalse_Main_suspend_t* msg = ((_enc__oneway_msg__assertFalse_Main_suspend_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__assertFalse_Main_suspend_t)), _ENC__ONEWAY_MSG__assertFalse_Main_suspend));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


void* _enc__method__assertFalse_Main_main(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType, array_t* _argv)
{
  ENC_DTRACE3(METHOD_ENTRY, (uintptr_t)*_ctx, (uintptr_t)_this, "main");
  /* assertFalse(false) */;
  void* _ite_0;
  if (({int64_t _literal_1 = 0/*False*/; _literal_1;}))
  {
    /* print("Assertion failed at \"assertFalse.enc\" (line 5, column 5):\nassertFalse(false)\n") */;
    fprintf(stderr, "Assertion failed at \"assertFalse.enc\" (line 5, column 5):\nassertFalse(false)\n");
    /* exit(1) */;
    int64_t _literal_2 = 1;
    exit(_literal_2);
    _ite_0 = ((void*) UNIT);
  }
  else
  {
    UNIT;
    _ite_0 = ((void*) UNIT);
  };
  /* assertFalse(true, "Kingfisher") */;
  void* _ite_3;
  if (({int64_t _literal_4 = 1/*True*/; _literal_4;}))
  {
    /* print("Assertion failed at \"assertFalse.enc\" (line 6, column 5):\n") */;
    fprintf(stderr, "Assertion failed at \"assertFalse.enc\" (line 6, column 5):\n");
    /* print("Kingfisher") */;
    fprintf(stderr, "Kingfisher");
    /* print("\n") */;
    fprintf(stderr, "\n");
    /* exit(1) */;
    int64_t _literal_5 = 1;
    exit(_literal_5);
    _ite_3 = ((void*) UNIT);
  }
  else
  {
    UNIT;
    _ite_3 = ((void*) UNIT);
  };
  ENC_DTRACE3(METHOD_EXIT, (uintptr_t)*_ctx, (uintptr_t)_this, "main");
  return UNIT;
}


future_t* _enc__method__assertFalse_Main_main_future(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType)
{
  future_t* _fut = future_mk(_ctx, ENCORE_PRIMITIVE);
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__assertFalse_Main_main_t* msg = ((_enc__fut_msg__assertFalse_Main_main_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__assertFalse_Main_main_t)), _ENC__FUT_MSG__assertFalse_Main_main));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


future_t* _enc__method__assertFalse_Main_main_forward(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType, future_t* _fut)
{
  pony_gc_send((*_ctx));
  encore_trace_object((*_ctx), _fut, future_trace);
  pony_send_done((*_ctx));
  _enc__fut_msg__assertFalse_Main_main_t* msg = ((_enc__fut_msg__assertFalse_Main_main_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__fut_msg__assertFalse_Main_main_t)), _ENC__FUT_MSG__assertFalse_Main_main));
  msg->_fut = _fut;
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
  return _fut;
}


void _enc__method__assertFalse_Main_main_one_way(pony_ctx_t** _ctx, _enc__active__assertFalse_Main_t* _this, pony_type_t** runtimeType)
{
  pony_gc_send((*_ctx));
  /* No tracing future for oneway msg */;
  pony_send_done((*_ctx));
  _enc__oneway_msg__assertFalse_Main_main_t* msg = ((_enc__oneway_msg__assertFalse_Main_main_t*) pony_alloc_msg(POOL_INDEX(sizeof(_enc__oneway_msg__assertFalse_Main_main_t)), _ENC__ONEWAY_MSG__assertFalse_Main_main));
  pony_sendv((*_ctx), ((pony_actor_t*) _this), ((pony_msg_t*) msg));
}


static void _enc__dispatch__assertFalse_Main(pony_ctx_t** _ctx, pony_actor_t* _a, pony_msg_t* _m)
{
  _enc__active__assertFalse_Main_t* _this = ((_enc__active__assertFalse_Main_t*) _a);
  switch (_m->id)
  {
    case _ENC__MSG_MAIN:
    {
      pony_main_msg_t* msg = ((pony_main_msg_t*) _m);
      _enc__method__assertFalse_Main_main(_ctx, ((_enc__active__assertFalse_Main_t*) _a), NULL, _init_argv(_ctx, msg->argc, msg->argv));
      break;
    }
    case _ENC__FUT_MSG__assertFalse_Main_init:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__assertFalse_Main_init(_ctx, _this, methodTypeVars)}));
      break;
    }
    case _ENC__ONEWAY_MSG__assertFalse_Main_init:
    {
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__assertFalse_Main_init(_ctx, _this, methodTypeVars);
      break;
    }
    case _ENC__FUT_MSG__assertFalse_Main_await:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      pony_type_t* _enc__type__t = ((_enc__fut_msg__assertFalse_Main_await_t*) _m)->_enc__type__t;
      future_t* _enc__arg_f = ((_enc__fut_msg__assertFalse_Main_await_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_f, future_trace);
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {_enc__type__t};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__assertFalse_Main_await(_ctx, _this, methodTypeVars, _enc__arg_f)}));
      break;
    }
    case _ENC__ONEWAY_MSG__assertFalse_Main_await:
    {
      pony_type_t* _enc__type__t = ((_enc__oneway_msg__assertFalse_Main_await_t*) _m)->_enc__type__t;
      future_t* _enc__arg_f = ((_enc__oneway_msg__assertFalse_Main_await_t*) _m)->f1;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _enc__arg_f, future_trace);
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {_enc__type__t};
      _enc__method__assertFalse_Main_await(_ctx, _this, methodTypeVars, _enc__arg_f);
      break;
    }
    case _ENC__FUT_MSG__assertFalse_Main_suspend:
    {
      future_t* _fut = ((encore_fut_msg_t*) _m)->_fut;
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      encore_trace_object((*_ctx), _fut, future_type.trace);
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      future_fulfil(_ctx, _fut, ((encore_arg_t) {.p = _enc__method__assertFalse_Main_suspend(_ctx, _this, methodTypeVars)}));
      break;
    }
    case _ENC__ONEWAY_MSG__assertFalse_Main_suspend:
    {
      
      // --- GC on receive ----------------------------------------;
      pony_gc_recv((*_ctx));
      /* Not tracing the future in a oneWay send */;
      pony_recv_done((*_ctx));
      // --- GC on receive ----------------------------------------;
      
      pony_type_t* methodTypeVars[] = {};
      _enc__method__assertFalse_Main_suspend(_ctx, _this, methodTypeVars);
      break;
    }
    default:
    {
      printf("error, got invalid id: %zd", _m->id);
    }
  };
}


pony_type_t _enc__active__assertFalse_Main_type = {.id=_ENC__ID__assertFalse_Main, .size=sizeof(_enc__active__assertFalse_Main_t), .trace=_enc__trace__assertFalse_Main, .dispatch=_enc__dispatch__assertFalse_Main, .vtable=trait_method_selector};
