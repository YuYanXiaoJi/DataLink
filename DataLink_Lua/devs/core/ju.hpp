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

    // 通过 AbstractAtomic 继承
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

    std::list<IO_Type>  buffer_list;                //从 hub 接收的消息 全部保存在这里. 立即通过 output 进行触发
    std::map<std::string , std::shared_ptr<JuComponent> > map_component;

    msg::TimeSlice    time_silce;                   //保存 接收到的时间片信息

    std::map<std::string , handler::TrackInformation>  dict_active_track;
    std::map<std::string , handler::TrackInformation>  dict_recv_track;
    std::map<std::string , TimeType>          dict_r2;
  public:
    // 与 Hub 通信 端口
    const PortType port_broadcast = util::Uid();
    const PortType port_private   = util::Uid();
  //public:
  //  //与Component 传输使用
  //  const PortType    portSelfRecv = util::Uid();                       //内部使用的接收端口

  //  const PortType    portSelfRecvToTranspond = util::Uid();            //直接广播 component 想要广播的 数据
  //  const PortType    portToBroadcast = util::Uid();  //
  //  ///注意: 此port 未在 JuComponent 绑定,需要实现绑定
  //  const PortType    portSelfSendToTranspondBuffer = util::Uid();      //将 port_self_recv_to_transpond 的数据转发给 CoreBroadcastComponent

  //  const PortType    portSelfSendCmd = util::Uid();                  //CMD 转发
  //  const PortType    portSelfSendLT = util::Uid();                  //Local Track 消息转发
  //  const PortType    portSelfSendJ3 = util::Uid();                  //J_3 消息转发
  //  const PortType    portSelfSendJ7 = util::Uid();                  //J_7 消息转发
  //  const PortType    portSelfSendJ2 = util::Uid();                     //J_2 消息转发
  //  const PortType    portSelfSendTS = util::Uid();                     //TimeSlice 消息转发
  //  const PortType    portSelfSendSubTS = util::Uid();                  //TimeSlice 消息转发
  //  //主要传递 AT 消息
  //  const PortType    portPrivateRecv = util::Uid();                    //与广播1v1接收端口
  //  //主要 传送 J 消息
  //  const PortType    portBroadcastSend = util::Uid();                  //广播发送端口 
  //  const PortType    portBroadcastRecv = util::Uid();                  //广播接收端口 
  public:
    int32_t _uSTN;
  public:


  private:
    const TimeType  _time_slice_trigger_interval = 20;
    util::MinPriorityQueue<handler::ScheduleBufferNode>  _time_slice_trigger_queue;


  };

}
