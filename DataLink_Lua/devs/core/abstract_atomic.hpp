#pragma once
#include<Adevs/adevs.h>
#include"typedef.hpp"

#include"../../utility/uid.hpp"
namespace devs {
  class AbstractAtomic :
    public adevs::Atomic<IO_Type , TimeType>
  {
  public:
    AbstractAtomic(Digraph& _digraph,const std::string& _name ) :digraph(_digraph),name(_name){}

  public:
    Digraph &digraph;
    const std::string  name;
    const uint64_t     uid=utility::Uid();

  public:
    // delta_ext
    virtual void Input(const devs::IO_Type &x) = 0;

    //  等价=delta_int
    virtual void Internal() = 0;

    //  等价=output_func
    virtual void Output(devs::IO_Bag &yb) = 0;

    //  等价=ta
    virtual devs::TimeType Ta() = 0;

  protected:
#pragma region 
    virtual inline void gc_output(IO_Bag &g) override
    {
      //解除 虚方法.
    };
    virtual inline void delta_conf(const IO_Bag &xb) override
    {
      delta_int();
      delta_ext(0 , xb);
    };
    virtual inline devs::TimeType ta() override {
      return Ta();
    }
    virtual inline void delta_int() override {
      Internal();
    }
    virtual inline void delta_ext(devs::TimeType e , const IO_Bag &xb) override {
      for(auto &io : xb) {
        Input(io);
      }
    }
    virtual inline void output_func(IO_Bag &yb) override {
      Output(yb);
    }
#pragma endregion
  };

}