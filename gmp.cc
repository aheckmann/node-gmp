#include <v8.h>
#include <math.h>
#include <string.h>
#include <node.h>

using namespace v8;
using namespace node;

Handle<Value>
add(const Arguments &args) {
  HandleScope scope;
  if (args[0]->IsNumber() && args[1]->IsNumber()) {
    Local<Integer> res = Integer::New(args[0]->Int32Value() + args[1]->Int32Value());
    return scope.Close(res);
  }
}

extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::New("str"), String::New("i am a string!"));
  target->Set(String::New("num"), Number::New(34));
  target->Set(String::New("add"), FunctionTemplate::New(add)->GetFunction());
}
