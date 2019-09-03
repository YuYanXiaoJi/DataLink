#include "RuleE.hpp"
#include"../handler.hpp"
#include "../time.hpp"
#include "../../utility/utility.hpp"
devs::component::RuleE::RuleE(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
  :JuComponent(ju, _digraph, _name, _uid)
{
  BindSelfRecvTS();
}

void devs::component::RuleE::delta_int(){
  is_recv_ts = false;
}

devs::TimeType devs::component::RuleE::ta(){
  return (is_recv_ts == false)*TIME_MAX;
}


void devs::component::RuleE::delta_ext(devs::TimeType e, const IO_Bag & xb){
  for (auto&x : xb)  {
    if (x.port==GetSelfRecvTS()){
      is_recv_ts = true;
    }
  }
}


void devs::component::RuleE::output_func(IO_Bag & yb)
{
  for (auto[track_name, rttn] : parent.dict_recv_track) {
    auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);


    if (is_exist_at && is_exist_rt && is_exist_r2 == false) {

      TimeType diff_time = Time::now() - rttn.time_msec;
      TimeType min_wait_time = devs::GetWaitInterval(rttn.track_platform);
      if (diff_time> min_wait_time) {// Timeout

        //SET R2
        yb.insert(IO_Type(GetSelfSend(),
          util::CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2, track_name.c_str()))
        ));

        //发送J7_ACT=0的消息 
        yb.insert(CreatBroadcastIO(util::CreateSptrBlob(
          msg::JointMsg7I(track_name.c_str(), parent.name.c_str(), 0, Time::now())
        )));

      }//IF
    }//IF
  }//FOR
}

