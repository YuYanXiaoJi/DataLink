#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {

  /*
    ���LTʱ��,��track_name�Ž����������.
    ���,��Sub Time Slice����,�ٽ����б�
  */
  class RuleA
    : JuComponent
  {

  public:
      RuleA(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);

    // ͨ�� JuComponent �̳�
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;

    _FUNC_MakeShared_(RuleA)
  private:
    //Ԥ����Set
    std::set<std::string> preTreatmentSet;

    //�Ƿ��յ�sub_ts signal
    //�ñ����� ta() ����ʹ��. �� delta_int ������
    bool  isRecvSubTS=false;

  };
  //const auto CreatSptrRuleA = RuleA::make_shared;
  _FUNC_CreatSptr_(RuleA);
}