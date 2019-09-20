#pragma once
#include"../ju_component.hpp"
namespace devs::core::ju_component {
  class CorePeriodBroadcastComponent
    :public JuComponent
  {
  public:
    CorePeriodBroadcastComponent(Digraph & _digraph , Ju & _ju);
    __CREATOR__(CorePeriodBroadcastComponent);

    // Í¨¹ý JuComponent ¼Ì³Ð
    virtual void Input(const devs::IO_Type & x) override;

    virtual void Internal() override;

    virtual void Output(devs::IO_Bag & yb) override;

    virtual devs::TimeType Ta() override;

  private:
    bool is_recv_ts = false;
    
  };
}