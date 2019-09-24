#include "core_period_broadcast_component.hpp"
#include "../../handler/time_interval_handler.hpp"

devs::core::ju_component::CorePeriodBroadcastComponent::CorePeriodBroadcastComponent(Digraph & _digraph , Ju & _ju)
  :JuComponent(_digraph , _ju , "CorePeriodBroadcastComponent")
{
  BindInSTS();
}

void devs::core::ju_component::CorePeriodBroadcastComponent::Input(const devs::IO_Type & x)
{
  if(x.port == sigi_sts) {
    is_recv_ts = true;
  }
}

void devs::core::ju_component::CorePeriodBroadcastComponent::Internal()
{
  is_recv_ts = false;
}

void devs::core::ju_component::CorePeriodBroadcastComponent::Output(devs::IO_Bag & yb)
{
  using namespace devs::handler::time_interval_handler;
  auto current_time = Time::Now();  //当前时间

  auto& ts = ju.time_slice;
  for(auto[track_name , last_broadcast_time]/*[key,value] c++17*/ : ju.dict_r2) {
    auto& ltn = ju.dict_local_track[track_name];
    auto broadcast_interval_min = GetMinBroadcastInterval(ltn.track_platform);
    auto pre_next_broadcast_time_min = broadcast_interval_min + last_broadcast_time;  //预测的下一次发送的时间.

    if(pre_next_broadcast_time_min <= current_time /* 预测的时间小于当前时间*/  || last_broadcast_time == 0) {
      ju.dict_r2[track_name] = current_time;  //更新时间
      //广播 J3i
      auto sptr_msg = util::CreateSptrBlob(ju.dict_local_track[track_name].Get<msg::JointMsg3I>(true));
      InsertSecureBroadcast(sptr_msg , yb);
    }
  }
}

devs::TimeType devs::core::ju_component::CorePeriodBroadcastComponent::Ta()
{
  if(is_recv_ts)
    return 0;
  else
    return devs::TIME_MAX;
}
