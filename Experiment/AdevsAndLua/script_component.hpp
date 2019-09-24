#pragma once
#include"component.hpp"
#include"integer.hpp"
#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>
#include<string>
#include<iostream>
#include"blob.hpp"
namespace cc {
  class ScriptComponent
    :public Component
  {
  public:
    ScriptComponent(const string &filename , devs::Digraph &digrapg , Generator &parent);

    // Í¨¹ý Component ¼Ì³Ð
    virtual void Input(const devs::PortType &recvPort , const SptrBlob sptrBlob) override;
    virtual void Internal() override;
    virtual void Output(devs::IO_Bag &yb) override;
    virtual devs::TimeType Ta() override;

    void SendFunc(devs::PortType sendPort , Integer info);
    void SendFuncBlob( devs::PortType sendPort , Blob info );
    void SendFuncLuaRef(devs::PortType sendPort , luabridge::LuaRef info);
  private:
    //private pointer lua state
    lua_State *m_pLuaState;
    //luabridge::LuaRef m_luaRefInit;
    devs::IO_Bag *p_yb=nullptr;
    
  };
}