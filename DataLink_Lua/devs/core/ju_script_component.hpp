#pragma once
#include"ju_component.hpp"

#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>

namespace devs::core {
  class JuScriptComponent 
    :public JuComponent
  {
  public:
    JuScriptComponent(Digraph &digraph , Ju &ju , const std::string lua_file , const std::string &name);

    // 通过 JuComponent 继承
    virtual void Input(const devs::IO_Type &x) override;

    virtual void Internal() override;

    virtual void Output(devs::IO_Bag &yb) override;

    virtual devs::TimeType Ta() override;

  public:
    void SecureBroadcast(luabridge::LuaRef msg);
    void ImmediateBroadcast(luabridge::LuaRef msg);
    void InteriorBroadcast(luabridge::LuaRef msg);


    msg::TimeSlice GetTS();
    handler::TrackInformation GetLocalTrackInfo(std::string track_name);//
    handler::TrackInformation GetRecvTrackInfo(std::string track_name);//Recv  Track Info
    int64_t  GetR2(std::string track_name);
    bool ExistLocalTrackInfo(std::string track_name);
    bool ExistRecvTrackInfo(std::string track_name);
    bool ExistR2(std::string track_name);
    bool CorrelationTest(std::string track_name);
  
    luabridge::LuaRef ViewLocalTrackDict();
    luabridge::LuaRef ViewRecvTrackDict();
    luabridge::LuaRef ViewR2Dict();

    void SetR2(std::string track_name , int64_t time);

  private:
    void InjectTheSoul();//( ͡° ͜ʖ ͡°)滑稽
  private:
    lua_State    *plua  = nullptr;
    devs::IO_Bag *pyb = nullptr;
  };
}