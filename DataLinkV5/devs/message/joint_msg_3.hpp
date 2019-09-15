#pragma once
#include"msg_type.hpp"
#include"track_platform_type.hpp"
#include"../typedef.hpp"
#include"joint_msg_base.hpp"
#include<cstring>
#include<cstdint>
namespace devs::message {
  struct JointMsg3I :
    public JointMsgBase
  {

    // ����Ŀ��
    char  track_number[STR_MAX_LENGTH];

   

    TrackPlatform  track_platform;

    // �ź����� Խ��Խ��
    int32_t track_quality;
    // STNָ��
    int32_t _uSTN;
    // ���ĵĴ���ʱ��
    TimeType  time_msec;

    JointMsg3I(
      const char* _track_number, const char* _from_sut_name,
      TrackPlatform _track_platform, int32_t _track_quality, TimeType _time_msec, int32_t uSTN)
      :JointMsgBase("J3", "0I", MsgType::Msg_JointMsg3I)
    {
      strcpy(track_number, _track_number);
      strcpy(from_sut_name, _from_sut_name);
      _uSTN = uSTN;
      track_platform = _track_platform;
      track_quality = _track_quality;
      time_msec = _time_msec;
    }

  };

}