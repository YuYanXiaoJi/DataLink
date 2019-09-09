#pragma once
#include"devs.hpp"
#include<list>
namespace cc {
  class CalcOdd :
    public devs::AtomicAbstract {
  public:
    CalcOdd();


    // ͨ�� AtomicAbstract �̳�
    virtual void External(const devs::PortType & recvPort, const devs::SptrBlob sptrBlob) override;
    virtual void Internal() override;
    virtual void Output(devs::IO_Bag & yb) override;
    virtual devs::TimeType Ta() override;

    const devs::Port recvOdd  = devs::Port("r_Odd");
    const devs::Port send     = devs::Port("Send");
  public:
    std::list<devs::SptrBlob> buffer_list;

  };

}