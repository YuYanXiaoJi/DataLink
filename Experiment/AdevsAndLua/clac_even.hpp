#pragma once
#include"devs.hpp"
#include"component.hpp"
#include<list>
namespace cc {
  class CalcEven :
    public Component {
  public:
    CalcEven(devs::Digraph &digrapg, Generator &parent);

    // Í¨¹ý AtomicAbstract ¼Ì³Ð
    virtual void Input(const devs::PortType & recvPort, const devs::SptrBlob sptrBlob) override;

    virtual void Internal() override;

    virtual void Output(devs::IO_Bag & yb) override;

    virtual devs::TimeType Ta() override;

  };

}