#pragma once
#include"../message/joint_msg_3.hpp"
#include"../message/local_msg.hpp"

#include<istream>
#include<ostream>


/*
  此头文件实现关于 使用 C++ ">>" & "<<" 对 message struct进行操作(读写)
*/

#pragma region TrackPlatform

istream & operator >>(istream &in , devs::message::TrackPlatform &tp) {
  std::string word;
  in >> word;
  if(word == "MARITIME") {
    tp = devs::message::TrackPlatform::Platform_MARITIME;
  }
  else if(word == "LAND") {

    tp = devs::message::TrackPlatform::Platform_LAND;
  }else if(word == "AIR") {

    tp = devs::message::TrackPlatform::Platform_AIR;
  }
  else {
    tp = devs::message::TrackPlatform::Platform_UNDEFINED;
    assert(false);
  }

  return in;
}


#pragma endregion


#pragma region LocalTrack

/*
define:
    char            track_number[STR_MAX_LENGTH];
    TrackPlatform   track_platform;
    int32_t         track_quality;
    TimeType        create_time;
*/

//顺序为 track_number , track_quality, track_platform, create_time
istream & operator >>(istream &in , devs::message::LocalTrack &lt) {
  in >> lt.track_number >> lt.track_platform >> lt.track_platform >> lt.create_time;
  return in;
}

#pragma endregion




#pragma region J3

/*
define:
    char              track_number[STR_MAX_LENGTH];
    TrackPlatform     track_platform;
    int32_t           track_quality;
    int32_t           _uSTN;
    TimeType          create_time;
*/

//顺序为 track_number , track_quality, track_platform,_uSTN, create_time
istream & operator >>(istream &in , devs::message::JointMsg3I &j3) {
  in >> j3.track_number >> j3.track_platform >> j3.track_quality >> j3._uSTN >> j3.create_time;
  return in;
}

#pragma endregion