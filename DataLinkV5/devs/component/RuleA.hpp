#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {

  /*
    �1�7�1�7�1�7LT�0�2�1�7�1�7,�1�7�1�7track_name�1�7�0�5�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7.
    �1�7�1�7�1�7,�1�7�1�7Sub Time Slice�1�7�1�7�1�7�1�7,�1�7�1�5�1�7�1�7�1�7�1�7�҄1�7
  */
  class RuleA
    : JuComponent
  {

  public:
      RuleA(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);

    // �0�0�1�7�1�7 JuComponent �1�7�0�7�1�7
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;

    _FUNC_MakeShared_(RuleA)
  private:
    //�0�0�1�7�1�7�1�7�1�7Set
    std::set<std::string> preTreatmentSet;

    //�1�7�0�9�1�7�1�7�0�1�1�7sub_ts signal
    //�1�7�0�9�1�7�1�7�1�7�1�7�1�7 ta() �1�7�1�7�1�7�1�7�0�0�1�7�1�7. �1�7�1�7 delta_int �1�7�1�7�1�7�1�7�1�7�1�7
    bool  isRecvSubTS=false;

  };
  //const auto CreatSptrRuleA = RuleA::make_shared;
  _FUNC_CreatSptr_(RuleA);
}