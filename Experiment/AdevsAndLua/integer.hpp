#pragma once
#include<cstdint>
#include<memory>
namespace cc {
  enum MsgType
  {
    MSG_Integer=100
  };

  class Integer{
  public:
    Integer(std::int32_t val) {
      this->src = val;
      this->val = val;
      this->inc = 0;
    }
    uint8_t type = MsgType::MSG_Integer;
    std::int32_t src;
    std::int32_t val;
    std::int32_t inc;
    inline static std::int32_t t=100;
    template<class... _Types>
    [[nodiscard]] inline static auto MakeShared(_Types&&... _Args) {
      return std::make_shared<Integer>(_Args);
    }
  };


}