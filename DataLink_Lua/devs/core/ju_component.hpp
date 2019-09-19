#pragma once
#include"abstract_atomic.hpp"
#include"ju.hpp"

namespace devs::core {
  class JuComponent 
    :public AbstractAtomic
  {
  public:
    JuComponent(Digraph &_digraph , Ju &_ju , const std::string &_name);
    
  public:
#pragma region 端口信号定义
    /*
      端口的定义为 sig+i+o+_+name
                  sig :为signal的缩写
                  i   :input,接收 ,替代 recv
                  o   :output,发送,替代 send
    */
    /// 与 Hub 通信 端口
    inline const static PortType  sigo_interior = util::Uid();        //  发送数据给Ju

  /// Component
    /*Component->Ju*/
    //inline const static PortType  sigi_interior_accept = util::Uid();      //  内部接收 ,portSelfRecv
    inline const static PortType  sigo_secure_broadcast = util::Uid();     
    inline const static PortType  sigo_immediate_broadcast = util::Uid();  

    /*Ju->Component*/
    inline const static PortType  sigi_broadcast_buffer = util::Uid();  
    inline const static PortType  sigi_time_slice = util::Uid();       
    inline const static PortType  sigi_sub_ts = util::Uid();            
    inline const static PortType  sigi_command = util::Uid();        
    inline const static PortType  sigi_local_track = util::Uid();
    inline const static PortType  sigi_j2 = util::Uid();
    inline const static PortType  sigi_j3 = util::Uid();
    inline const static PortType  sigi_j7 = util::Uid();
#pragma endregion
    
#pragma region 端口绑定函数
  private:
    inline void BindSend(PortType sig_out , PortType sig_in) {
      digraph.couple(this , sig_out , &ju , sig_in);
    }
    inline void BindRecv(PortType sig_out , PortType sig_in) {
      digraph.couple(&ju , sig_out ,this  , sig_in);
    }
    inline void BindOutInterior() {
      BindSend(sigo_interior , ju.sigi_interior);
    }
    inline void BindOutSecureBroadcast() {
      BindSend(sigo_secure_broadcast , ju.sigi_secure_broadcast);
    }
    inline void BindOutImmediateBroadcast() {
      BindSend(sigo_immediate_broadcast , ju.sigi_immediate_broadcast);
    }
  public:
    inline void BindInBroadcastBuffer(){
      BindSend(ju.sigo_broadcast_buffer , sigi_broadcast_buffer);
    }
    inline void BindInTS() {
      BindSend(ju.sigo_time_slice , sigi_time_slice);
    }
    inline void BindInSTS() {
      BindSend(ju.sigo_sub_ts , sigi_sub_ts);
    }
    inline void BindInCMD() {
      BindSend(ju.sigo_command , sigi_command);
    }
    inline void BindInLT() {
      BindSend(ju.sigo_local_track , sigi_local_track);
    }
    inline void BindInJ2() {
      BindSend(ju.sigo_j2, sigi_j2);
    }
    inline void BindInJ3() {
      BindSend(ju.sigo_j3 , sigi_j3);
    }
    inline void BindInJ7() {
      BindSend(ju.sigo_j7 , sigi_j7);
    }
#pragma endregion

#pragma region emmm



#pragma endregion
  public:
    Ju& ju;


  };
}