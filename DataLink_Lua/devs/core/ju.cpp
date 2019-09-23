#include "ju.hpp"
#include<iostream>

#include"core_ju_component/print_component.hpp"

#include"core_ju_component/core_broadcast_component.hpp"
#include"core_ju_component/core_period_broadcast_component.hpp"
#include"core_ju_component/core_reporting_responsibility_component.hpp"


#include"../rule/rule_a.hpp"
namespace devs::core {

  std::shared_ptr<Ju> Ju::make_shared(Digraph &_digraph , const std::string &_name , int32_t _uSTN)
  {
    return std::make_shared<Ju>(_digraph, _name, _uSTN);
  }

  devs::core::Ju::Ju(Digraph &_digraph , const std::string &_name , int32_t _uSTN)
    :AbstractAtomic(_digraph,_name),_uSTN(_uSTN)
  {
    AddComponent(ju_component::PrintComponent::Creator(*this));

    AddComponent(ju_component::CoreBroadcastComponent::Creator(*this));
    AddComponent(ju_component::CorePeriodBroadcastComponent::Creator(*this));
    AddComponent(ju_component::CoreReportingResponsibilityComponent::Creator(*this));

    AddComponent(ju_component::RuleA::Creator(*this));
  }

  std::tuple<bool , bool , bool> Ju::GetExist(const std::string &track_name) {
    bool is_exist_r2 = dict_r2.exist(track_name);
    bool is_exist_at = dict_local_track.exist(track_name);
    bool is_exist_rt = dict_recv_track.exist(track_name);
    return std::tuple(is_exist_at,is_exist_rt,is_exist_r2);
  }

  void Ju::Input(const devs::IO_Type &x)
  {
    // 处理 来自 HUB的消息
    if(x.port == sigio_hub) {
      if(CheckIsSelfSend(*x.value) == true) {
        return;
      }
      UpdateInfo(*x.value);
      LogMsg(*x.value);
      PushBuffer(Time::Now() , x);  // 来自HUB的消息立即处理
    }

    // 处理 来自 内部component的消息
    if(x.port == sigi_interior) {
      PushBuffer(Time::Now() , x);  // 来自 内部 的消息立即处理
    }

    // 处理 想要在 TimeSlice 内进行广播的
    if(x.port == sigi_secure_broadcast) {
      PushBuffer(Time::Now() , x);  // 来自 内部 的消息立即处理
    }

    //  处理 想要立即 广播的数据
    if(x.port == sigi_immediate_broadcast ) {
      PushBuffer(Time::Now() , x);  // 直接将数据发送给 HUB
    }

  }

  void Ju::Internal()
  {
    recv_buffer_queue.pop();
  }

  void Ju::Output(devs::IO_Bag &yb)
  {
    auto io = recv_buffer_queue.top().io_buffer;
    auto & blob = *io.value;
    const auto blob_sig = recv_buffer_queue.top().io_buffer.port;

    if(blob_sig == sigio_hub) {
      InsertToYBag(io , yb);
    }

    if(blob_sig == sigi_interior) {
      InsertToYBag(io , yb);
    }

    if(blob_sig == sigi_secure_broadcast) {
      yb.insert(IO_Type(sigo_broadcast_buffer , io.value));
    }

    if(blob_sig == sigi_immediate_broadcast) {
      RecordMsgTrackNumber(*io.value);
      yb.insert(IO_Type(sigio_hub , io.value));
    }
  }

  devs::TimeType Ju::Ta()
  {
    if(recv_buffer_queue.empty())
      return devs::TIME_MAX;
    
    auto t = recv_buffer_queue.top().schedule_time;
    return Time::Distance(t);
  }

  void Ju::AddComponent(const shared_ptr<JuComponent> sptr_component)
  {
    assert(sptr_component != nullptr);
    map_component[sptr_component->uid] = sptr_component;
  }

  bool Ju::CheckIsSelfSend(const util::Blob &blob)
  {
    auto type = blob.blob_type<msg::MsgType>();

    //判断是不是 J系列的报文. 是J系列的报文才有判断是否是自己发的意义
    if(type == msg::Msg_JointMsg2I || type == msg::Msg_JointMsg3I || type == msg::Msg_JointMsg7I) {
      auto base_msg = blob.get<msg::JointMsgBase>();
      return set_record_track_number.find(base_msg.track_number) == set_record_track_number.end();
    }
    return false;
  }

  void Ju::UpdateInfo(const util::Blob &blob)
  {
    auto type = blob.blob_type<msg::MsgType>();
    if(type == msg::Msg_JointMsg3I) {
      auto& msg = blob.get<msg::JointMsg3I>();
      auto track_name = handler::TrackNumberHandler::GetName(msg.track_number);
      dict_local_track[track_name] = handler::TrackInformation(msg);
    }

    if(type == msg::Msg_LocalTrack) {
      auto& msg = blob.get<msg::LocalTrack>();
      auto track_name = handler::TrackNumberHandler::GetName(msg.track_number);
      dict_local_track[track_name] = handler::TrackInformation(msg , this->name);
    }

    if(type == msg::Msg_TimeSlice) {
      auto ts = blob.get<msg::TimeSlice>();
      this->time_silce = ts;
      for(auto t = ts.begin_time; t < ts.end_time-1; t += _time_slice_trigger_interval) {
        auto sptr_sts = util::CreateSptrBlob(msg::SubTimeSlice(ts , t));
        PushBuffer(t , IO_Type(sigi_interior , sptr_sts));
      }
      auto sptr_sts = util::CreateSptrBlob(msg::SubTimeSlice(ts , ts.end_time - 1));
      PushBuffer(ts.end_time - 1 , IO_Type(sigi_interior , sptr_sts));
    }
  }
  void Ju::LogMsg(const util::Blob &blob)
  {
    if(blob.blob_type<msg::MsgType>() == msg::Msg_TimeSlice)
      return;
    std::cout << Time::Now() << "\t" << "R: " << msg::GetMsgTypeName(blob.blob_type<msg::MsgType>()) << std::endl;
  }
  void Ju::PushBuffer(TimeType schedule_time , const IO_Type& x){
    recv_buffer_queue.push(handler::ScheduleBufferNode(schedule_time , x));
  }

  
  void Ju::InsertToYBag(const devs::IO_Type x , devs::IO_Bag &yb) {
    auto sptr_blob = recv_buffer_queue.top().io_buffer.value;
    auto & blob = *sptr_blob;

    switch(blob.blob_type<msg::MsgType>())
    {
    case devs::message::Msg_JointMsg2I:
      yb.insert(IO_Type(sigo_j2 , sptr_blob));
      break;
    case devs::message::Msg_JointMsg3I:
      yb.insert(IO_Type(sigo_j3 , sptr_blob));
      break;
    case devs::message::Msg_JointMsg7I:
      yb.insert(IO_Type(sigo_j7 , sptr_blob));
      break;
    case devs::message::Msg_LocalTrack:
      yb.insert(IO_Type(sigo_lt , sptr_blob));
      break;
    case devs::message::Msg_TimeSlice:
      yb.insert(IO_Type(sigo_ts , sptr_blob));
      break;
    case devs::message::Msg_SubTimeSlice:
      yb.insert(IO_Type(sigo_sts , sptr_blob));
      break;
    case devs::message::Msg_LoaclCmdType:
      yb.insert(IO_Type(sigo_cmd , sptr_blob));
      break;
    default:
      break;
    }
  }
  void Ju::RecordMsgTrackNumber(const util::Blob & blob)
  {
    auto type = blob.blob_type<msg::MsgType>();
    if(type == msg::Msg_JointMsg2I || type == msg::Msg_JointMsg3I || type == msg::Msg_JointMsg7I) {
      auto base_msg = blob.get<msg::JointMsgBase>();
      set_record_track_number.insert(base_msg.track_number);
    }
  }
}