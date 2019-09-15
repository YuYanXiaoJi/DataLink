#pragma once
namespace utility
{
  namespace math {
    // �ж� val �Ƿ��� [left,right) ,�������,�ҿ�����
    template<typename Ty> bool isInRange(const Ty &left , const Ty &val , const Ty &right) {
      return ( left <= val ) && ( val < right );
    }
  }
}