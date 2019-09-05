#include "RuleF.hpp"

#include"../time.hpp"
devs::component::RuleF::RuleF(Ju& ju, Digraph& digraph, const std::string&name, PortType uid)
  :JuComponent(ju, digraph, name, uid)
{
  BindSelfRecvTS();
  BindSelfRecvJ7();

}

void devs::component::RuleF::delta_int()
{
  is_recv_ts = false;
}

void devs::component::RuleF::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
  for (auto&x : xb) {
    if (x.port == GetSelfRecvJ7()) {
      auto&j7 = x.value->get<msg::JointMsg7I>();
      if (j7.action==0)
      {
        string track_name = util::TrackNumberHandler::GetName(j7.track_number);
        auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);
        if(is_exist_at==true)
          j7ActZeroList.push_back(j7);
      }
    }

    if (x.port == GetSelfRecvTS()) {
      is_recv_ts = true;
    }
  }
}

void devs::component::RuleF::output_func(IO_Bag & yb)
{
  while (j7ActZeroList.empty() == false) {
    auto& j7 = j7ActZeroList.front();

    // F规则只处理ACT=0的情况
    if (j7.action != 0) return;
    auto track_name = util::TrackNumberHandler::GetName(j7.track_number);
    auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);

    if(is_exist_rt==false 
      || (is_exist_rt && util::math::isInRange(j7.time_msec, parent.dict_recv_track[track_name].time_msec, Time::now()) == false))
    {
      //J3 不存在 或者 在 [j7.time_msec,now) 没收到 新的相关 J3 报告.
      if (parent.CorrelationTest(track_name) == false) {
        if (is_exist_r2 == false) {
          //SET R2
          yb.insert(IO_Type(GetSelfSend(),
            util::CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2, track_name.c_str()))
          ));
        }
      }
    }
    else {//收到了报告
      if (is_exist_r2 == true) {
        //RM R2
        yb.insert(IO_Type(GetSelfSend(),
          util::CreateSptrBlob(msg::LocalCmd(msg::CMD_RM_R2, track_name.c_str()))
        ));
      }
    }

    j7ActZeroList.pop_front();
  }
}

devs::TimeType devs::component::RuleF::ta()
{
  return (is_recv_ts == false)*TIME_MAX;
}

