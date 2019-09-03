#pragma once
#include"msg_type.hpp"
#include"track_platform_type.hpp"
#include"../typedef.hpp"
#include"joint_msg_base.hpp"
#include<cstring>
#include<cstdint>
namespace devs::message {
  struct JointMsg7I :
    public JointMsgBase
  {

    // 航迹目标
    char  track_number[STR_MAX_LENGTH];

    char  from_sut_name[STR_MAX_LENGTH];
    uint8_t action;  //ACT

    // 报文的创造时间
    TimeType  time_msec;

    JointMsg7I(
      const char* _track_number, const char* _from_sut_name, uint8_t _action,
      TimeType _time_msec)
      :JointMsgBase("J7", "0I", MsgType::Msg_JointMsg7I)
    {
      strcpy(track_number, _track_number);
      strcpy(from_sut_name, _from_sut_name);
      action = _action;
      time_msec = _time_msec;
    }

    inline bool operator < (const JointMsg7I& obj) const {
      return track_number < obj.track_number;
    }
  };

}