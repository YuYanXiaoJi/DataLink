#pragma once
#include"../message/message.hpp"
#include"../../utility/utility.hpp"
#include"../core/time.hpp"


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
  };
}