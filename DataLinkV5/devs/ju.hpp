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
    // J3 AT ��������󶼵�����
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
    
    std::list<IO_Type>  buffer_list;                //�� hub ���յ���Ϣ ȫ������������. ����ͨ�� output ���д���
    std::map<std::string, std::any> map_component;  //
    
    msg::TimeSlice    time_silce;                   //���� ���յ���ʱ��Ƭ��Ϣ
    

    
    util::sync::Map<std::string, TrackInformation>  dict_active_track;
    util::sync::Map<std::string, TrackInformation>  dict_recv_track;
    util::sync::Map<std::string, TimeType>          dict_r2;
  public:
    //��Component ����ʹ��
    const PortType    portSelfRecv;                       //�ڲ�ʹ�õĽ��ն˿�

    const PortType    portSelfRecvToTranspond;          //ֱ�ӹ㲥 component ��Ҫ�㲥�� ����

    ///ע��: ��port δ�� JuComponent ��,��Ҫʵ�ְ�
    const PortType    portSelfSendToTranspondBuffer;   //�� port_self_recv_to_transpond ������ת���� CoreBroadcastComponent

    const PortType    portSelfSendCmd;                   //CMD ת��
    const PortType    portSelfSendLT;                    //Local Track ��Ϣת��
    const PortType    portSelfSendJ3;                    //J_3 ��Ϣת��
    const PortType    portSelfSendJ7;                    //J_7 ��Ϣת��
    const PortType    portSelfSendJ2;                    //J_2 ��Ϣת��
    const PortType    portSelfSendTS;                    //TimeSlice ��Ϣת��
    const PortType    portSelfSendSubTS;                  //TimeSlice ��Ϣת��
    //��Ҫ���� AT ��Ϣ
    const PortType    portPrivateRecv;                    //��㲥1v1���ն˿�
    //��Ҫ ���� J ��Ϣ
    const PortType    portBroadcastSend;                  //�㲥���Ͷ˿� 
    const PortType    portBroadcastRecv;                  //�㲥���ն˿� 
  public:
    int32_t _uSTN;
    
  public:
    // ͨ�� AtomicAbstract �̳�
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
    assert(std::dynamic_pointer_cast<JuComponent>(sptr_component) == nullptr/*����ΪJuComponent����*/);
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
    assert(false);//�����Ͳ������ɷ�Χ��
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
