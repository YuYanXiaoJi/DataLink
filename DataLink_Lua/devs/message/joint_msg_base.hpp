#pragma once
#include"msg_type.hpp"
#include"track_platform_type.hpp"
#include"../core/typedef.hpp"

#include"../handler/track_number_handler.h"

#include<cstring>
#include<cstdint>
namespace devs::message {
  struct JointMsgBase
  {

    int32_t msg_type;
    char label[STR_MAX_LENGTH];
    char sub_label[STR_MAX_LENGTH];
    char track_number[STR_MAX_LENGTH];
//    char from[STR_MAX_LENGTH];
    TimeType  create_time;

    JointMsgBase( const char *_label , const char *_sub_label , const char *_track_number ,
                  /*const char *_from,*/TimeType _create_time,MsgType _msg_type = MsgType::Msg_JointMsgBase) {
      strcpy(label , _label);
      strcpy(sub_label , _sub_label);
      strcpy(track_number , _track_number);
 //     strcpy(from , _from);
      create_time = _create_time;
      msg_type = _msg_type;
    }

    std::string GetTrackName() {
      return handler::TrackNumberHandler::GetName(track_number);
    }
  };

}