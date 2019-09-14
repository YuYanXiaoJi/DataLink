#pragma once
#include"msg_type.hpp"
#include"joint_track_platform_type.hpp"
#include"joint_msg_base.hpp"
#include<cstring>
#include<cstdint>
namespace devs::message {
  //给字符串分配的空间
  const std::size_t STR_MAX_LENGTH = 32;

  struct JointMsgBase
  {

    MsgType msg_type;
    char label[STR_MAX_LENGTH];
    char sub_label[STR_MAX_LENGTH];
    char track_number[STR_MAX_LENGTH];


    JointMsgBase(const char *in_label , const char *in_sub_label , const char *in_track_number , MsgType _msg_type = MsgType::Msg_JointMsgBase) {
      strcpy(label , in_label);
      strcpy(sub_label , in_sub_label);
      strcpy(track_number , in_track_number);
      msg_type = _msg_type;
    }
  };
}