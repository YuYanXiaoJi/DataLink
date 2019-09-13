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
    const devs::PortType recv  = devs::PortType("Recv");
    const devs::PortType odd   = devs::PortType("Odd");
    const devs::PortType even  = devs::PortType("Even");
    const devs::PortType print = devs::PortType("Print");
  public:
    std::list<devs::SptrBlob> buffer_list;
  };

}