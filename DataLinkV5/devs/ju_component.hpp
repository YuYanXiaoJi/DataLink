#pragma once
#include"atomic.hpp"
#include"ju.hpp"
#include"typedef.hpp"
#include"../utility/utility.hpp"

namespace devs {
  class JuComponent 
    :public AtomicAbstract
  {
  protected:
    JuComponent(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid)
      :AtomicAbstract(_digraph, _name, _uid)
      , parent(ju)
    {
      digraph.couple(this, this->port_self_send, &ju, ju.port_self_recv); //���͸�Ju
      digraph.couple(this, this->port_self_send_to_transpond, &ju, ju.port_self_recv_to_transpond); //���͸�Ju

      digraph.couple(&ju, ju.port_self_send_cmd, this, this->port_self_recv_cmd);
      digraph.couple(&ju, ju.port_self_send_at, this, this->port_self_recv_at);
      digraph.couple(&ju, ju.port_self_send_j2, this, this->port_self_recv_j2);
      digraph.couple(&ju, ju.port_self_send_j3, this, this->port_self_recv_j3);
      digraph.couple(&ju, ju.port_self_send_j7, this, this->port_self_recv_j7);
      digraph.couple(&ju, ju.port_self_send_ts, this, this->port_self_recv_ts);
      digraph.couple(&ju, ju.port_self_send_sub_ts, this, this->port_self_recv_sub_ts);
    }
  public:
    // ͨ�� Atomic �̳�
    virtual void delta_int() = 0;
    virtual void delta_ext(devs::TimeType e, const IO_Bag& xb) = 0;
    virtual void output_func(IO_Bag& yb) = 0;
    virtual devs::TimeType ta() = 0;

  public:
    Ju & parent;

   
  public:
    inline void BindSelfSendPort() {
      digraph.couple(this, this->port_self_send, &parent, parent.port_self_recv); //���͸�Ju
    }

  private:
    /*��Component ����ʹ��*/

    //�ڲ�ʹ�õĽ��ն˿�
    PortType    port_self_send              = util::NextUid();

    PortType    port_self_send_to_transpond = util::NextUid();
    //CMD ת��
    PortType    port_self_recv_cmd= util::NextUid();
    //Active Track ��Ϣת��
    PortType    port_self_recv_at = util::NextUid();
    //J_2 ��Ϣת��
    PortType    port_self_recv_j2 = util::NextUid();
    //J_3 ��Ϣת��
    PortType    port_self_recv_j3 = util::NextUid();
    //J_7 ��Ϣת��
    PortType    port_self_recv_j7 = util::NextUid();
    //TimeSlice ��Ϣת��
    PortType    port_self_recv_ts = util::NextUid();;
    //Sub TimeSlice ��Ϣת��
    PortType    port_self_recv_sub_ts = util::NextUid();;
    



  };

}

#define _FUNC_MakeShared_(CLASS_NAME) static inline auto  make_shared(Ju& ju, Digraph& digraph, const std::string&name, PortType uid)  {return std::make_shared<CLASS_NAME>(ju, digraph, name, uid);};

#define _FUNC_CreatSptr_(CLASS_NAME) const auto CreatSptr##CLASS_NAME=CLASS_NAME::make_shared;
