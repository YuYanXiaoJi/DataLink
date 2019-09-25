#pragma once
#include"abstract_atomic.hpp"
#include"..//message/message.hpp"
#include"../../utility/utility.hpp"
#include"../handler/schedule_buffer_node.hpp"
#include"../handler/track_infomation.hpp"
#include<set>
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
    std::tuple<bool,bool,bool> GetExist(const std::string &track_name);

    //bool  CorrelationTest(const std::string &track_name);

    void AddComponent(const shared_ptr<JuComponent> sptr_component);
    void LoadScriptComponent(const std::string& lua_file , const std::string& jsc_name);
  public:

    msg::TimeSlice    time_slice;                   //保存 接收到的时间片信息
    util::sync::Map<std::string , handler::TrackInformation>   dict_local_track;
    util::sync::Map<std::string , handler::TrackInformation>   dict_recv_track;
    util::sync::Map<std::string , TimeType>                    dict_r2;

    
  public:
#pragma region 端口信号定义
    /*
      端口的定义为 sig+i+o+_+name
                  sig :为signal的缩写
                  i   :input,接收 ,替代 recv
                  o   :output,发送,替代 send
    */
  /// 与 Hub 通信 端口
    inline const static PortType  sigio_hub = util::Uid();        //  portBroadcast Send & Recv & portPrivateRecv
    
  /// Component
    /*Component->Ju*/
    inline const static PortType  sigi_interior  = util::Uid();      //  内部接收 ,portSelfRecv
    inline const static PortType  sigi_secure_broadcast = util::Uid();     //  接受 component 想要广播的内容. 由于TDMA的限制,发往该 Port 的消息会通过 sig_broadcast_buffer 发送到 对应的 component
    inline const static PortType  sigi_immediate_broadcast = util::Uid();  //  接收消息后,将接收的消息立即发送给port_broadcast

    /*Ju->Component*/
    inline const static PortType  sigo_broadcast_buffer = util::Uid();  //将 port_secure_broadcast 的数据 转发到 Component 
    inline const static PortType  sigo_ts = util::Uid();        //  向内部Component发送 TimeSlice 到达的消息.
    inline const static PortType  sigo_sts = util::Uid();            //  向内部Component发送 Sub TimeSlice 到达的消息.
    inline const static PortType  sigo_cmd = util::Uid();           //  ...
    inline const static PortType  sigo_lt = util::Uid();
    inline const static PortType  sigo_j2 = util::Uid();
    inline const static PortType  sigo_j3 = util::Uid();
    inline const static PortType  sigo_j7 = util::Uid();
#pragma endregion
  public:
    int32_t _uSTN;
  private:
    const TimeType                                        time_slice_trigger_interval = 20;
    std::set<std::string/*track_number*/>                 set_record_track_number;  //用于记录本JU广播出去的消息的TN;
    util::MinPriorityQueue<handler::ScheduleBufferNode>   recv_buffer_queue;
    std::map<int64_t/*uid*/,std::shared_ptr<JuComponent>> map_component;
  private:
    bool CheckIsSelfSend(const util::Blob &blob);
    void UpdateInfo(const util::Blob &blob);
    void LogMsg(const util::Blob & blob);
    void PushBuffer(TimeType schedule_time ,const IO_Type& x);

    //只适用于 sigi_hub , sigi_interior
    void InsertToYBag(const devs::IO_Type x, devs::IO_Bag &yb);

    //记录本地发出的消息的Track Number
    void RecordMsgTrackNumber(const util::Blob & blob);
  };

}
