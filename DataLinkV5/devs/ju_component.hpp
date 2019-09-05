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
      BindPortSelfSend();
      BindSelfSendToTranspond();
    }
  public:
    // 通过 Atomic 继承
    virtual void delta_int() = 0;
    virtual void delta_ext(devs::TimeType e, const IO_Bag& xb) = 0;
    virtual void output_func(IO_Bag& yb) = 0;
    virtual devs::TimeType ta() = 0;

  public:
    Ju & parent;

   
  private:

    /*
      端口
    */

    /*与Component 传输使用*/
    static const PortType kPortUndefine=std::numeric_limits<PortType>::min();

    PortType    portSelfSendToTranspond = kPortUndefine;

    //内部使用的接收端口
    PortType    portSelfSend = kPortUndefine;

    //CMD 转发
    PortType    portSelfRecvCmd= kPortUndefine;
    //Active Track 消息转发
    PortType    portSelfRecvLT = kPortUndefine;
    //J_2 消息转发
    PortType    portSelfRecvJ2 = kPortUndefine;
    //J_3 消息转发
    PortType    portSelfRecvJ3 = kPortUndefine;
    //J_7 消息转发
    PortType    portSelfRecvJ7 = kPortUndefine;
    //TimeSlice 消息转发
    PortType    portSelfRecvTS = kPortUndefine;
    //Sub TimeSlice 消息转发
    PortType    portSelfRecvSubTS = kPortUndefine;
  private:

    inline void BindPortSelfSend() {
      portSelfSend = util::NextUid();
      digraph.couple(this, this->portSelfSend, &parent, parent.portSelfRecv); //发送给Ju
    }
    //转发请求
    inline void BindSelfSendToTranspond() {
      portSelfSendToTranspond = util::NextUid();
      digraph.couple(this, this->portSelfSendToTranspond, &parent, parent.portSelfRecvToTranspond); //发送给Ju
    }
    
  public:

    inline void BindSelfRecvCmd() {
      portSelfRecvCmd = util::NextUid();
      digraph.couple(&parent, parent.portSelfSendCmd,this, this->portSelfRecvCmd); 
    }

    inline void BindSelfRecvLT() {
      portSelfRecvLT = util::NextUid();
      digraph.couple(&parent, parent.portSelfSendLT, this, this->portSelfRecvLT);
    }

    inline void BindSelfRecvJ2() {
      portSelfRecvJ2 = util::NextUid();
      digraph.couple(&parent, parent.portSelfSendJ2, this, this->portSelfRecvJ2);
    }

    inline void BindSelfRecvJ3() {
      portSelfRecvJ3 = util::NextUid();
      digraph.couple(&parent, parent.portSelfSendJ3, this, this->portSelfRecvJ3);
    }

    inline void BindSelfRecvJ7() {
      portSelfRecvJ7 = util::NextUid();
      digraph.couple(&parent, parent.portSelfSendJ7, this, this->portSelfRecvJ7);
    }

    inline void BindSelfRecvTS() {
      portSelfRecvTS = util::NextUid();
      digraph.couple(&parent, parent.portSelfSendTS, this, this->portSelfRecvTS);
    }

    inline void BindSelfRecvSubTS() {
      portSelfRecvSubTS = util::NextUid();
      digraph.couple(&parent, parent.portSelfSendSubTS, this, this->portSelfRecvSubTS);
      
    }

#define __GET_FUNC__(name) inline PortType Get##name() { assert(port##name!=kPortUndefine/*端口未绑定*/);return port##name;}
    __GET_FUNC__(SelfSend);
    __GET_FUNC__(SelfRecvCmd);
    __GET_FUNC__(SelfRecvLT);
    __GET_FUNC__(SelfRecvJ2);
    __GET_FUNC__(SelfRecvJ3);
    __GET_FUNC__(SelfRecvJ7);
    __GET_FUNC__(SelfRecvTS);
    __GET_FUNC__(SelfRecvSubTS);
#undef __GET_FUNC__


    public:
      inline IO_Type CreatBroadcastIO(util::SptrBlob sptr_blob) { return IO_Type(portSelfSendToTranspond, sptr_blob); }
  };

}

#define _FUNC_MakeShared_(CLASS_NAME) static inline auto  make_shared(Ju& ju, Digraph& digraph, const std::string&name, PortType uid)  {return std::make_shared<CLASS_NAME>(ju, digraph, name, uid);};

#define _FUNC_CreatSptr_(CLASS_NAME) const auto CreatSptr##CLASS_NAME=CLASS_NAME::make_shared;
