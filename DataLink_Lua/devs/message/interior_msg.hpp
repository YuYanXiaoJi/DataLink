#pragma once
#include"msg_type.hpp"
#include"track_platform_type.hpp"
#include"../core/typedef.hpp"
namespace devs::message {


  enum LoaclCmdType
  {
      CMD_SET_R2          //���� R2 
    , CMD_RM_R2           //�Ƴ� R2, RM = remove
    , CMD_BROADCAST_J3    //rB ֪ͨ SUT ����㲥 track_name �� J3����
    , CMD_BROADCAST_J7    //����J7 ��Ϣ
  };

  struct LocalCmd {
    int32_t   msg_type = MsgType::Msg_LocalCmd;
    int32_t   cmd_id;
    char  track_name[32];

    LocalCmd(int32_t _cmd_id , const char *_track_name) {
      cmd_id = _cmd_id;
      strcpy(track_name , _track_name);
    }
  };
}