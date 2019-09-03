#pragma once
namespace devs::message {

  enum class MsgType :std::uint8_t
  {
    Msg_JointMsgBase,
    Msg_JointMsg3I, 
    Msg_JointMsg7I,
    Msg_JointMsg2I,
    //////////////////////
    Msg_ActiveTrack,
    Msg_MissingTrack,
    Msg_TimeSilce,
    Msg_SubTimeSilce,
    //////////////////////
    Msg_LocalMsg,
    //////////////////////
    Msg_VerifyMsg,
    Msg_VerifyCalc,
  };

  //给字符串分配的空间
  const std::size_t STR_MAX_LENGTH = 32;
}