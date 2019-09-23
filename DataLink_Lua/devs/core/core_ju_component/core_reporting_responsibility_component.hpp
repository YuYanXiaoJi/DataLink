#pragma once
#include"../ju_component.hpp"
#include<queue>
namespace devs::core::ju_component {
  class CoreReportingResponsibilityComponent
    :public JuComponent
  {
  public:
    CoreReportingResponsibilityComponent(Digraph & _digraph , Ju & _ju);
    __CREATOR__(CoreReportingResponsibilityComponent);

    // Í¨¹ý JuComponent ¼Ì³Ð
    virtual void Input(const devs::IO_Type & x) override;

    virtual void Internal() override;

    virtual void Output(devs::IO_Bag & yb) override;

    virtual devs::TimeType Ta() override;

  private:
    std::queue<msg::LocalCmd> local_cmd_queue;
  };
}