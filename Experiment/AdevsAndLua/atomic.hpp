#pragma once
#include"typedef.hpp"
#include<Adevs/adevs.h>

namespace devs {
  class AtomicAbstract :
    public adevs::Atomic<IO_Type, TimeType>
  {
  public:
    //  等价=delta_ext
    virtual void Input(const devs::PortType& recvPort, const devs::SptrBlob sptrBlob) = 0;

    //  等价=delta_int
    virtual void Internal() = 0;

    //  等价=output_func
    virtual void Output(devs::IO_Bag& yb) = 0;

    //  等价=ta
    virtual devs::TimeType Ta() = 0;
  protected:
    virtual inline void gc_output(IO_Bag& g) override
    {
      //解除 虚方法.
    };

    virtual inline void delta_conf(const IO_Bag& xb) override
    {
      delta_int();
      delta_ext(0, xb);
    };

    virtual inline devs::TimeType ta() override {
      return Ta();
    }
    virtual inline void delta_int() override {
      Internal();
    }
    virtual inline void delta_ext(devs::TimeType e, const IO_Bag& xb)override {
      for (auto& io : xb) {
        Input(io.port, io.value);
      }
    }
    virtual inline void output_func(IO_Bag& yb) override {
      Output(yb);
    }
    
  };
  
}