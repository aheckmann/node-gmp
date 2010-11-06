
#ifndef __NODE_GMP_H__
#define __NODE_GMP_H__

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>

using namespace v8;


class GInt: public node::ObjectWrap {
  public:
    ~GInt();
    GInt(int num);
    static Handle<Value> Add(const Arguments &args);
    static Handle<Value> ToString(const Arguments &args);

    static Handle<Value> New(const Arguments &args);

  private:
    int val_;
};

#endif // NODE_GMP_H
