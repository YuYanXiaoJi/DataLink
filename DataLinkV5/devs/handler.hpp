#pragma once
#include"message/track_platform_type.hpp"
#include"typedef.hpp"
namespace devs {
	//��ҪΪ ����E �ṩ�ȴ�ʱ��
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
}