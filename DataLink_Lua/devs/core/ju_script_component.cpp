#include "ju.hpp"
#include "ju_script_component.hpp"
#include "../handler/lua_inject_handler.hpp"
using namespace devs::core;
using namespace devs;
devs::core::JuScriptComponent::JuScriptComponent(Digraph &digraph , Ju &ju , const std::string lua_file , const std::string &name)
  :JuComponent(digraph , ju , name)
{


}
void devs::core::JuScriptComponent::Input(const devs::IO_Type &x)
{
}

void devs::core::JuScriptComponent::Internal()
{
}

void devs::core::JuScriptComponent::Output(devs::IO_Bag &yb)
{
}

devs::TimeType devs::core::JuScriptComponent::Ta()
{
  return devs::TimeType();
}

msg::TimeSlice devs::core::JuScriptComponent::GetTS(){
  return this->ju.time_slice;
}

handler::TrackInformation devs::core::JuScriptComponent::GetLocalTrackInfo(std::string track_name)
{
  return ju.dict_local_track[track_name];
}

handler::TrackInformation devs::core::JuScriptComponent::GetRecvTrackInfo(std::string track_name)
{
  return ju.dict_recv_track[track_name];
}

int64_t devs::core::JuScriptComponent::GetR2(std::string track_name)
{
  return ju.dict_r2[track_name];
}

bool devs::core::JuScriptComponent::ExistLocalTrackInfo(std::string track_name)
{
  return ju.dict_local_track.exist(track_name);
}

bool devs::core::JuScriptComponent::ExistRecvTrackInfo(std::string track_name)
{
  return ju.dict_recv_track.exist(track_name);
}

bool devs::core::JuScriptComponent::ExistR2(std::string track_name)
{
  return ju.dict_r2.exist(track_name);
}

bool devs::core::JuScriptComponent::CorrelationTest(std::string track_name)
{
  return true;
}

luabridge::LuaRef devs::core::JuScriptComponent::ViewLocalTrackDict()
{
  luabridge::LuaRef view(plua , luabridge::newTable(plua));
  for(auto[key , value] : ju.dict_local_track) {
    view[key] = value;
  }
  return view;
}

luabridge::LuaRef devs::core::JuScriptComponent::ViewRecvTrackDict()
{
  luabridge::LuaRef view(plua , luabridge::newTable(plua));
  for(auto[key , value] : ju.dict_recv_track) {
    view[key] = value;
  }
  return view;
}

luabridge::LuaRef devs::core::JuScriptComponent::ViewR2Dict()
{
  luabridge::LuaRef view(plua , luabridge::newTable(plua));
  for(auto[key , value] : ju.dict_r2) {
    view[key] = value;
  }
  return view;
}

void devs::core::JuScriptComponent::SetR2(std::string track_name , int64_t time)
{
  ju.dict_r2[track_name] = time;
}

void devs::core::JuScriptComponent::InjectTheSoul()
{
  this->plua = luaL_newstate();
  luaL_openlibs(plua);

  lua_handler::LuaInject<handler::EnumWrapper>(plua);
  lua_handler::LuaInject<msg::TimeSlice>(plua);
  lua_handler::LuaInject<msg::SubTimeSlice>(plua);
  lua_handler::LuaInject<msg::JointMsg2I>(plua);
  lua_handler::LuaInject<msg::JointMsg3I>(plua);
  lua_handler::LuaInject<msg::JointMsg7I>(plua);
  lua_handler::LuaInject<msg::LocalTrack>(plua);
  lua_handler::LuaInject<msg::LocalCmd>(plua);
  lua_handler::LuaInject<handler::TrackInformation>(plua);
  lua_handler::LuaInject<JuScriptComponent>(plua);
}
