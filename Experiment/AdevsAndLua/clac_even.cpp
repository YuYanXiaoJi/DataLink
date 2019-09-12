#include "clac_even.hpp"
#include "integer.hpp"


cc::CalcEven::CalcEven(devs::Digraph & digrapg, Generator & parent)
  :Component(digrapg,parent)
{
  BindEven();
  BindSend();
}

void cc::CalcEven::External(const devs::PortType & recvPort, const devs::SptrBlob sptrBlob)
{
  buffer_list.push_back(sptrBlob);
}

void cc::CalcEven::Internal()
{
  buffer_list.pop_front();
}

void cc::CalcEven::Output(devs::IO_Bag & yb)
{
  auto & sptr_blob = buffer_list.front();
  auto & i = sptr_blob->get<Integer>();
  i.val = i.val /2;
  i.inc++;
  yb.insert(devs::IO_Type( send,sptr_blob ));
}

devs::TimeType cc::CalcEven::Ta()
{
  return buffer_list.empty()*devs::TIME_MAX;
}
