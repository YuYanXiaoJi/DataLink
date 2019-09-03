#include "core_broadcast_component.hpp"
#include"../time.hpp"
devs::component::CoreBroadcastComponent::CoreBroadcastComponent(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
  :JuComponent(ju, _digraph, _name, _uid)
{
  digraph.couple(&ju, ju.portSelfSendToTranspondBuffer, this, this->portSelfRecvToTranspondBuffer);

}

void devs::component::CoreBroadcastComponent::delta_int()
{
  
}

void devs::component::CoreBroadcastComponent::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
  for (auto&x : xb) {
    if (x.port == portSelfRecvToTranspondBuffer) {
      broadcastBuferrList.push_back(x.value);
    }
  }
}

void devs::component::CoreBroadcastComponent::output_func(IO_Bag & yb)
{
  while (broadcastBuferrList.empty() == false) {
    yb.insert(this->CreatBroadcastIO(broadcastBuferrList.front()));
    broadcastBuferrList.pop_front();
  }
}

devs::TimeType devs::component::CoreBroadcastComponent::ta()
{
  //时间要在时间片内 && 待发送队列不为空 
  auto now = Time::now();
  auto&ts = parent.time_silce;
  if (ts.begin_time <= now && now < ts.end_time  && this->broadcastBuferrList.empty() == false) {
    return 0;
  }
  else {
    return TIME_MAX;
  }
}
