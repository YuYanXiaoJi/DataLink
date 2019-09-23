#pragma once
#include"joint_msg_base.hpp"
namespace devs::message {
  struct JointMsg2I :
    public JointMsgBase
  {
    uint8_t _uNPSI;    // 网络参与单元状态标识符

    JointMsg2I(
      const char *_track_number /*, const char *_from*/ , uint8_t uNPSI ,
      TimeType _create_time)
      :JointMsgBase("J2" , "0I" , _track_number,/* _from,*/ _create_time , MsgType::Msg_JointMsg2I)
    {
      _uNPSI = uNPSI;
    }

  };
}