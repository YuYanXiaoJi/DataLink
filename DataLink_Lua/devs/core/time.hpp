#pragma once
#include"typedef.hpp"
namespace devs {
  class Time {
  private:
    static inline TimeType current_msec = 0;
  public:

    static inline TimeType Now()
    {
      return current_msec;
    }
    static inline TimeType Update(TimeType t)
    {
      current_msec = t;
      return t;
    }

    static inline TimeType Distance(TimeType t) {
      assert(( t - Now() ) >= 0); // t����Ҫ����|���� global_msec
      return t - Now();
    }
  };
}