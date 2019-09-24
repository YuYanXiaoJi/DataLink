#include "calc_odd.hpp"
#include "integer.hpp"


cc::CalcOdd::CalcOdd(devs::Digraph & digrapg, Generator & parent)
  :Component(digrapg,parent)
{
  BindOdd();
  BindSend();
}

void cc::CalcOdd::Input(const devs::PortType & recvPort, const SptrBlob sptrBlob)
{
  buffer_list.push_back(sptrBlob);
}

void cc::CalcOdd::Internal()
{
  buffer_list.pop_front();
}

void cc::CalcOdd::Output(devs::IO_Bag & yb)
{
  auto & sptr_blob = buffer_list.front();
  auto & i = sptr_blob->get<Integer>();
  i.val = i.val * 3 + 1;
  i.inc++;
  yb.insert(devs::IO_Type(send, sptr_blob));

}

devs::TimeType cc::CalcOdd::Ta()
{
  return buffer_list.empty()*devs::TIME_MAX;
}
