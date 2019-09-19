#pragma once
#include <cstdint>
#include <cstddef>
namespace devs::message {


  enum MsgType
  {
#define __Msg__(name) Msg_##name , /* Msg_$Name */
#include"msg_type_name.def"
#undef __Msg__
  };



  inline std::string GetMsgTypeName(MsgType val) {
    switch(val)
    {
#define __Msg__(name) case devs::message::Msg_##name : return "Msg_"#name; 
#include"msg_type_name.def"
#undef __Msg__
    default:
      return "Unknow";
    }
  }

}
