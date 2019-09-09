#pragma once
#include"devs.hpp"
#include<list>
namespace cc {
  class CalcEven :
    public devs::AtomicAbstract {
  public:
    CalcEven();

    // Í¨¹ý AtomicAbstract ¼Ì³Ð
    virtual void External(const devs::PortType & recvPort, const devs::SptrBlob sptrBlob) override;

    virtual void Internal() override;

    virtual void Output(devs::IO_Bag & yb) override;

    virtual devs::TimeType Ta() override;

    const devs::Port recvEven = devs::Port("r_Even");
    const devs::Port send = devs::Port("Send");
  public:
    std::list<devs::SptrBlob> buffer_list;




  };

}