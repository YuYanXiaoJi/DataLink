#pragma once
#include"../core/typedef.hpp"
namespace devs::handler {
  class ScheduleBufferNode
  {
  public:
    TimeType  schedule_time;//∑¢ÀÕ ±º‰
    IO_Type   io_buffer;


    ScheduleBufferNode(devs::TimeType _schedule_time , devs::IO_Type _io_buffer) {
      schedule_time = _schedule_time;
      io_buffer = _io_buffer;
    }

    ScheduleBufferNode(devs::TimeType _schedule_time , devs::PortType _port , devs::ValueType _sptr_blob) {
      schedule_time = _schedule_time;
      io_buffer = IO_Type(_port , _sptr_blob);
    }

    bool operator < (const devs::handler::ScheduleBufferNode &other)const {
      return schedule_time < other.schedule_time;
    }

    bool operator > (const devs::handler::ScheduleBufferNode &other)const {
      return schedule_time > other.schedule_time;
    }
  };
}