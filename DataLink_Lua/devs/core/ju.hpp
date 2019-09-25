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

    // ͨ�� AbstractAtomic �̳�
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

    msg::TimeSlice    time_slice;                   //���� ���յ���ʱ��Ƭ��Ϣ
    util::sync::Map<std::string , handler::TrackInformation>   dict_local_track;
    util::sync::Map<std::string , handler::TrackInformation>   dict_recv_track;
    util::sync::Map<std::string , TimeType>                    dict_r2;

    
  public:
#pragma region �˿��źŶ���
    /*
      �˿ڵĶ���Ϊ sig+i+o+_+name
                  sig :Ϊsignal����д
                  i   :input,���� ,��� recv
                  o   :output,����,��� send
    */
  /// �� Hub ͨ�� �˿�
    inline const static PortType  sigio_hub = util::Uid();        //  portBroadcast Send & Recv & portPrivateRecv
    
  /// Component
    /*Component->Ju*/
    inline const static PortType  sigi_interior  = util::Uid();      //  �ڲ����� ,portSelfRecv
    inline const static PortType  sigi_secure_broadcast = util::Uid();     //  ���� component ��Ҫ�㲥������. ����TDMA������,������ Port ����Ϣ��ͨ�� sig_broadcast_buffer ���͵� ��Ӧ�� component
    inline const static PortType  sigi_immediate_broadcast = util::Uid();  //  ������Ϣ��,�����յ���Ϣ�������͸�port_broadcast

    /*Ju->Component*/
    inline const static PortType  sigo_broadcast_buffer = util::Uid();  //�� port_secure_broadcast ������ ת���� Component 
    inline const static PortType  sigo_ts = util::Uid();        //  ���ڲ�Component���� TimeSlice �������Ϣ.
    inline const static PortType  sigo_sts = util::Uid();            //  ���ڲ�Component���� Sub TimeSlice �������Ϣ.
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
    std::set<std::string/*track_number*/>                 set_record_track_number;  //���ڼ�¼��JU�㲥��ȥ����Ϣ��TN;
    util::MinPriorityQueue<handler::ScheduleBufferNode>   recv_buffer_queue;
    std::map<int64_t/*uid*/,std::shared_ptr<JuComponent>> map_component;
  private:
    bool CheckIsSelfSend(const util::Blob &blob);
    void UpdateInfo(const util::Blob &blob);
    void LogMsg(const util::Blob & blob);
    void PushBuffer(TimeType schedule_time ,const IO_Type& x);

    //ֻ������ sigi_hub , sigi_interior
    void InsertToYBag(const devs::IO_Type x, devs::IO_Bag &yb);

    //��¼���ط�������Ϣ��Track Number
    void RecordMsgTrackNumber(const util::Blob & blob);
  };

}
