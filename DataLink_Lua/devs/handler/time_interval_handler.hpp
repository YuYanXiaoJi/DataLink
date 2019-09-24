#pragma once
#include"../core/typedef.hpp"
#include"../message/track_platform_type.hpp"
namespace devs::handler {
  namespace time_interval_handler {
    //主要为 规则E 提供等待时间
    inline TimeType GetWaitInterval(uint32_t track_platform) {
      using namespace message;
      TimeType t = TIME_MAX;
      if(track_platform == Platform_AIR) t = kWaitTimeFromAir;
      else if(track_platform == Platform_LAND) t = kWaitTimeFromLand;
      else if(track_platform == Platform_MARITIME) t = kWaitTimeFromMaritime;
      else assert(false/*you kown*/);
      return t;
    }

    inline TimeType GetMinBroadcastInterval(uint32_t track_platform) {
      using namespace message;
      TimeType t = TIME_MAX;
      if(track_platform == Platform_AIR) t = kBroadcastInterval_Air;
      else if(track_platform == Platform_LAND) t = kBroadcastInterval_Land;
      else if(track_platform == Platform_MARITIME) t = kBroadcastInterval_Maritime;
      else assert(false/*you kown*/);
      return t;
    }
  };
}