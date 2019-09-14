#pragma once
#include<atomic>
namespace utility {
  class UidHander
  {
  public:
    static inline std::atomic_uint32_t next_uid = 1;
    static inline uint32_t Uid() {
      return next_uid++;
    }
  };

  // 每次都分配一个新的程序唯一的UID
  const auto Uid = UidHander::Uid;
}