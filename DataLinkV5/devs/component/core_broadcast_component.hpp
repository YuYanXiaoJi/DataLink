#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {

  class CoreBroadcastComponent
    : JuComponent
  {

  public:
    CoreBroadcastComponent(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);

    _FUNC_MakeShared_(CoreBroadcastComponent);

    // 通过 JuComponent 继承
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;

  private:
    //std::list<util::SptrBlob> broadcastSendList;      //直接发送
    std::list<util::SptrBlob> broadcastBuferrList;    //等待发送
  public:
    const PortType portSelfRecvToTranspondBuffer = util::NextUid();
  };
  _FUNC_CreatSptr_(CoreBroadcastComponent);
}