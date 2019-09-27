#pragma once
#include"../message/msg_type.hpp"
#include"../message/track_platform_type.hpp"
#include"../message/interior_msg.hpp"
#include"../core/ju_component.hpp"
/*
  由于 LuaBridge 不支持 c++ enum 类型 
 2019年9月24日 
  ->将 msg_type  与 track_platform_type 在这个内中实现为static int32_t 类型,以供 lua 使用.
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
    
    //JuComponent Recv Port
    inline static int32_t SigI_BB = core::JuComponent::sigi_broadcast_buffer;
    inline static int32_t SigI_TS = core::JuComponent::sigi_ts;
    inline static int32_t SigI_STS = core::JuComponent::sigi_sts;
    inline static int32_t SigI_CMD = core::JuComponent::sigi_cmd;
    inline static int32_t SigI_LT = core::JuComponent::sigi_lt;
    inline static int32_t SigI_J2 = core::JuComponent::sigi_j2;
    inline static int32_t SigI_J3 = core::JuComponent::sigi_j3;
    inline static int32_t SigI_J7 = core::JuComponent::sigi_j7;

    //Const
    inline static TimeType TIME_MAX = devs::TIME_MAX;
  };
}