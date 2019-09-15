#pragma once
#include"abstract_atomic.hpp"
#include"../handler/schedule_buffer_node.hpp"
#include"../../utility/utility.hpp"

#include"ju.hpp"
namespace devs::core {
  class Hub
    :public AbstractAtomic
  {
  public:
    Hub(Digraph &_digraph , const std::string &_name);

    void AddJu(std::shared_ptr<Ju> sptr_ju);

    template<class Ty>void PushBuffer(TimeType schedule_time , PortType send_port , const Ty &msg) {
      priority_blob_queue.push(ScheduleBufferNode(schedule_time , IO_Type(send_port , util::Blob(msg))));
    }
  public:
    // 通过 AbstractAtomic 继承
    virtual void Input(const devs::IO_Type &x) override;
    virtual void Internal() override;
    virtual void Output(devs::IO_Bag &yb) override;
    virtual devs::TimeType Ta() override;

  public:
    //广播端口(双向)
    const  PortType  port_broadcast=utility::Uid();   //用于 广播<发送,接收>的端口  
    const  PortType  port_abandon = -1;               //用于抛弃一些无效消息

    //私有端口(单向)
    std::map<uint64_t, PortType> map_private_port;   //map<uid,private_port> 
    std::vector<std::shared_ptr<Ju>>     ary_ju;
  protected:
    util::MinPriorityQueue<handler::ScheduleBufferNode> priority_blob_queue;
    TimeType  time_division_interval = 100; //TDMA  时间片大小  (ms)
    int       tdma_idx = 0;  //在 _PushNextTimeSlice 函数中自动更新

  private:
    void m_PushNextTimeSlice();  //将生成的下一的 时间片 推入 priority_blob_queue
  };

}