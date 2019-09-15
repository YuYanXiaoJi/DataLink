#pragma once
#include"abstract_atomic.hpp"
#include"..//message/message.hpp"
#include"../../utility/utility.hpp"
#include"../handler/schedule_buffer_node.hpp"
#include"../handler/track_infomation.hpp"
#include<map>
namespace devs::core {
  class JuComponent;
  class Ju
    :public AbstractAtomic
  {
  public:
    static std::shared_ptr<Ju> make_shared(Digraph &_digraph , const std::string &_name, int32_t _uSTN);
  public:
    Ju(Digraph &_digraph , const std::string &_name , int32_t _uSTN);

    // ͨ�� AbstractAtomic �̳�
    virtual void Input(const devs::IO_Type &x) override;
    virtual void Internal() override;
    virtual void Output(devs::IO_Bag &yb) override;
    virtual devs::TimeType Ta() override;

    // used only c++17 or more than
    // usage:  auto [is_exist_at, is_exist_rt, is_exist_r2] = GetExist(track_name); 
    //std::tuple<bool , bool , bool> GetExist(const std::string &track_name);

    //bool  CorrelationTest(const std::string &track_name);

    //template<class Ty> void AddComponent(const std::string &name , const shared_ptr<Ty> &sptr_component);
  public:

    std::list<IO_Type>  buffer_list;                //�� hub ���յ���Ϣ ȫ������������. ����ͨ�� output ���д���
    std::map<std::string , std::shared_ptr<JuComponent> > map_component;

    msg::TimeSlice    time_silce;                   //���� ���յ���ʱ��Ƭ��Ϣ

    std::map<std::string , handler::TrackInformation>  dict_active_track;
    std::map<std::string , handler::TrackInformation>  dict_recv_track;
    std::map<std::string , TimeType>          dict_r2;
  public:
    // �� Hub ͨ�� �˿�
    const PortType port_broadcast = util::Uid();
    const PortType port_private   = util::Uid();
  //public:
  //  //��Component ����ʹ��
  //  const PortType    portSelfRecv = util::Uid();                       //�ڲ�ʹ�õĽ��ն˿�

  //  const PortType    portSelfRecvToTranspond = util::Uid();            //ֱ�ӹ㲥 component ��Ҫ�㲥�� ����
  //  const PortType    portToBroadcast = util::Uid();  //
  //  ///ע��: ��port δ�� JuComponent ��,��Ҫʵ�ְ�
  //  const PortType    portSelfSendToTranspondBuffer = util::Uid();      //�� port_self_recv_to_transpond ������ת���� CoreBroadcastComponent

  //  const PortType    portSelfSendCmd = util::Uid();                  //CMD ת��
  //  const PortType    portSelfSendLT = util::Uid();                  //Local Track ��Ϣת��
  //  const PortType    portSelfSendJ3 = util::Uid();                  //J_3 ��Ϣת��
  //  const PortType    portSelfSendJ7 = util::Uid();                  //J_7 ��Ϣת��
  //  const PortType    portSelfSendJ2 = util::Uid();                     //J_2 ��Ϣת��
  //  const PortType    portSelfSendTS = util::Uid();                     //TimeSlice ��Ϣת��
  //  const PortType    portSelfSendSubTS = util::Uid();                  //TimeSlice ��Ϣת��
  //  //��Ҫ���� AT ��Ϣ
  //  const PortType    portPrivateRecv = util::Uid();                    //��㲥1v1���ն˿�
  //  //��Ҫ ���� J ��Ϣ
  //  const PortType    portBroadcastSend = util::Uid();                  //�㲥���Ͷ˿� 
  //  const PortType    portBroadcastRecv = util::Uid();                  //�㲥���ն˿� 
  public:
    int32_t _uSTN;
  public:


  private:
    const TimeType  _time_slice_trigger_interval = 20;
    util::MinPriorityQueue<handler::ScheduleBufferNode>  _time_slice_trigger_queue;


  };

}
