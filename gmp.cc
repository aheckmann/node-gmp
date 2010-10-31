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

Handle<Value>
add(const Arguments &args) {
  HandleScope scope;
  if (args[0]->IsNumber() && args[1]->IsNumber()) {
    Local<Integer> res = Integer::New(args[0]->Int32Value() + args[1]->Int32Value());
    return scope.Close(res);
  } else {
    return ThrowException(Exception::Error(String::New("invalid argument error!")));
  }
}

extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;

  target->Set(String::New("version"), String::New(gmp_version));
  target->Set(String::New("str"), String::New("i am a string!"));
  target->Set(String::New("num"), Number::New(34));
  NODE_SET_METHOD(target, "add", add);
}
