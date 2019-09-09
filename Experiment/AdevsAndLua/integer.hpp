#pragma once
#include<cstdint>
#include<memory>
namespace cc {
  class Integer{
  public:
    Integer(std::int32_t val) {
      this->src = val;
      this->val = val;
      this->inc = 0;
    }

    std::int32_t src;
    std::int32_t val;
    std::int32_t inc;

    template<class... _Types>
    [[nodiscard]] inline static auto MakeShared(_Types&&... _Args) {
      return std::make_shared<Integer>(_Args);
    }
  };


}