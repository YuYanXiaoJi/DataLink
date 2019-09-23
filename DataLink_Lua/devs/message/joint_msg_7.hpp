#pragma once
#include"joint_msg_base.hpp"
namespace devs::message {
  struct JointMsg7I :
    public JointMsgBase
  {
    uint8_t action;  //ACT

    JointMsg7I(
      const char *_track_number , /*const char *_from ,*/ uint8_t _action ,
      TimeType _create_msec)
      :JointMsgBase("J7" , "0I" , _track_number,/* _from,*/ _create_msec, MsgType::Msg_JointMsg7I)
    {
      action = _action;
    }

  };

}