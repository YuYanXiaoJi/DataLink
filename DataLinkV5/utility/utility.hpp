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

    // �ж� val �Ƿ��� [left,right) ,�������,�ҿ�����
    template<typename Ty>
    bool isInRange(const Ty& left, const Ty&  val, const Ty& right) {
      return (left <= val) && (val < right);
    }
  
  }
}