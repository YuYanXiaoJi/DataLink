#pragma once
#include"blob.hpp"
#include"priority_queue.hpp"
#include"sync/list.hpp"
#include"sync/map.hpp"
#include"uid_handler.hpp"
#include<atomic>
#include<cstdio>
namespace  util = utility;
namespace utility
{
  namespace TrackNumberHandler
  {
    inline std::string Create(const std::string & name) {
      static std::atomic_uint32_t inc = 0;
      char buff[32];
      sprintf(buff, "%s-%08X", name.c_str(), inc++);
      return std::string(buff);
    }

    inline std::string GetName(const std::string& track_number) {
      int index = track_number.find_last_of('-');
      return track_number.substr(0, index);
    }
  }

  namespace math {

    // 判断 val 是否在 [left,right) ,左闭区间,右开区间
    template<typename Ty>
    bool isInRange(const Ty& left, const Ty&  val, const Ty& right) {
      return (left <= val) && (val < right);
    }
  
  }
}