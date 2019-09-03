#include "RuleA.hpp"
using namespace util;
devs::component::RuleA::RuleA(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
  :JuComponent(ju, _digraph,_name,_uid)
{
  BindSelfRecvLT();
  BindSelfRecvSubTS();
}

void devs::component::RuleA::delta_int()
{
  isRecvSubTS = false;
}

void devs::component::RuleA::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
  for (auto&x : xb) {

    //接受 AT 消息
    if (x.port == GetSelfRecvLT()) {
      const auto& msg = x.value->get<msg::LocalTrack>();
      string track_name = TrackNumberHandler::GetName(msg.track_number);
      if (parent.dict_recv_track.exist(track_name) == false 
          && preTreatmentSet.find(track_name)== preTreatmentSet.end()) {
        preTreatmentSet.insert(track_name);
      }
    }

    //检测 sub_ts消息
    if (x.port == GetSelfRecvSubTS()) {
      isRecvSubTS = true;
      std::cout << x.value->get<msg::SubTimeSlice>().current_time << endl;
    }

  }
}

void devs::component::RuleA::output_func(IO_Bag & yb)
{
  for (auto& track_name : preTreatmentSet) {
    auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);
    if ( (is_exist_r2 == false) && (is_exist_rt == false) && (is_exist_at == true))
    {
      IO_Type y;
      y.port = GetSelfSend();
      y.value = CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2, track_name.c_str()));
      yb.insert(y);
    }
  }
}

devs::TimeType devs::component::RuleA::ta()
{
  return (isRecvSubTS==false)*TIME_MAX;
}
