#include "ju.hpp"
#include<iostream>

#include"core_ju_component/print_component.hpp"
#include"core_ju_component/core_broadcast_component.hpp"
#include"core_ju_component/core_period_broadcast_component.hpp"

namespace devs::core {

  std::shared_ptr<Ju> devs::core::Ju::make_shared(Digraph &_digraph , const std::string &_name , int32_t _uSTN)
  {
    return std::make_shared<Ju>(_digraph, _name, _uSTN);
  }

  devs::core::Ju::Ju(Digraph &_digraph , const std::string &_name , int32_t _uSTN)
    :AbstractAtomic(_digraph,_name),_uSTN(_uSTN)
  {
    //AddComponent(ju_component::PrintComponent::Creator(*this));
    AddComponent(ju_component::CoreBroadcastComponent::Creator(*this));
    AddComponent(ju_component::CorePeriodBroadcastComponent::Creator(*this));
  }

  void Ju::Input(const devs::IO_Type &x)
  {
    // ���� ���� HUB����Ϣ
    if(x.port == sigio_hub) {
      if(CheckIsSelfSend(*x.value) == true) {
        return;
      }
      UpdateInfo(*x.value);
      LogMsg(*x.value);
      PushBuffer(Time::Now() , x);  // ����HUB����Ϣ��������
    }

    // ���� ���� �ڲ�component����Ϣ
    if(x.port == sigi_interior) {
      PushBuffer(Time::Now() , x);  // ���� �ڲ� ����Ϣ��������
    }

    // ���� ��Ҫ�� TimeSlice �ڽ��й㲥��
    if(x.port == sigi_secure_broadcast) {
      PushBuffer(Time::Now() , x);  // ���� �ڲ� ����Ϣ��������
    }

    //  ���� ��Ҫ���� �㲥������
    if(x.port == sigi_immediate_broadcast ) {
      PushBuffer(Time::Now() , x);  // ֱ�ӽ����ݷ��͸� HUB
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
      PushBuffer(Time::Now() , IO_Type(sigo_broadcast_buffer , io.value));
    }

    if(blob_sig == sigi_immediate_broadcast) {
      PushBuffer(Time::Now() , IO_Type(sigio_hub , io.value));
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

    //�ж��ǲ��� Jϵ�еı���. ��Jϵ�еı��Ĳ����ж��Ƿ����Լ���������
    if(type == msg::Msg_JointMsg2I || type == msg::Msg_JointMsg3I || type == msg::Msg_JointMsg7I) {
      auto base_msg = blob.get<msg::JointMsgBase>();
      if(this->name == base_msg.from) //ֻ����Ȳ����� true
        return true;
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
      yb.insert(IO_Type(sigo_local_track , sptr_blob));
      break;
    case devs::message::Msg_TimeSlice:
      yb.insert(IO_Type(sigo_time_slice , sptr_blob));
      break;
    case devs::message::Msg_SubTimeSlice:
      yb.insert(IO_Type(sigo_sub_ts , sptr_blob));
      break;
    case devs::message::Msg_LoaclCmdType:
      yb.insert(IO_Type(sigo_command , sptr_blob));
      break;
    default:
      break;
    }
  }
}