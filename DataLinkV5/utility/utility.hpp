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


  namespace math {

    // 判断 val 是否在 [left,right) ,左闭区间,右开区间
    template<typename Ty>
    bool isInRange(const Ty& left, const Ty&  val, const Ty& right) {
      return (left <= val) && (val < right);
    }
  
  }
}