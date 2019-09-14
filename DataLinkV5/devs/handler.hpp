#pragma once
#include"message/track_platform_type.hpp"
#include"typedef.hpp"
namespace devs {
  //主要为 规则E 提供等待时间
  inline TimeType GetWaitInterval(message::TrackPlatform track_platform) {
    using namespace message;
    TimeType t = TIME_MAX;
    if (track_platform == Platform_AIR) t = kWaitTimeFromAir;
    else if (track_platform == Platform_LAND) t = kWaitTimeFromLand;
    else if (track_platform == Platform_MARITIME) t = kWaitTimeFromMaritime;
    else assert(false/*you kown*/);
    return t;
  }

  inline TimeType GetMinBroadcastInterval(message::TrackPlatform track_platform) {
    using namespace message;
    TimeType t = TIME_MAX;
    if (track_platform == Platform_AIR) t = kBroadcastInterval_Air;
    else if (track_platform == Platform_LAND) t = kBroadcastInterval_Land;
    else if (track_platform == Platform_MARITIME) t = kBroadcastInterval_Maritime;
    else assert(false/*you kown*/);
    return t;
  }

  namespace TrackNumberHandler
  {
    inline std::string Create(const std::string &name) {
      static std::atomic_uint32_t inc = 0;
      char buff[32];
      sprintf(buff , "%s-%08X" , name.c_str() , inc++);
      return std::string(buff);
    }

    inline std::string GetName(const std::string &track_number) {
      int index = track_number.find_last_of('-');
      return track_number.substr(0 , index);
    }
  }
}