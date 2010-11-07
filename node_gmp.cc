
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <obstack.h>

#include "node_gmp.h"


using namespace v8;
using namespace node;


Handle<Value>
GInt::New(const Arguments &args) {
  HandleScope scope;

  mpz_class i = 0;

  if (args[0]->IsNumber() || args[0]->IsString()) {
    String::Utf8Value val(args[0]->ToString());

    // truncate decimals
    char * num = strtok(*val, ".");

    try {
      i = num;
    } catch (std::invalid_argument err) {
      return ThrowException(Exception::Error(String::New("bad argument")));
    }
  } else if (!(args[0]->IsUndefined() || args[0]->IsNull())) {
    return ThrowException(Exception::Error(String::New("bad argument")));
  }

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

  if (args[0]->IsNumber() || args[0]->IsString()) {
    String::Utf8Value val(args[0]->ToString());

    // truncate decimals
    char * num = strtok(*val, ".");

    mpz_class i;

    try {
      i = num;
    } catch (std::invalid_argument err) {
      return ThrowException(Exception::Error(String::New("bad argument")));
    }

    GInt *self = ObjectWrap::Unwrap<GInt>(args.This());
    self->val_ += i;

  } else if (!(args[0]->IsUndefined() || args[0]->IsNull())) {
    return ThrowException(Exception::Error(String::New("bad argument")));
  }

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
  NODE_SET_PROTOTYPE_METHOD(t_int, "toString", GInt::ToString);

  target->Set(String::NewSymbol("Int"), t_int->GetFunction());

}

NODE_MODULE(gmp, RegisterModule);

