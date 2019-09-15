#pragma once
#include"joint_msg_base.hpp"
namespace devs::message {
  struct JointMsg3I :
    public JointMsgBase
  {
    TrackPlatform  track_platform;

    // 信号质量 越高越好
    int32_t track_quality;
    // STN指标
    int32_t _uSTN;

    JointMsg3I(
      const char *_track_number , const char *_from ,
      TrackPlatform _track_platform , int32_t _track_quality , TimeType _create_time , int32_t uSTN)
      :JointMsgBase("J3" , "0I" , _track_number,_from,_create_time, MsgType::Msg_JointMsg3I)
    {
      _uSTN = uSTN;
      track_platform = _track_platform;
      track_quality = _track_quality;
    }

  };

}