#pragma once
#include"typedef.hpp"
namespace devs {
  class Time {
  private:
    static inline TimeType current_msec = 0;
  public:
  
    static inline TimeType now()
    {
      return current_msec;
    }
    static inline TimeType update(TimeType t)
    {
      current_msec = t;
    }

    static inline TimeType distance(TimeType t) {
      assert((t - now()) >= 0); // t必须要大于|等于 global_msec
      return t - now();
    }
  };
}