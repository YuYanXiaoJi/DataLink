#include "calc_odd.hpp"
#include "integer.hpp"
cc::CalcOdd::CalcOdd()
{
}

void cc::CalcOdd::External(const devs::PortType & recvPort, const devs::SptrBlob sptrBlob)
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
  yb.insert({ send,sptr_blob });
  std::cout << i.src << "\t" << i.inc << std::endl;
}

devs::TimeType cc::CalcOdd::Ta()
{
  return buffer_list.empty()*devs::TIME_MAX;
}
