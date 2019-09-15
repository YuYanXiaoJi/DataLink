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
    // ͨ�� AbstractAtomic �̳�
    virtual void Input(const devs::IO_Type &x) override;
    virtual void Internal() override;
    virtual void Output(devs::IO_Bag &yb) override;
    virtual devs::TimeType Ta() override;

  public:
    //�㲥�˿�(˫��)
    const  PortType  port_broadcast=utility::Uid();   //���� �㲥<����,����>�Ķ˿�  
    const  PortType  port_abandon = -1;               //��������һЩ��Ч��Ϣ

    //˽�ж˿�(����)
    std::map<uint64_t, PortType> map_private_port;   //map<uid,private_port> 
    std::vector<std::shared_ptr<Ju>>     ary_ju;
  protected:
    util::MinPriorityQueue<handler::ScheduleBufferNode> priority_blob_queue;
    TimeType  time_division_interval = 100; //TDMA  ʱ��Ƭ��С  (ms)
    int       tdma_idx = 0;  //�� _PushNextTimeSlice �������Զ�����

  private:
    void m_PushNextTimeSlice();  //�����ɵ���һ�� ʱ��Ƭ ���� priority_blob_queue
  };

}