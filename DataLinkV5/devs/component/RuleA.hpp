#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {

  /*
    获得LT时候,将track_name放进缓冲队列中.
    随后,由Sub Time Slice触发,再进行判别
  */
  class RuleA
    : JuComponent
  {

  public:
      RuleA(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);

    // 通过 JuComponent 继承
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;

    _FUNC_MakeShared_(RuleA)
  private:
    //预处理Set
    std::set<std::string> preTreatmentSet;

    //是否收到sub_ts signal
    //该变量被 ta() 函数使用. 在 delta_int 被置零
    bool  isRecvSubTS=false;

  };
  //const auto CreatSptrRuleA = RuleA::make_shared;
  _FUNC_CreatSptr_(RuleA);
}