#pragma once
#include"msg_type.hpp"
#include"track_platform_type.hpp"
#include"../typedef.hpp"
#include"joint_msg_base.hpp"
#include<cstring>
#include<cstdint>
namespace devs::message {
  struct JointMsg2I :
    public JointMsgBase
  {

    // 航迹目标
    char  track_number[STR_MAX_LENGTH];

    char  from_sut_name[STR_MAX_LENGTH];
    uint8_t _uNPSI;    // 网络参与单元状态标识符

    // 报文的创造时间
    TimeType  time_msec;

    JointMsg2I(
      const char* _track_number, const char* _from_sut_name, uint8_t uNPSI,
      TimeType _time_msec)
      :JointMsgBase("J2", "0I", MsgType::Msg_JointMsg2I)
    {
      strcpy(track_number, _track_number);
      strcpy(from_sut_name, _from_sut_name);
      _uNPSI = uNPSI;
      time_msec = _time_msec;
    }

    inline bool operator < (const JointMsg2I& obj) const {
      return track_number < obj.track_number;
    }
  };
}