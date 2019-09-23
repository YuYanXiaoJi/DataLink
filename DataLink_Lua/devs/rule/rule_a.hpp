#pragma once
#include"../core/ju_component.hpp"
#include<set>
namespace devs::core::ju_component {
  class RuleA
    :public JuComponent
  {
  public:
    RuleA(Digraph & _digraph , Ju & _ju);
    __CREATOR__(RuleA);

    // Í¨¹ý JuComponent ¼Ì³Ð
    virtual void Input(const devs::IO_Type & x) override;

    virtual void Internal() override;

    virtual void Output(devs::IO_Bag & yb) override;

    virtual devs::TimeType Ta() override;

  private:
    bool is_recv_ts = false;
    std::set<std::string> local_track_name_set;
  };



}