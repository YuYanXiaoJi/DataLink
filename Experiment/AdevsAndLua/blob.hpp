#pragma once

#include<vector>
#include<cstdint>
#include<memory>


  //binary large object
  class Blob :public std::vector<std::uint8_t> {
  public:
    Blob() {/*pass*/ }

    template<class Ty> Blob(const Ty& _ojb)
    {
      this->resize(sizeof(Ty));
      std::memcpy(this->data(), &_ojb, sizeof(Ty));
    }

    template<class Ty>
    inline Ty& get() {
      return *reinterpret_cast<Ty*>(data());
    }

    template<class Ty>
    inline const Ty& get() const {
      return *reinterpret_cast<const Ty*>(data());
    }

    template<class Ty>
    inline static const Blob from(const Ty& _ojb) {
      Blob buff;
      buff.resize(sizeof(Ty));
      std::memcpy(buff.data(), &_ojb, sizeof(Ty));
      return buff;
    }

    template<class Ty>
    inline static std::shared_ptr<Blob> MakeShared(const Ty& _ojb) {
      return std::make_shared<Blob>(_ojb);
    }

    template<class Ty> Ty top()
    {
      return *reinterpret_cast<Ty*>(data());
    }
  };
  typedef std::shared_ptr<Blob> SptrBlob;
  
