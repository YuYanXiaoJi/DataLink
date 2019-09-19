#include "hub.hpp"

namespace devs::core {
  Hub::Hub(Digraph &_digraph , const std::string &_name):AbstractAtomic(_digraph,_name){
    this->m_PushNextTimeSlice();
  }

  void Hub::AddJu(std::shared_ptr<Ju> sptr_ju)
  {
    ary_ju.push_back(sptr_ju);

    //�󶨹㲥�˿�
    digraph.couple(this , this->sigio_broadcast , sptr_ju.get() , sptr_ju->sigio_hub);  // HUB  -->  JU
    digraph.couple(sptr_ju.get() , sptr_ju->sigio_hub , this , this->sigio_broadcast);  // JU  -->  HUB

    //��˽�ж˿�
    map_private_port[sptr_ju->uid] = util::Uid();  //���� HUB ��JU �󶨵Ķ˿�
    digraph.couple(this , map_private_port[sptr_ju->uid] , sptr_ju.get() , sptr_ju->sigio_hub);  //  HUB(private)->JU(private)

  }

  void Hub::Input(const devs::IO_Type &x){
    if(x.port == this->sigio_broadcast)
      PushBuffer(Time::Now() , this->sigio_broadcast , x.value);
    else
      assert(false/*ֻ���յ� ����ȫ��ת������Ϣ*/);
  }

  void Hub::Internal(){
    priority_blob_queue.pop();
  }

  void Hub::Output(devs::IO_Bag &yb){
    auto &y = priority_blob_queue.top();
    yb.insert(y.io_buffer);

    if(y.io_buffer.value->at(0) == msg::MsgType::Msg_TimeSlice)
    {
      //�ж��Ƿ��͵���ʱ��Ƭ,�����,�ͽ��µ�ʱ��Ƭ���뷢�Ͷ�����
      this->m_PushNextTimeSlice();
    }
  }

  devs::TimeType Hub::Ta(){
    if(priority_blob_queue.empty())
      return TIME_MAX;
    return  Time::Distance(priority_blob_queue.top().schedule_time);
  }

  void Hub::m_PushNextTimeSlice(){
    PortType port;
    if(ary_ju.empty())
      port = sig_abandon;
    else {
      int idx = this->tdma_idx % ary_ju.size();
      port = map_private_port[ary_ju[idx]->uid];
    }
    auto msg = msg::TimeSlice(tdma_idx * time_division_interval , ( tdma_idx + 1 ) * time_division_interval);
    tdma_idx++;
    PushBuffer(msg.begin_time , port , msg);
  }
}