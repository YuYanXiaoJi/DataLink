#include "core_broadcast_component.hpp"

namespace devs::core::ju_component {

  CoreBroadcastComponent::CoreBroadcastComponent(Digraph & _digraph , Ju & _ju)
    :JuComponent(_digraph , _ju , "CoreBroadcastComponent")
  {
    BindInBroadcastBuffer();  //接受想安全转发的
  }

  void CoreBroadcastComponent::Input(const devs::IO_Type & x)
  {
    if(x.port == sigi_broadcast_buffer) {
      broadcast_buffer_queue.push(x.value);
    }
  }

  void CoreBroadcastComponent::Internal()
  {

  }

  void CoreBroadcastComponent::Output(devs::IO_Bag & yb)
  {
    while(broadcast_buffer_queue.empty() == false) {
      InsertImmediateBroadcast(broadcast_buffer_queue.front() , yb);
      Log(broadcast_buffer_queue.front());

      broadcast_buffer_queue.pop();
    }
  }

  devs::TimeType CoreBroadcastComponent::Ta()
  {
    //时间要在时间片内 && 待发送队列不为空 
    auto now = Time::Now();
    auto&ts = ju.time_silce;
    if(ts.begin_time <= now && now < ts.end_time  && this->broadcast_buffer_queue.empty() == false) {
      return 0;
    }
    else {
      return TIME_MAX;
    }
  }

  void CoreBroadcastComponent::Log(devs::ValueType value)
  {
    std::cout << Time::Now() << "\t" << "CoreBroadcastComponent S: " << msg::GetMsgTypeName(value->blob_type<msg::MsgType>()) << std::endl;
  }


}