#pragma once
#include"../message/message.hpp"
#include"../../utility/utility.hpp"
#include"../core/time.hpp"
#include"time_interval_handler.hpp"


/// 整理工具函数
namespace devs::handler {
  class FuncWrapper {
  public:
    inline static int64_t Now(){
      return Time::Now();
    } 
    inline static std::string GetMsgName(int32_t msg_type) {
      return message::GetMsgName(msg_type);
    }
    inline static int64_t GetMinBroadcastInterval(int32_t track_plotform) {
      return time_interval_handler::GetMinBroadcastInterval(track_plotform);
    }
    inline static int64_t GetWaitInterval(int32_t track_plotform) {
      return time_interval_handler::GetWaitInterval(track_plotform);
    }
  };
}