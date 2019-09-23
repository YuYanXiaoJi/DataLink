#pragma once
#include"abstract_atomic.hpp"
#include"ju.hpp"
#include<memory>
namespace devs::core {
  class JuComponent 
    :public AbstractAtomic
  {
  public:
    JuComponent(Digraph &_digraph , Ju &_ju , const std::string &_name)
      :AbstractAtomic(_digraph , _name) , ju(_ju)
    {
      BindOutInterior();
      BindOutSecureBroadcast();
      BindOutImmediateBroadcast();
    }
    
  
#pragma region �˿��źŶ���
    /*
      �˿ڵĶ���Ϊ sig+i+o+_+name
                  sig :Ϊsignal����д
                  i   :input,���� ,��� recv
                  o   :output,����,��� send
    */
  private:
    /// �� Hub ͨ�� �˿�
    inline const static PortType  sigo_interior = util::Uid();        //  �������ݸ�Ju

  /// Component
    /*Component->Ju*/
    //inline const static PortType  sigi_interior_accept = util::Uid();      //  �ڲ����� ,portSelfRecv
    inline const static PortType  sigo_secure_broadcast = util::Uid();     
    inline const static PortType  sigo_immediate_broadcast = util::Uid();  

  public:
    /*Ju->Component*/
    inline const static PortType  sigi_broadcast_buffer = util::Uid();  
    inline const static PortType  sigi_ts = util::Uid();       
    inline const static PortType  sigi_sts = util::Uid();            
    inline const static PortType  sigi_cmd = util::Uid();        
    inline const static PortType  sigi_lt = util::Uid();
    inline const static PortType  sigi_j2 = util::Uid();
    inline const static PortType  sigi_j3 = util::Uid();
    inline const static PortType  sigi_j7 = util::Uid();
#pragma endregion
    
#pragma region �˿ڰ󶨺���
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
      BindRecv(ju.sigo_broadcast_buffer , sigi_broadcast_buffer);
    }
    inline void BindInTS() {
      BindRecv(ju.sigo_ts , sigi_ts);
    }
    inline void BindInSTS() {
      BindRecv(ju.sigo_sts , sigi_sts);
    }
    inline void BindInCMD() {
      BindRecv(ju.sigo_cmd , sigi_cmd);
    }
    inline void BindInLT() {
      BindRecv(ju.sigo_lt , sigi_lt);
    }
    inline void BindInJ2() {
      BindRecv(ju.sigo_j2, sigi_j2);
    }
    inline void BindInJ3() {
      BindRecv(ju.sigo_j3 , sigi_j3);
    }
    inline void BindInJ7() {
      BindRecv(ju.sigo_j7 , sigi_j7);
    }
#pragma endregion

#pragma region emmm

    // ������Ҫ ��ȫ�㲥��
    inline void InsertSecureBroadcast(ValueType value , devs::IO_Bag &yb) {
      yb.insert(IO_Type(sigo_secure_broadcast , value));
    }

    // ������Ҫ �����㲥��
    inline void InsertImmediateBroadcast(ValueType value , devs::IO_Bag &yb) {
      yb.insert(IO_Type(sigo_immediate_broadcast , value));
    }

    // ������Ҫ �ڲ�����������
    inline void InsertInteriorBroadcast( ValueType value , devs::IO_Bag &yb ) {
      yb.insert(IO_Type(sigo_interior , value));
    }

#pragma endregion
  public:
    Ju& ju;


  };

  //template<typename Ty>
  //shared_ptr<JuComponent> Creator(Ju&ju) {
  //  static_assert( false , "��δʵ�ֵ������е�����");
  //  return nullptr;
  //}

#define __CREATOR__(name) \
  inline static shared_ptr<devs::core::JuComponent> Creator(devs::core::Ju&ju) {    \
    auto ptr=std::make_shared<name>(ju.digraph ,ju);        \
    return static_pointer_cast<devs::core::JuComponent>(ptr);  }
}