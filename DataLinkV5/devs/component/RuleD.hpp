#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {

  /*
    ��TS����.��output�������ж��Ƿ�TQ==0
  */
  class RuleD
    : JuComponent
  {

  public:
    RuleD(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);
    _FUNC_MakeShared_(RuleD);

    // ͨ�� JuComponent �̳�
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;
  private:
    bool  is_recv_ts = false;
  };
  _FUNC_CreatSptr_(RuleD);
}