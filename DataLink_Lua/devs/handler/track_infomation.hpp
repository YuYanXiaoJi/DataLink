#pragma once
#include"track_number_handler.h"
#include"../message/message.hpp"
#include"../../utility/utility.hpp"
#include"../core/time.hpp"
#include<string>
namespace devs::handler {
  struct TrackInformation
  {
    std::string track_number;
    //std::string from;

    msg::TrackPlatform  track_platform;
    int32_t             track_quality;
    int32_t             _uSTN;

    TimeType  create_time;

    TrackInformation()
    {
      track_number = "";
      //from = "";
      track_platform = msg::Platform_UNDEFINED;
      track_quality = -1;
      create_time = -1;
    }

    TrackInformation(const msg::LocalTrack &at , const std::string &sut_name) {
      track_number = at.track_number;
      //from = sut_name;
      track_platform = at.track_platform;
      track_quality = at.track_quality;
      create_time = at.create_time;
    }

    TrackInformation(const msg::JointMsg3I &j30i) {
      track_number = j30i.track_number;
      //from = j30i.from;
      track_platform = j30i.track_platform;
      track_quality = j30i.track_quality;
      create_time = j30i.create_time;
      _uSTN = j30i._uSTN;
    }

    template<class Ty> Ty Get(bool is_create_new = true) {
      static_assert(false,"该类型不在生成范围内!!!");
      return Ty();
    }


  };
}



namespace devs::handler {


  template <> inline devs::msg::JointMsg3I  TrackInformation::Get(bool is_create_new) {

    std::string t_track_number = this->track_number;
    if(is_create_new)
      t_track_number = TrackNumberHandler::Create(TrackNumberHandler::GetName(t_track_number));

    auto ojb = msg::JointMsg3I(
      t_track_number.c_str() ,
     // this->from.c_str() ,
      this->track_platform ,
      this->track_quality ,
      this->create_time ,
      this->_uSTN
    );

    if(is_create_new)
      ojb.create_time = Time::Now();
    return ojb;
  }
}