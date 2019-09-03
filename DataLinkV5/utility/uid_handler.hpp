#pragma once
#include<atomic>
#include<functional>
namespace utility {
  class UidHander 
  {
  public:
    static inline std::atomic_uint32_t next_uid=1;
    static inline uint32_t NextUid() {
      return next_uid++;
    }
  };

  const std::function<uint32_t()> NextUid = UidHander::NextUid;
}



