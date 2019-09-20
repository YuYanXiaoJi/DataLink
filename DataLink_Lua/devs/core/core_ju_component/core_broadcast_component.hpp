#pragma once
#include"../ju_component.hpp"
#include<queue>
namespace devs::core::ju_component {
  class CoreBroadcastComponent
    :public JuComponent
  {
  public:
    CoreBroadcastComponent(Digraph & _digraph , Ju & _ju);
    __CREATOR__(CoreBroadcastComponent);

    // 通过 JuComponent 继承
    virtual void Input(const devs::IO_Type & x) override;

    virtual void Internal() override;

    virtual void Output(devs::IO_Bag & yb) override;

    virtual devs::TimeType Ta() override;

  public:
    void Log(devs::ValueType value);

  private:
    std::queue<util::SptrBlob> broadcast_buffer_queue;    //等待发送
  };
};