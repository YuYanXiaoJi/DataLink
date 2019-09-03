#pragma once
#include"msg_type.hpp"
#include"track_platform_type.hpp"
#include"../typedef.hpp"
#include<cstring>
#include<cstdint>
namespace devs::message {
  struct ActiveTrack
  {
    MsgType msg_type = MsgType::Msg_ActiveTrack;
    // 来源
    TrackPlatform  track_platform;

    // 航迹目标
    char  track_number[32];

    // 信号质量 越高越好
    int32_t track_quality;

    // 报文的创造时间
    TimeType  time_msec;

    ActiveTrack(const char* _track_number, TrackPlatform _track_platform,
      int32_t _track_quality, TimeType _time_msec) {

      strcpy(track_number, _track_number);
      track_quality = _track_quality;
      track_platform = _track_platform;
      time_msec = _time_msec;
    }

    inline bool operator < (const ActiveTrack& obj) const {
      return track_number < obj.track_number;
    }
  };
  struct TimeSlice
  {
    MsgType msg_type = MsgType::Msg_TimeSilce;
    TimeType begin_time;
    TimeType end_time;

    TimeSlice(TimeType _begin_time = -1, TimeType _end_time = -1) {
      begin_time = _begin_time;
      end_time = _end_time;
    }
  };

  struct SubTimeSlice
  {
    MsgType msg_type = MsgType::Msg_SubTimeSilce;
    TimeType begin_time;
    TimeType end_time;
    TimeType current_time;
    SubTimeSlice(TimeSlice ts,TimeType _current_time) {
      begin_time = ts.begin_time;
      end_time = ts.end_time;
      current_time = _current_time;
    }
  };

  enum LoaclCmdType
  {
      CMD_SET_R2      //设置 R2 
    , CMD_RM_R2        //移除 R2, RM = remove
    , CMD_BROADCAST_J3    //rB 通知 SUT 向外广播 track_name 的 J3报文
    , CMD_BROADCAST_J7    //发送J7 消息
  };

  struct LocalCmd {
    MsgType msg_type = MsgType::Msg_LocalMsg;
    uint8_t  cmd_id;
    char  track_name[32];

    LocalCmd(LoaclCmdType _cmd_id, const char* _track_name) {
      cmd_id = _cmd_id;
      strcpy(track_name, _track_name);
    }
  };
}