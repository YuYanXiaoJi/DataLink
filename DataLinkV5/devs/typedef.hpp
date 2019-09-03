#pragma once
#include<Adevs/adevs.h>
#include"../utility/utility.hpp"
namespace devs {
  typedef int32_t            PortType;
  typedef int64_t            TimeType;
  typedef adevs::PortValue<util::SptrBlob, PortType> IO_Type;
  typedef adevs::Bag<IO_Type>      IO_Bag;

  typedef adevs::Digraph<util::SptrBlob, PortType, TimeType>  Digraph;
  typedef adevs::Simulator< IO_Type, TimeType>      Simulator;

  const TimeType  TIME_MAX = std::numeric_limits<TimeType>::max();

  /// SUT
  const TimeType kWaitTimeFromMaritime    = 40'000;  // ˮ�� 40s
  const TimeType kWaitTimeFromAir        = 40'000;  // ���� 40s
  const TimeType kWaitTimeFromLand      = 120'000;  // ½�� 120s
  const TimeType kBroadcastInterval_Maritime  = 12'000;  // 12��
  const TimeType kBroadcastInterval_Air    = 12'000;  // 12��
  const TimeType kBroadcastInterval_Land    = 48'000;  // 48��
  const TimeType kThresholdTQ          = 2;    // TQ��ֵ

}