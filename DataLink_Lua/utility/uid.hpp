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

  // ÿ�ζ�����һ���µĳ���Ψһ��UID
  const auto Uid = UidHander::Uid;
}