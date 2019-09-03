#include "core_reporting_responsibility_handler.hpp"

devs::component::CoreReportingResponsibilityHandler::CoreReportingResponsibilityHandler(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
  :JuComponent(ju, _digraph, _name, _uid)
{
}

void devs::component::CoreReportingResponsibilityHandler::delta_int()
{
  local_cmd_list.pop_front();
}

void devs::component::CoreReportingResponsibilityHandler::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
  for (auto&x : xb) {
    if (x.port == port_self_recv_cmd) {
      auto& cmd = x.value->get<msg::LocalCmd>();
      local_cmd_list.push_back(cmd);
    }
  }
}

void devs::component::CoreReportingResponsibilityHandler::output_func(IO_Bag & yb)
{
  auto&cmd = local_cmd_list.front();
  if (cmd.cmd_id == msg::CMD_RM_R2 ) {
    parent.dict_r2.erase(cmd.track_name);
  }
  else if (cmd.cmd_id == msg::CMD_SET_R2) {
    if (parent.dict_r2.exist(cmd.track_name)==false) {
      parent.dict_r2[cmd.track_name] = 0;
    }
  }
}

devs::TimeType devs::component::CoreReportingResponsibilityHandler::ta()
{
  return local_cmd_list.empty()*TIME_MAX;
}
