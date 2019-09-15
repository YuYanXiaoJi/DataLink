#pragma once
#include<string>
#include<atomic>
namespace devs::handler {
  class TrackNumberHandler
  {
  public:
    inline static std::string Create(const std::string &name) {
      static std::atomic_uint32_t inc = 0;
      char buff[64];
      sprintf(buff , "%s-%08X" , name.c_str() , inc++);
      return std::string(buff);
    }

    inline static std::string GetName(const std::string &track_number) {
      int index = track_number.find_last_of('-');
      return track_number.substr(0 , index);
    }
  };
}