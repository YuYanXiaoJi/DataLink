#include "core_reporting_responsibility_component.hpp"

devs::core::ju_component::CoreReportingResponsibilityComponent::CoreReportingResponsibilityComponent(Digraph & _digraph , Ju & _ju)
  :JuComponent(_digraph,_ju,"CoreReportingResponsibilityComponent")
{
  BindInCMD();
}

void devs::core::ju_component::CoreReportingResponsibilityComponent::Input(const devs::IO_Type & x)
{
  if(x.port == sigi_cmd) {
    local_cmd_queue.push(x.value->get<msg::LocalCmd>());
  }
}

void devs::core::ju_component::CoreReportingResponsibilityComponent::Internal()
{
  local_cmd_queue.pop();
}

void devs::core::ju_component::CoreReportingResponsibilityComponent::Output(devs::IO_Bag & yb)
{
  auto msg = local_cmd_queue.front();
  if(msg.cmd_id == msg::CMD_RM_R2) {
    ju.dict_r2.erase(msg.track_name);
  }
  else if(msg.cmd_id == msg::CMD_SET_R2) {
    if(ju.dict_r2.exist(msg.track_name) == false) {
      ju.dict_r2[msg.track_name] = 0;
    }
  }
}

devs::TimeType devs::core::ju_component::CoreReportingResponsibilityComponent::Ta()
{
  if(local_cmd_queue.empty())
    return TIME_MAX;
  else
    return 0;
}
