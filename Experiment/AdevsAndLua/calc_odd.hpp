#pragma once
#include"devs.hpp"
#include"component.hpp"
namespace cc {
  class CalcOdd :
    public Component {
  public:
    CalcOdd(devs::Digraph &digrapg, Generator &parent);


    // Í¨¹ý AtomicAbstract ¼Ì³Ð
    virtual void Input(const devs::PortType & recvPort, const devs::SptrBlob sptrBlob) override;
    virtual void Internal() override;
    virtual void Output(devs::IO_Bag & yb) override;
    virtual devs::TimeType Ta() override;



  };

}