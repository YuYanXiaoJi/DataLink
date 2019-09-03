#include "RuleG.h"

devs::component::RuleG::RuleG(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid)
  :JuComponent(ju, _digraph, _name, _uid)
{

}

void devs::component::RuleG::delta_int()
{
  at_sptr_blob_list.pop_front();
}

void devs::component::RuleG::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
  for (auto&x : xb) {
    if (x.port == this->port_self_recv_at) {
      at_sptr_blob_list.push_back(x.value);
    }
  }
}

void devs::component::RuleG::output_func(IO_Bag & yb)
{
  auto& at = at_sptr_blob_list.front()->get<msg::ActiveTrack>();
  auto track_name = util::TrackNumberHandler::GetName(at.track_number);
  auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);
  if ( is_exist_rt && is_exist_r2 == false) {
    // G¹æÔò
    if (0==parent.dict_recv_track[track_name].track_quality && parent.dict_active_track[track_name].track_quality>0) {
      yb.insert(IO_Type(port_self_send,
                util::CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2, track_name.c_str()))
      ));
    }
  }
}

devs::TimeType devs::component::RuleG::ta()
{
  return at_sptr_blob_list.empty()*TIME_MAX;
}

