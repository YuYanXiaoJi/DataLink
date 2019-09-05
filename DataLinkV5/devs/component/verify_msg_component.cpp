#include "verify_msg_component.hpp"

#include<iostream>
devs::component::VerifyMsgComponent::VerifyMsgComponent(Ju & ju, Digraph & digraph, const std::string & name, PortType uid)
  :JuComponent(ju, digraph, name, uid)
{
  BindSelfRecvSubTS();

}

void devs::component::VerifyMsgComponent::delta_int()
{

}

void devs::component::VerifyMsgComponent::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
  for (auto&x : xb) {
    if (x.port == GetSelfRecvSubTS()) {
      std::cout << "sub_time_slice\t" << x.value->get<msg::SubTimeSlice>().current_time << std::endl;
    }
  
  }

}

void devs::component::VerifyMsgComponent::output_func(IO_Bag & yb)
{
}

devs::TimeType devs::component::VerifyMsgComponent::ta()
{
  return TIME_MAX;
}
