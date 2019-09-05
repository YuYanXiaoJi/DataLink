#include "core_broadcast_component.hpp"
#include"../time.hpp"
devs::component::CoreBroadcastComponent::CoreBroadcastComponent(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
  :JuComponent(ju, _digraph, _name, _uid)
{
  digraph.couple(&ju, ju.portSelfSendToTranspondBuffer, this, this->portSelfRecvToTranspondBuffer);
  digraph.couple(this, portToBroadcast, &ju, ju.portToBroadcast);
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
    yb.insert(IO_Type( portToBroadcast, broadcastBuferrList.front()));
    log(broadcastBuferrList.front());

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

void devs::component::CoreBroadcastComponent::log(util::SptrBlob sptr_blob)
{
  auto& blob = *sptr_blob;
  switch (blob.blob_type<msg::MsgType>())
  {
  case msg::MsgType::Msg_LocalTrack:
  {
    auto& msg = blob.get<msg::LocalTrack>();
    auto track_name = util::TrackNumberHandler::GetName(msg.track_number);
    std::cout << Time::now() << "\t" << parent.name << " S: LocalTrack\t" << msg.track_number << std::endl;
    break;
  }
  case msg::MsgType::Msg_JointMsg3I:
  {
    auto& msg = blob.get<msg::JointMsg3I>();
    auto track_name = util::TrackNumberHandler::GetName(msg.track_number);
    std::cout << Time::now() << "\t" << parent.name << " S: JointMsg3I\t" << msg.track_number << std::endl;
    break;
  }
  case msg::MsgType::Msg_JointMsg7I:
  {
    auto& msg = blob.get<msg::JointMsg7I>();
    std::cout << Time::now() << "\t" << parent.name << " S: JointMsg7I\t" << msg.track_number << std::endl;
    break;
  }
  case msg::MsgType::Msg_JointMsg2I:
  {
    auto& msg = blob.get<msg::JointMsg2I>();
    std::cout << Time::now() << "\t" << parent.name << " S: JointMsg2I\t" << msg.track_number << std::endl;
    break;
  }
  default:
    break;
  }
    
}
