#pragma once
#include"msg_type.hpp"
#include"track_platform_type.hpp"
#include"../core/typedef.hpp"

namespace devs::message {
  struct LocalTrack
  {
    int32_t msg_type = MsgType::Msg_LocalTrack;
    // 来源
    TrackPlatform  track_platform;
    // 航迹目标
    char  track_number[STR_MAX_LENGTH];
    // 信号质量 越高越好
    int32_t track_quality;
    // 报文的创造时间
    TimeType  create_time;

    LocalTrack(const char *_track_number , TrackPlatform _track_platform ,int32_t _track_quality , TimeType _create_time) {
      strcpy(track_number , _track_number);
      track_quality = _track_quality;
      track_platform = _track_platform;
      create_time =  _create_time;
    }

    std::string GetTrackName() {
      return handler::TrackNumberHandler::GetName(track_number);
    }
  };

  struct TimeSlice
  {
    int32_t msg_type = MsgType::Msg_TimeSlice;
    TimeType begin_time;
    TimeType end_time;

    TimeSlice(TimeType _begin_time = -1 , TimeType _end_time = -1) {
      begin_time = _begin_time;
      end_time = _end_time;
    }
  };

  struct SubTimeSlice
  {
    int32_t msg_type = MsgType::Msg_SubTimeSlice;
    TimeType begin_time;
    TimeType end_time;
    TimeType current_time;
    SubTimeSlice(TimeSlice ts , TimeType _current_time) {
      begin_time = ts.begin_time;
      end_time = ts.end_time;
      current_time = _current_time;
    }
  };

}