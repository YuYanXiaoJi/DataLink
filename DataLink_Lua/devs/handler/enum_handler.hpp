#pragma once
#include"../message/msg_type.hpp"
#include"../message/track_platform_type.hpp"

/*
  ���� LuaBridge ��֧�� c++ enum ���� 
 2019��9��24�� 
  ->�� msg_type  �� track_platform_type ���������ʵ��Ϊstatic int32_t ����,�Թ� lua ʹ��.
*/

namespace devs::handler {
  class EnumWrapper {
  public:
    //TrackPlatform
    inline static int32_t Platform_UNDEFINED  = message::Platform_UNDEFINED;
    inline static int32_t Platform_MARITIME   = message::Platform_MARITIME;
    inline static int32_t Platform_LAND       = message::Platform_LAND;
    inline static int32_t Platform_AIR        = message::Platform_AIR;

    //MsgType
    inline static int32_t Msg_TimeSlice = message::Msg_TimeSlice;
    inline static int32_t Msg_SubTimeSlice = message::Msg_SubTimeSlice;
    inline static int32_t Msg_JointMsgBase = message::Msg_JointMsgBase;
    inline static int32_t Msg_JointMsg2I = message::Msg_JointMsg2I;
    inline static int32_t Msg_JointMsg3I = message::Msg_JointMsg3I;
    inline static int32_t Msg_JointMsg7I = message::Msg_JointMsg7I;
    inline static int32_t Msg_LocalTrack = message::Msg_LocalTrack;
    inline static int32_t Msg_LoaclCmd = message::Msg_LocalCmd;

    //LoaclCmdType
    inline static int32_t CMD_SET_R2 = message::CMD_SET_R2;
    inline static int32_t CMD_RM_R2 = message::CMD_RM_R2;
    inline static int32_t CMD_BROADCAST_J3 = message::CMD_BROADCAST_J3;
    inline static int32_t CMD_BROADCAST_J7 = message::CMD_BROADCAST_J7;

    inline static TimeType TIME_MAX = devs::TIME_MAX;
  };
}