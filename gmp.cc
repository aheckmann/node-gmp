#include <math.h>
#include <string.h>
#include <v8.h>
#include <node.h>

#include <stdio.h>
#include <stdarg.h>
#include <obstack.h>
#include <gmp.h>
#include <gmpxx.h>

using namespace v8;
using namespace node;

// http://github.com/embedthis/packages/blob/a0123bc7a4728dd1b4eec012d46f2bf45ae3c8f0/php/php-5.3.2/ext/gmp/gmp.c







const char * gettype(const Arguments &args){
  const char * ret = "";

  if (args[0]->IsUndefined()){
    ret = "undefined";

  } else if (args[0]->IsString()){
    ret = "string";

  } else if (args[0]->IsFunction()){
    ret = "function";

  } else if (args[0]->IsUint32()){
    ret = "uint32";

  } else if (args[0]->IsInt32()){
    ret = "int32";

  } else if (args[0]->IsArray()){
    ret = "array";

  } else if (args[0]->IsBoolean()){
    ret = "boolean";

  } else if (args[0]->IsNull()){
    ret = "null";

  } else if (args[0]->IsRegExp()){
    ret = "regexp";

  } else if (args[0]->IsObject()){
    ret = "object";

  } else if (args[0]->IsNumber()){
    ret = "number";
  }

  return ret;
}



Handle<Value>
getType(const Arguments &args){
  HandleScope scope;
  Local<String> res = String::New(gettype(args));
  return scope.Close(res);
}

Handle<Value>
noop(const Arguments &args) {
  return Undefined();
}

Handle<Value>
ex(Handle<String> msg = String::New("invalid argument")) {
  return ThrowException(Exception::Error(msg));
}



Handle<String> getArg(Handle<Value> arg) {
  if ( arg->IsUint32() || arg->IsInt32() ) {
    return arg->ToString();
  }
  if (arg->IsString()) {
    // handle decimals
    return arg->ToString();
  }
  ex();
}

mpz_class getmpz(Handle<Value> arg) {
  if (arg->IsUint32() || arg->IsInt32() || arg->IsNumber() || arg->IsString()) {
    String::Utf8Value val(arg);

    // truncate decimals
    char * num = strtok(*val, ".");

    mpz_class a(num, 10);

    return a;
  }

  throw "invalid argument";
}



Handle<Value>
add(const Arguments &args) {
  HandleScope scope;
  mpz_class c;

  try {
    c = getmpz(args[0]) + getmpz(args[1]);
  } catch (const char * err) {
    return ex(String::New(err));
  }

  Local<String> res = String::New(c.get_str(10).c_str());
  return scope.Close(res);
}

Handle<Value>
sub(const Arguments &args) {
  HandleScope scope;
  mpz_class c;

  try {
    c = getmpz(args[0]) - getmpz(args[1]);
  } catch (const char * err) {
    return ex(String::New(err));
  }

  Local<String> res = String::New(c.get_str(10).c_str());
  return scope.Close(res);
}

Handle<Value>
mul(const Arguments &args) {
  HandleScope scope;
  mpz_class c;

  try {
    c = getmpz(args[0]) * getmpz(args[1]);
  } catch (const char * err) {
    return ex(String::New(err));
  }

  Local<String> res = String::New(c.get_str(10).c_str());
  return scope.Close(res);
}

Handle<Value>
div(const Arguments &args) {
  HandleScope scope;
  mpz_class c;

  try {
    c = getmpz(args[0]) / getmpz(args[1]);
  } catch (const char * err) {
    return ex(String::New(err));
  }

  Local<String> res = String::New(c.get_str(10).c_str());
  return scope.Close(res);
}

Handle<Value>
mod(const Arguments &args) {
  HandleScope scope;
  mpz_class c;

  try {
    c = getmpz(args[0]) % getmpz(args[1]);
  } catch (const char * err) {
    return ex(String::New(err));
  }

  Local<String> res = String::New(c.get_str(10).c_str());
  return scope.Close(res);
}



extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;

  target->Set(String::New("version"), String::New(gmp_version));
  //target->Set(String::New("str"), String::New("i am a string!"));
  //target->Set(String::New("num"), Number::New(34));
  NODE_SET_METHOD(target, "add", add);
  NODE_SET_METHOD(target, "sub", sub);
  NODE_SET_METHOD(target, "mul", mul);
  NODE_SET_METHOD(target, "div", div);
  NODE_SET_METHOD(target, "mod", mod);
  NODE_SET_METHOD(target, "longToBinary", noop);
  NODE_SET_METHOD(target, "binaryToLong", noop);
  NODE_SET_METHOD(target, "base64ToLong", noop);
  NODE_SET_METHOD(target, "rand", noop);
  NODE_SET_METHOD(target, "pow", noop);
  NODE_SET_METHOD(target, "cmp", noop);
  NODE_SET_METHOD(target, "powmod", noop);

  // testing
  NODE_SET_METHOD(target, "type", getType);
}

