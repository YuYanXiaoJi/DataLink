#pragma once
#include"msg_type.hpp"
#include"track_platform_type.hpp"
#include"../typedef.hpp"
#include<cstring>
#include<cstdint>
namespace devs::message {
  struct JointMsgBase
  {

    MsgType msg_type;
    char label[STR_MAX_LENGTH];
    char sub_label[STR_MAX_LENGTH];

    JointMsgBase(const char* in_label, const char* in_sub_label, MsgType _msg_type =  MsgType::Msg_JointMsgBase) {
      strcpy(label, in_label);
      strcpy(sub_label, in_sub_label);
      msg_type = _msg_type;
    }
  };

}
