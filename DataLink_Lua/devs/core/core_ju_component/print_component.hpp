#pragma once
#include"../ju_component.hpp"
namespace devs::core::ju_component {
  class PrintComponent 
    :public JuComponent
  {
  public:
    PrintComponent(Digraph & _digraph , Ju & _ju)
      :JuComponent(_digraph , _ju , "PrintComponent")
    {
      //BindInTS();
      BindInLT();
      BindInCMD();
      //BindInSTS();
    }

    __CREATOR__(PrintComponent);

    // Í¨¹ý JuComponent ¼Ì³Ð
    inline virtual void Input(const devs::IO_Type & x) override {
      std::cout << Time::Now() << "\tPrintComponent R:" << msg::GetMsgTypeName(x.value->blob_type<msg::MsgType>()) << std::endl;
    };

    inline virtual void Internal() override {};

    inline virtual void Output(devs::IO_Bag & yb) override {};

    inline virtual devs::TimeType Ta() override {
      return devs::TIME_MAX;
    };


   
  };



}