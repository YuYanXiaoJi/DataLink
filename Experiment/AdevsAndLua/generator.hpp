#pragma once
#include"devs.hpp"
#include<list>
namespace cc {
  class Generator :
    public devs::AtomicAbstract {
  public:
    Generator();

    // Í¨¹ý AtomicAbstract ¼Ì³Ð
    virtual void External(const devs::PortType & recvPort, const devs::SptrBlob sptrBlob) override;

    virtual void Internal() override;

    virtual void Output(devs::IO_Bag & yb) override;

    virtual devs::TimeType Ta() override;

  public:
    const devs::Port recv     = devs::Port("Recv");
    const devs::Port sendOdd  = devs::Port("s_Odd");
    const devs::Port sendEven = devs::Port("s_Even");
    const devs::Port sendPrint = devs::Port("s_Print");
  public:
    std::list<devs::SptrBlob> buffer_list;
  };

}