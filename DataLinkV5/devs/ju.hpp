#pragma once
#include"atomic.hpp"
#include"typedef.hpp"
#include"schedule_buffer_node.hpp"
#include"message/message.hpp"
#include"../utility/utility.hpp"

#include<memory>
#include<any>
namespace devs {
  class JuComponent;
  class Ju
    :public AtomicAbstract
  {
  public :
    // J3 AT 的数据最后都到这里
    struct TrackInformation;
    static std::shared_ptr<Ju> make_shared(Digraph& _digraph, const std::string&_name, uint64_t _uid, int32_t _uSTN);
  public:
    Ju(Digraph& _digraph, const std::string&_name, uint64_t _uid, int32_t _uSTN);

    // used only c++17 or more than
    // usage:  auto [is_exist_at, is_exist_rt, is_exist_r2] = GetExist(track_name); 
    std::tuple<bool, bool, bool> GetExist(const std::string& track_name);

    template<class Ty>
    void AddComponent(const std::string& name, const shared_ptr<Ty>& sptr_component);

  public:
    
    std::list<IO_Type>  buffer_list;                //从 hub 接收的消息 全部保存在这里. 立即通过 output 进行触发
    std::map<std::string, std::any> map_component;  //
    
    msg::TimeSlice    time_silce;                   //保存 接收到的时间片信息
    

    
    util::sync::Map<std::string, TrackInformation>  dict_active_track;
    util::sync::Map<std::string, TrackInformation>  dict_recv_track;
    util::sync::Map<std::string, TimeType>          dict_r2;
  public:
    //与Component 传输使用
    const PortType    portSelfRecv;                       //内部使用的接收端口

    const PortType    portSelfRecvToTranspond;          //直接广播 component 想要广播的 数据

    ///注意: 此port 未在 JuComponent 绑定,需要实现绑定
    const PortType    portSelfSendToTranspondBuffer;   //将 port_self_recv_to_transpond 的数据转发给 CoreBroadcastComponent

    const PortType    portSelfSendCmd;                   //CMD 转发
    const PortType    portSelfSendLT;                    //Local Track 消息转发
    const PortType    portSelfSendJ3;                    //J_3 消息转发
    const PortType    portSelfSendJ7;                    //J_7 消息转发
    const PortType    portSelfSendJ2;                    //J_2 消息转发
    const PortType    portSelfSendTS;                    //TimeSlice 消息转发
    const PortType    portSelfSendSubTS;                  //TimeSlice 消息转发
    //主要传递 AT 消息
    const PortType    portPrivateRecv;                    //与广播1v1接收端口
    //主要 传送 J 消息
    const PortType    portBroadcastSend;                  //广播发送端口 
    const PortType    portBroadcastRecv;                  //广播接收端口 
  public:
    int32_t _uSTN;
    
  public:
    // 通过 AtomicAbstract 继承
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;
  private:
    bool  isUseSubTS = false;
    const TimeType  _time_slice_trigger_interval = 20;
    util::MinPriorityQueue<ScheduleBufferNode>  _time_slice_trigger_queue;

  };

  inline auto CreatSptrJu(Digraph& _digraph, const std::string&_name, uint64_t _uid,int32_t uSTN) {
    return Ju::make_shared(_digraph, _name,_uid, uSTN);
  }

  typedef std::shared_ptr<Ju> SptrJu;
  template<class Ty>
  inline void Ju::AddComponent(const std::string & name, const shared_ptr<Ty>& sptr_component)
  {
    assert(std::dynamic_pointer_cast<JuComponent>(sptr_component) == nullptr/*必须为JuComponent子类*/);
    map_component[name] = sptr_component;
  }
}


struct devs::Ju::TrackInformation
{
  std::string track_number;
  std::string from_sut_name;

  msg::TrackPlatform track_platform;
  int32_t    track_quality;
  int32_t    _uSTN;

  TimeType  time_msec;

  explicit TrackInformation()
  {
    track_number = "";
    from_sut_name = "";
    track_platform = msg::Platform_UNDEFINED;
    track_quality = -1;
    time_msec = -1;
  }

  explicit TrackInformation(const msg::LocalTrack& at, const std::string& sut_name) {
    track_number = at.track_number;
    from_sut_name = sut_name;
    track_platform = at.track_platform;
    track_quality = at.track_quality;
    time_msec = at.time_msec;
  }

  explicit TrackInformation(const msg::JointMsg3I& j30i) {
    track_number = j30i.track_number;
    from_sut_name = j30i.from_sut_name;
    track_platform = j30i.track_platform;
    track_quality = j30i.track_quality;
    time_msec = j30i.time_msec;
    _uSTN = j30i._uSTN;

  }

  template<class Ty> inline Ty get(TimeType _time = -1, bool is_new_info = true) {
    assert(false);//该类型不在生成范围内
    return Ty();
  }

  template <> inline msg::JointMsg3I get(TimeType _time, bool is_new_info) {

    std::string t_track_number = this->track_number;
    if (is_new_info)
      t_track_number = util::TrackNumberHandler::Create(
        util::TrackNumberHandler::GetName(t_track_number));

    auto ojb = msg::JointMsg3I(
      t_track_number.c_str(),
      this->from_sut_name.c_str(),
      this->track_platform,
      this->track_quality,
      this->time_msec,
      this->_uSTN
    );


    if (_time > 0)
      ojb.time_msec = _time;
    return ojb;
  }
};
