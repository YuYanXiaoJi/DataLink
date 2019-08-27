#pragma once
#include"typedef.hpp"
namespace devs {
	class global {
	public:
		static inline TimeType global_msec=0;
		static inline TimeType distance(TimeType t) {
			assert((t - global_msec) >= 0); // t必须要大于|等于 global_msec
			return t - global_msec;
		}
	};
}