#include "core_j3_broadcast_handler.hpp"
#include"../handler.hpp"
#include<algorithm>
#include"../time.hpp"
devs::component::CoreJ3BroadcastHandler::CoreJ3BroadcastHandler(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
  :JuComponent(ju,_digraph,_name,_uid)
{
  BindSelfRecvSubTS();
}

void devs::component::CoreJ3BroadcastHandler::delta_int()
{
  is_recv_ts = false;
}

void devs::component::CoreJ3BroadcastHandler::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
  for (auto&x : xb) {
    if (x.port == GetSelfRecvSubTS()) {
      is_recv_ts = true;
    }
  }
}

void devs::component::CoreJ3BroadcastHandler::output_func(IO_Bag & yb)
{
  auto& ts = parent.time_silce;
  for (auto[track_name, last_broadcast_time]/*[key,value] c++17*/ : parent.dict_r2) {
    auto& attn = parent.dict_active_track[track_name];
    auto broadcast_interval = GetMinBroadcastInterval(attn.track_platform);
    auto next_broadcast_time_min = broadcast_interval + last_broadcast_time;

    //只要 next_broadcast_time_min 小于 ts.end 就可以发.
    //在根据 ts.begin 确定具体在哪个时间 发 
    if (next_broadcast_time_min < ts.end_time) {
      auto next_broadcast_time = std::max(next_broadcast_time_min, ts.begin_time);
      parent.dict_r2[track_name] = next_broadcast_time;  //更新时间

      //广播 J3i
      yb.insert(CreatBroadcastIO(util::CreateSptrBlob(
        parent.dict_active_track[track_name].get<msg::JointMsg3I>()
      )));
    }
    else if (last_broadcast_time == 0) {//立即发
      parent.dict_r2[track_name] = Time::now();
      yb.insert(CreatBroadcastIO(util::CreateSptrBlob(
        parent.dict_active_track[track_name].get<msg::JointMsg3I>()
      )));
    }
  }
  //std::cout << "time_silce:" << parent.time_silce.begin_time << "\t" << parent.time_silce.end_time << std::endl;
}

devs::TimeType devs::component::CoreJ3BroadcastHandler::ta()
{
  return (is_recv_ts == false)*TIME_MAX;
}
