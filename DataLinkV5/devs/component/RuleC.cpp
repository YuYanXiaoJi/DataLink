#include "RuleC.hpp"
#include"../time.hpp"
devs::component::RuleC::RuleC(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
  :JuComponent(ju, _digraph, _name, _uid)
{
}

void devs::component::RuleC::delta_int()
{
  is_recv_ts = false;
}

void devs::component::RuleC::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
  for (auto&x : xb) {
    if (x.port == port_self_recv_ts) {
      is_recv_ts = true;
    }
  }
}

devs::TimeType devs::component::RuleC::ta()
{
  return (is_recv_ts == false)*TIME_MAX;
}

void devs::component::RuleC::output_func(IO_Bag & yb)
{
  for (auto[track_name, last_broadcast_time] : parent.dict_active_track) {
    auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);
    if (is_exist_at && is_exist_rt && is_exist_r2 == false) {
      auto rttn = parent.dict_recv_track[track_name];
      auto attn = parent.dict_active_track[track_name];

      if (attn.track_quality - rttn.track_quality >= kThresholdTQ) {
        yb.insert(IO_Type(port_self_send,
          util::CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2, track_name.c_str()))
        ));
        //发送J7_ACT=0的消息 
        yb.insert(IO_Type(
          port_self_send_to_transpond,
          util::CreateSptrBlob(
            msg::JointMsg7I(track_name.c_str(), parent.name.c_str(), 0, Time::now())
          )
        ));

      }
    }
  }
}


