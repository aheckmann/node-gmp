
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <obstack.h>
#include <gmp.h>
#include <gmpxx.h>

#include "node_gmp.h"

using namespace v8;
using namespace node;



Handle<Value>
GInt::New(const Arguments &args) {
  HandleScope scope;

  int i = 0;

  if (args[0]->IsNumber() || args[0]->IsString()) {
    i = args[0]->Uint32Value();
  }

  GInt *g = new GInt(i);
  g->Wrap(args.This());
  return args.This();
}


GInt::GInt(int val): ObjectWrap() {
  val_ = val;
}

GInt::~GInt(){

}


Handle<Value>
GInt::Add(const Arguments &args) {
  HandleScope scope;


  int i = 0;

  if (args[0]->IsNumber() || args[0]->IsString()) {
    i = args[0]->Uint32Value();
  }

  GInt *self = ObjectWrap::Unwrap<GInt>(args.This());

  // todo check for size limitiations?
  // nah, this will be a mpz_t
  self->val_ += i;

  return args.This();
}

Handle<Value>
GInt::ToString(const Arguments &args) {
  HandleScope scope;

  GInt *self = ObjectWrap::Unwrap<GInt>(args.This());

  Handle<Value> val = Integer::New(self->val_);
  return scope.Close(val->ToString());
}



void RegisterModule(Handle<Object> target) {
  target->Set(String::NewSymbol("version"), String::New(gmp_version));

  //target->Set(String::NewSymbol("toHex"),   FunctionTemplate::New(ToHex)->GetFunction());

  Local<FunctionTemplate> t_int = FunctionTemplate::New(GInt::New);
  t_int->InstanceTemplate()->SetInternalFieldCount(1);
  t_int->SetClassName(String::NewSymbol("GInt"));

  NODE_SET_PROTOTYPE_METHOD(t_int, "add", GInt::Add);
  NODE_SET_PROTOTYPE_METHOD(t_int, "toString", GInt::ToString);

  target->Set(String::NewSymbol("Int"), t_int->GetFunction());

}

NODE_MODULE(gmp, RegisterModule);

