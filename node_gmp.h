
#ifndef __NODE_GMP_H__
#define __NODE_GMP_H__

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>

#include <gmp.h>
#include <gmpxx.h>


using namespace v8;


class GInt: public node::ObjectWrap {
  public:
    ~GInt();
    GInt(mpz_class num);
    static Handle<Value> Add(const Arguments &args);
    static Handle<Value> Sub(const Arguments &args);
    static Handle<Value> Mul(const Arguments &args);
    static Handle<Value> Div(const Arguments &args);
    static Handle<Value> ToString(const Arguments &args);

    static Handle<Value> New(const Arguments &args);

  private:
    mpz_class val_;
};

#endif // NODE_GMP_H
