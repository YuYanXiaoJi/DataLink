#pragma once
#include<Adevs/adevs.h>
#include"blob.hpp"
#include"port.hpp"
namespace devs {
  //typedef devs::Port              PortType;
  typedef std::string             PortType;
  typedef std::int32_t            TimeType;
  typedef adevs::PortValue<SptrBlob, PortType> IO_Type;
  typedef adevs::Bag<IO_Type>      IO_Bag;

  typedef adevs::Digraph<SptrBlob, PortType, TimeType>  Digraph;
  typedef adevs::Simulator< IO_Type, TimeType>      Simulator;

  static  TimeType TIME_MAX = std::numeric_limits<TimeType>::max();
}