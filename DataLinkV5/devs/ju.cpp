#include "ju.hpp"
#include"time.hpp"
#include"ju_component.hpp"

// core component
#include"component/core_broadcast_component.hpp"
#include"component/core_j3_broadcast_handler.hpp"
#include"component/core_reporting_responsibility_handler.hpp"

//Verify
#include"component/verify_msg_component.hpp"

// extend
#include"component/RuleA.hpp"
#include"component/RuleC.hpp"
#include"component/RuleD.hpp"
#include"component/RuleE.hpp"
#include"component/RuleF.hpp"

//#include "component/RuleG.h"
//#include "component/RuleH.h"
//#include "component/RuleI.h"



std::shared_ptr<devs::Ju> devs::Ju::make_shared(devs::Digraph & _digraph, const std::string & _name, uint64_t _uid, int32_t _uSTN)
{
  return std::make_shared<devs::Ju>(_digraph, _name, _uid, _uSTN);
}

devs::Ju::Ju(Digraph & _digraph, const std::string & _name, uint64_t _uid, int32_t uSTN)
  :AtomicAbstract(_digraph, _name, _uid)
  //, portSelfRecv(util::NextUid())
  //, portSelfRecvToTranspond(util::NextUid())
  //, portSelfSendToTranspondBuffer(util::NextUid())
  //, portSelfSendCmd(util::NextUid())
  //, portSelfSendLT(util::NextUid())
  //, portSelfSendJ2(util::NextUid())
  //, portSelfSendJ3(util::NextUid())
  //, portSelfSendJ7(util::NextUid())
  //, portSelfSendTS(util::NextUid())
  //, portSelfSendSubTS(util::NextUid())
  //, portPrivateRecv(util::NextUid())
  //, portBroadcastSend(util::NextUid())
  //, portBroadcastRecv(util::NextUid())
  , _uSTN (uSTN)
{
  //AddComponent("Verify", component::CreatSptrVerifyMsgComponent(*this, digraph, "", util::NextUid()));


  AddComponent("CORE_R2", component::CreatSptrCoreReportingResponsibilityHandler (*this, digraph, "", util::NextUid()));
  AddComponent("CORE_Broadcast", component::CreatSptrCoreBroadcastComponent(*this, digraph, "", util::NextUid()));
  AddComponent("CORE_Broadcast_J3", component::CreatSptrCoreJ3BroadcastHandler(*this, digraph, "", util::NextUid()));

  AddComponent("RuleA", component::CreatSptrRuleA(*this, digraph, "", util::NextUid()));
  AddComponent("RuleC", component::CreatSptrRuleC(*this, digraph, "", util::NextUid()));
  AddComponent("RuleD", component::CreatSptrRuleD(*this, digraph, "", util::NextUid()));
  AddComponent("RuleE", component::CreatSptrRuleE(*this, digraph, "", util::NextUid()));
  AddComponent("RuleF", component::CreatSptrRuleF(*this, digraph, "", util::NextUid()));
}


//
std::tuple<bool, bool, bool> devs::Ju::GetExist(const std::string & track_name)
{
  bool is_exist_r2 = dict_r2.exist(track_name);
  bool is_exist_at = dict_active_track.exist(track_name);
  bool is_exist_rt = dict_recv_track.exist(track_name);
  return { is_exist_at, is_exist_rt, is_exist_r2 };
}

bool devs::Ju::CorrelationTest(const std::string& track_name)
{
  if (dict_active_track.exist(track_name) == true)
    return true;
  else
    return false;
}


void devs::Ju::delta_int()
{
  if (buffer_list.empty() == false)
  {
    buffer_list.pop_front();
  }else if (_time_slice_trigger_queue.empty() == false  && Time::distance(_time_slice_trigger_queue.top().schedule_time)==0)
  {
    _time_slice_trigger_queue.pop();
  }

}

void devs::Ju::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
  for (auto&iter : xb) {

    //Test RM  "||iter.port == this->portSelfRecv "
    if (
      iter.port == this->portBroadcastRecv
      || iter.port == this->portPrivateRecv) 
    {
      auto& blob = *iter.value;
      switch (blob.blob_type<msg::MsgType>())
      {
        case msg::MsgType::Msg_TimeSilce:
        {
          auto ts = blob.get<msg::TimeSlice>();
          this->time_silce = ts;
          for (auto t = ts.begin_time; t < ts.end_time; t += _time_slice_trigger_interval) {
            auto sptr_sts = util::CreateSptrBlob(msg::SubTimeSlice(ts, t));
            _time_slice_trigger_queue.push(ScheduleBufferNode(t, portSelfSendSubTS, sptr_sts));
          }
          break;
        }
        case msg::MsgType::Msg_LocalTrack:
        {
          auto& msg = blob.get<msg::LocalTrack>();
          auto track_name = TrackNumberHandler::GetName(msg.track_number);
          dict_active_track[track_name] = TrackInformation(msg, this->name);

          std::cout << Time::now() << "\t" << this->name << " R: LocalTrack\t" << msg.track_number<<std::endl;
          break;
        }
        case msg::MsgType::Msg_JointMsg3I:
        {
          auto& msg = blob.get<msg::JointMsg3I>();
          if (msg.from_sut_name == this->name) {
            return; // 自己的发出的消息.无视
          }
          auto track_name = TrackNumberHandler::GetName(msg.track_number);
          dict_recv_track[track_name] = TrackInformation(msg);
          std::cout << Time::now() << "\t" << this->name << " R: JointMsg3I\t" << msg.track_number << std::endl;
          break;
        }
        case msg::MsgType::Msg_JointMsg7I:
        {
          auto& msg = blob.get<msg::JointMsg7I>();
          if (msg.from_sut_name == this->name) {
            return; // 自己的发出的消息.无视
          }
          std::cout << Time::now() << "\t" << this->name << " R: JointMsg7I\t" << msg.track_number << std::endl;
          break;
        }
        case msg::MsgType::Msg_JointMsg2I:
          {
            auto& msg = blob.get<msg::JointMsg2I>();
            if (msg.from_sut_name == this->name) {
              return; // 自己的发出的消息.无视
            }
            break;
          }
        default:
          break;
      }
    }
    //最后再推入 buffer 
    buffer_list.push_back(iter);
  }
}

void devs::Ju::output_func(IO_Bag & yb)
{
  if (buffer_list.empty() == false) {
    auto&y = buffer_list.front();
    auto& blob = *y.value;

    if (y.port == this->portBroadcastRecv
      || y.port == this->portSelfRecv
      || y.port == this->portPrivateRecv)
    {
      switch (blob.blob_type<msg::MsgType>())
      {
      case msg::MsgType::Msg_LocalTrack:
      {
        //std::cout << name << "\t" << "Message::ActiveTrack" << std::endl;
        yb.insert(IO_Type{ portSelfSendLT,y.value });
        break;
      }

      case msg::MsgType::Msg_JointMsg3I:
      {
        //std::cout << name << "\t" << "Message::JointMsg3I" << std::endl;
        yb.insert(IO_Type{ portSelfSendJ3,y.value });
        break;
      }
      case msg::MsgType::Msg_JointMsg7I:
      {
        //std::cout << name << "\t" << "Message::JointMsg7I" << std::endl;
        yb.insert(IO_Type{ portSelfSendJ7,y.value });
        break;
      }
      case msg::MsgType::Msg_LocalMsg:
      {
        //std::cout << name << "\t" << "Message::LocalMsg" << std::endl;
        yb.insert(IO_Type{ portSelfSendCmd,y.value });
        break;
      }
      case msg::MsgType::Msg_TimeSilce:
      {
        //std::cout << name << "\t" << "Message::TimeSilce" << std::endl;
        yb.insert(IO_Type(portSelfSendTS, y.value));
        break;
      }
      case msg::MsgType::Msg_JointMsg2I:
      {
        //std::cout << name << "\t" << "Message::JointMsg2I" << std::endl;
        yb.insert(IO_Type{ portSelfSendJ2,y.value });
        break;
      }
      default:
      {
        //std::cout << name << "\t" << "Message::Unkown" << std::endl;
        break;
      }
      }

    }
    else if (y.port == this->portSelfRecvToTranspond) {
      yb.insert(IO_Type(portSelfSendToTranspondBuffer, y.value));
    }
    else if (y.port == portToBroadcast) {
      yb.insert(IO_Type(portBroadcastSend, y.value));

    }
  }else if (_time_slice_trigger_queue.empty() == false) {
    yb.insert(_time_slice_trigger_queue.top().io_buffer);
  }
  
}

devs::TimeType devs::Ju::ta()
{
  if (buffer_list.empty() == false) {
    return 0;
  }
  else if (_time_slice_trigger_queue.empty() == false) {
    return  Time::distance(_time_slice_trigger_queue.top().schedule_time);
  }
  else {
    return TIME_MAX;
  }
}


