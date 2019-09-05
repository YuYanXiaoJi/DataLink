#pragma once
#include"typedef.hpp"
namespace devs {
  class ScheduleBufferNode
  {
  public:
    TimeType  schedule_time;//∑¢ÀÕ ±º‰
    IO_Type    io_buffer;

    ScheduleBufferNode(TimeType _schedule_time, IO_Type _io_buffer) {
      schedule_time = _schedule_time;
      io_buffer = _io_buffer;
    }

    ScheduleBufferNode(TimeType _schedule_time, PortType _port, util::SptrBlob _sptr_blob) {
      schedule_time = _schedule_time;
      io_buffer = IO_Type(_port, _sptr_blob);
    }

    bool operator < (const ScheduleBufferNode& other)const {
      return schedule_time < other.schedule_time;
    }

    bool operator > (const ScheduleBufferNode& other)const {
      return schedule_time > other.schedule_time;
    }
  };
}