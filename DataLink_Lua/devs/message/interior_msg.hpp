#pragma once
#include"msg_type.hpp"
#include"track_platform_type.hpp"
#include"../core/typedef.hpp"
namespace devs::message {


  enum LoaclCmdType
  {
      CMD_SET_R2          //设置 R2 
    , CMD_RM_R2           //移除 R2, RM = remove
    , CMD_BROADCAST_J3    //rB 通知 SUT 向外广播 track_name 的 J3报文
    , CMD_BROADCAST_J7    //发送J7 消息
  };

  struct LocalCmd {
    MsgType msg_type = MsgType::Msg_LoaclCmdType;
    uint8_t  cmd_id;
    char  track_name[32];

    LocalCmd(LoaclCmdType _cmd_id , const char *_track_name) {
      cmd_id = _cmd_id;
      strcpy(track_name , _track_name);
    }
  };
}