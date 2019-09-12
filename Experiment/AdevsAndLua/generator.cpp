#include "generator.hpp"
#include"integer.hpp"
#include<iostream>
cc::Generator::Generator() {
  for (auto i : { 1,2,3,5,7,11,13 }) {
    buffer_list.push_back(devs::Blob::MakeShared(Integer(i)));
  }
}

void cc::Generator::External(const devs::PortType & recvPort, const devs::SptrBlob sptrBlob)
{
  buffer_list.push_front(sptrBlob);
}

void cc::Generator::Internal()
{
  buffer_list.pop_front();
}

void cc::Generator::Output(devs::IO_Bag & yb)
{
  auto & sptr_blob = buffer_list.front();
  auto & i = sptr_blob->get<Integer>();
  if (i.val == 1) {
    //yb.insert({ sendPrint,sptr_blob });
    std::cout << i.src << "\t" << i.inc << std::endl;
  }
  else if (i.val%2==1) {
    yb.insert(devs::IO_Type(odd, sptr_blob));
    //std::cout << i.src << "\t" << i.inc << std::endl;
  }
  else {
    yb.insert(devs::IO_Type(even, sptr_blob));
    //std::cout << i.src << "\t" << i.inc << std::endl;
  }
}

devs::TimeType cc::Generator::Ta()
{
  if (buffer_list.empty())
    return devs::TIME_MAX;
  else
    return 1;
}
