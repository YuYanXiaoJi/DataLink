#pragma once
#include"component.hpp"
#include<Lua/lua.hpp>
#include<string>

namespace cc {
  class ScriptComponent
    :public Component
  {
  public:
    ScriptComponent(const string &filename , devs::Digraph &digrapg , Generator &parent);

    // Í¨¹ý Component ¼Ì³Ð
    virtual void External(const devs::PortType &recvPort , const devs::SptrBlob sptrBlob) override;
    virtual void Internal() override;
    virtual void Output(devs::IO_Bag &yb) override;
    virtual devs::TimeType Ta() override;

  private:
    //private pointer lua state
    lua_State *m_pluaState;
  };
}