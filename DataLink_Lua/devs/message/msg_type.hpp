#pragma once
#include <cstdint>
#include <cstddef>
namespace devs::message {

  enum MsgType
  {
    Msg_JointMsgBase ,
    Msg_JointMsg3I ,
    Msg_JointMsg7I ,
    Msg_JointMsg2I ,
    //////////////////////
    Msg_LocalTrack ,
    Msg_MissingTrack ,
    Msg_TimeSilce ,
    Msg_SubTimeSilce ,
    //////////////////////
    Msg_LocalMsg ,
    //////////////////////
    Msg_VerifyMsg ,
    Msg_VerifyCalc ,
  };


}