#pragma once
#include<Adevs/adevs.h>
#include"blob.hpp"
#include"port.hpp"
namespace devs {
  typedef devs::Port              PortType;
  typedef std::int64_t            TimeType;
  typedef adevs::PortValue<SptrBlob, PortType> IO_Type;
  typedef adevs::Bag<IO_Type>      IO_Bag;

  typedef adevs::Digraph<SptrBlob, PortType, TimeType>  Digraph;
  typedef adevs::Simulator< IO_Type, TimeType>      Simulator;

  constexpr TimeType TIME_MAX = std::numeric_limits<TimeType>::max();
}