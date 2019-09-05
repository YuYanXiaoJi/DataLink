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

    // ͨ�� JuComponent �̳�
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;

  private:
    //std::list<util::SptrBlob> broadcastSendList;      //ֱ�ӷ���
    std::list<util::SptrBlob> broadcastBuferrList;    //�ȴ�����

    void log(util::SptrBlob sptr_blob);
  public:
    const PortType portSelfRecvToTranspondBuffer = util::NextUid();
    const PortType portToBroadcast = util::NextUid();
  };
  _FUNC_CreatSptr_(CoreBroadcastComponent);
}