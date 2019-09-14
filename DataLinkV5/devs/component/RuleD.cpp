#include "RuleD.hpp"
#include"../../utility/utility.hpp"
#include"../time.hpp"
devs::component::RuleD::RuleD(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
  :JuComponent(ju, _digraph, _name, _uid)
{
  BindSelfRecvTS();
}

void devs::component::RuleD::delta_int()
{
  is_recv_ts = false;
}

void devs::component::RuleD::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
  for (auto&x : xb) {
    if (x.port == GetSelfRecvTS()) {
      is_recv_ts = true;
    }
  }
}

void devs::component::RuleD::output_func(IO_Bag & yb)
{
  for (auto[track_name, rttn] : parent.dict_recv_track) {
    auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);
    if (is_exist_at && is_exist_rt && is_exist_r2 == false) {
      if (rttn.track_quality == 0) {// TQ==0

        //SET R2
        yb.insert(IO_Type(GetSelfSend(),
          util::CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2, track_name.c_str()))
        ));

        //发送J7_ACT=0的消息 
        yb.insert(CreatBroadcastIO(util::CreateSptrBlob(
          msg::JointMsg7I(TrackNumberHandler::Create(track_name).c_str(), parent.name.c_str(), 0, Time::now())
        )));
      }//IF
    }//IF
  }//FOR

}

devs::TimeType devs::component::RuleD::ta()
{
  return (is_recv_ts==false)*TIME_MAX;
}
