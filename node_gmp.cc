
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <obstack.h>

#include "node_gmp.h"


using namespace v8;
using namespace node;

#define GETARG(arg)                                                              \
  if (arg->IsNumber() || arg->IsString()) {                                      \
    String::Utf8Value val(arg->ToString());                                      \
    char * num = strtok(*val, ".");                                              \
    try {                                                                        \
      i = num;                                                                   \
    } catch (std::invalid_argument err) {                                        \
      return ThrowException(Exception::TypeError(String::New("bad argument")));  \
    }                                                                            \
  } else if (!(arg->IsUndefined() || arg->IsNull())) {                           \
    return ThrowException(Exception::TypeError(String::New("bad argument")));    \
  }


Handle<Value>
GInt::New(const Arguments &args) {
  HandleScope scope;

  mpz_class i = 0;

  GETARG(args[0]);

  GInt *g = new GInt(i);
  g->Wrap(args.This());
  return args.This();
}


GInt::GInt(mpz_class val): ObjectWrap() {
  val_ = val;
}

GInt::~GInt(){

}


Handle<Value>
GInt::Add(const Arguments &args) {
  HandleScope scope;

  mpz_class i = 0;

  GETARG(args[0]);

  GInt *self = ObjectWrap::Unwrap<GInt>(args.This());
  self->val_ += i;

  return args.This();
}

Handle<Value>
GInt::Sub(const Arguments &args) {
  HandleScope scope;

  mpz_class i = 0;

  GETARG(args[0]);

  GInt *self = ObjectWrap::Unwrap<GInt>(args.This());
  self->val_ -= i;

  return args.This();
}

Handle<Value>
GInt::Mul(const Arguments &args) {
  HandleScope scope;

  mpz_class i = 0;

  GETARG(args[0]);

  GInt *self = ObjectWrap::Unwrap<GInt>(args.This());
  self->val_ *= i;

  return args.This();
}

Handle<Value>
GInt::Div(const Arguments &args) {
  HandleScope scope;

  mpz_class i = 0;

  GETARG(args[0]);

  GInt *self = ObjectWrap::Unwrap<GInt>(args.This());
  self->val_ /= i;

  return args.This();
}

Handle<Value>
GInt::Pow(const Arguments &args) {
  HandleScope scope;

  if (!args[0]->IsNumber()) {
    return ThrowException(Exception::TypeError(String::New("exponent must be an int")));
  }

  GInt *self = ObjectWrap::Unwrap<GInt>(args.This());

  mpz_t c;
  mpz_init(c);

  mpz_pow_ui(c, self->val_.get_mpz_t(), (long)args[0]->Int32Value());

  self->val_ = mpz_class(c);

  mpz_clear(c);

  return args.This();
}

Handle<Value>
GInt::ToString(const Arguments &args) {
  HandleScope scope;

  GInt *self = ObjectWrap::Unwrap<GInt>(args.This());

  Local<String> str = String::New(self->val_.get_str(10).c_str());
  return scope.Close(str);
}



void RegisterModule(Handle<Object> target) {
  target->Set(String::NewSymbol("version"), String::New(gmp_version));

  //target->Set(String::NewSymbol("toHex"),   FunctionTemplate::New(ToHex)->GetFunction());

  Local<FunctionTemplate> t_int = FunctionTemplate::New(GInt::New);
  t_int->InstanceTemplate()->SetInternalFieldCount(1);
  t_int->SetClassName(String::NewSymbol("GInt"));

  NODE_SET_PROTOTYPE_METHOD(t_int, "add", GInt::Add);
  NODE_SET_PROTOTYPE_METHOD(t_int, "sub", GInt::Sub);
  NODE_SET_PROTOTYPE_METHOD(t_int, "mul", GInt::Mul);
  NODE_SET_PROTOTYPE_METHOD(t_int, "div", GInt::Div);
  NODE_SET_PROTOTYPE_METHOD(t_int, "pow", GInt::Pow);
  NODE_SET_PROTOTYPE_METHOD(t_int, "toString", GInt::ToString);

  target->Set(String::NewSymbol("Int"), t_int->GetFunction());

}

NODE_MODULE(gmp, RegisterModule);

