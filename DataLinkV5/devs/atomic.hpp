#pragma once
#include"typedef.hpp"

#include"../utility/utility.hpp"
#include<Adevs/adevs.h>

namespace devs {
  class AtomicAbstract :
    public adevs::Atomic<IO_Type, TimeType>
  {
  public:
    AtomicAbstract(Digraph& _digraph, const std::string&_name, uint64_t _uid)
      :name(_name),
      digraph(_digraph),
      uid(_uid)
    {
      _digraph.add(this);
    }
    // 通过 Atomic 继承
    virtual void delta_int() = 0;
    virtual void delta_ext(devs::TimeType e, const IO_Bag& xb) = 0;
    virtual void output_func(IO_Bag& yb) = 0;
    virtual devs::TimeType ta() = 0;

  public:
    Digraph & digraph;

  public:
    const std::string  name;
    const uint64_t    uid;
  public:
    virtual inline void gc_output(IO_Bag& g) override
    {
      //解除 虚方法.
    };

    virtual inline void delta_conf(const IO_Bag& xb) override
    {
      delta_int();
      delta_ext(0, xb);
    };

  };

}