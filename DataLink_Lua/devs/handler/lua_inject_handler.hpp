#pragma once
#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>

#include"enum_handler.hpp"
#include"function_handler.hpp"
#include"track_infomation.hpp"
#include"../message/message.hpp"
#include"../core/ju_script_component.hpp"

namespace devs::lua_handler {
  template<typename _Ty> void LuaInject(lua_State *p_lua_state) { static_assert( false , "未实现该类型的 Inject" ); }

  template<> inline void LuaInject<handler::FuncWrapper>(lua_State *p_lua_state) {
    using namespace handler;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginClass<FuncWrapper>("Func")
      .addStaticFunction("Now" , &FuncWrapper::Now)
      .addStaticFunction("GetMsgName" , &FuncWrapper::GetMsgName)
      .endClass();
  }

  template<> inline void LuaInject<handler::EnumWrapper>(lua_State *p_lua_state) {
    using namespace handler;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginClass<EnumWrapper>("Enum")
      .addStaticData("Msg_JointMsg2I" , &EnumWrapper::Msg_JointMsg2I , false)
      .addStaticData("Msg_JointMsg3I" , &EnumWrapper::Msg_JointMsg3I , false)
      .addStaticData("Msg_JointMsg7I" , &EnumWrapper::Msg_JointMsg7I , false)
      .addStaticData("Msg_JointMsgBase" , &EnumWrapper::Msg_JointMsgBase , false)
      .addStaticData("Msg_LoaclCmd" , &EnumWrapper::Msg_LoaclCmd , false)
      .addStaticData("Msg_LocalTrack" , &EnumWrapper::Msg_LocalTrack , false)
      .addStaticData("Msg_SubTimeSlice" , &EnumWrapper::Msg_SubTimeSlice , false)
      .addStaticData("Msg_TimeSlice" , &EnumWrapper::Msg_TimeSlice , false)

      .addStaticData("Platform_AIR" , &EnumWrapper::Platform_AIR , false)
      .addStaticData("Platform_LAND" , &EnumWrapper::Platform_LAND , false)
      .addStaticData("Platform_MARITIME" , &EnumWrapper::Platform_MARITIME , false)
      .addStaticData("Platform_UNDEFINED" , &EnumWrapper::Platform_UNDEFINED , false)

      .addStaticData("CMD_SET_R2" , &EnumWrapper::CMD_SET_R2 , false)
      .addStaticData("CMD_RM_R2" , &EnumWrapper::CMD_RM_R2 , false)
      .addStaticData("CMD_BROADCAST_J3" , &EnumWrapper::CMD_BROADCAST_J3 , false)
      .addStaticData("CMD_BROADCAST_J7" , &EnumWrapper::CMD_BROADCAST_J7 , false)

      .addStaticData("TIME_MAX",&EnumWrapper::TIME_MAX,false)
      .endClass();
  }

  template<> inline void LuaInject<msg::TimeSlice> (lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::TimeSlice>("TimeSlice")
      .addData("msg_type"   , &TimeSlice::msg_type    , false)
      .addData("begin_time" , &TimeSlice::begin_time  , false)
      .addData("end_time"   , &TimeSlice::end_time    , false)
      .endClass()
      .endNamespace();
  }

  template<> inline void LuaInject<msg::SubTimeSlice>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::SubTimeSlice>("SubTimeSlice")
      .addData("msg_type"     , &SubTimeSlice::msg_type     , false)
      .addData("begin_time"   , &SubTimeSlice::begin_time   , false)
      .addData("end_time"     , &SubTimeSlice::end_time     , false)
      .addData("current_time" , &SubTimeSlice::current_time , false)
      .endClass()
      .endNamespace();
  }

  template<> inline void LuaInject<msg::JointMsg2I>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::JointMsg2I>("JointMsg2I")
      .addData("msg_type"     , &JointMsg2I::msg_type     , false)
      //.addData("track_number" , &JointMsg2I::track_number , false)
      .addData("uNPSI"        , &JointMsg2I::_uNPSI       , false)
      .addData("create_time"  , &JointMsg2I::create_time  , false)
      .addFunction("GetTrackName", &JointMsg2I::GetTrackName)
      .endClass()
      .endNamespace();
  }

  template<> inline void LuaInject<msg::JointMsg3I>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::JointMsg3I>("JointMsg3I")
      .addData("msg_type"       , &JointMsg3I::msg_type       , false)
      //.addData("track_number"   , &JointMsg3I::track_number   , false)
      .addData("track_platform" , &JointMsg3I::track_platform , false)
      .addData("track_quality"  , &JointMsg3I::track_quality  , false)
      .addData("create_time"    , &JointMsg3I::create_time    , false)
      .addFunction("GetTrackName" , &JointMsg3I::GetTrackName)
      .endClass()
      .endNamespace();
  }

  template<> inline void LuaInject<msg::JointMsg7I>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::JointMsg7I>("JointMsg7I")
      .addData("msg_type"     , &JointMsg7I::msg_type     , false)
      //.addData("track_number" , &JointMsg7I::track_number , false)
      .addData("action"       , &JointMsg7I::action       , false)
      .addData("create_time"  , &JointMsg7I::create_time  , false)
      .addFunction("GetTrackName" , &JointMsg7I::GetTrackName)
      .endClass()
      .endNamespace();
  }

  template<> inline void LuaInject<msg::LocalTrack>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::LocalTrack>("LocalTrack")
      .addData("msg_type"       , &LocalTrack::msg_type       , false)
      //.addData("track_number"   , &LocalTrack::track_number   , false)
      .addData("track_platform" , &LocalTrack::track_platform , false)
      .addData("track_quality"  , &LocalTrack::track_quality  , false)
      .addData("create_time"    , &LocalTrack::create_time    , false)
      .addFunction("GetTrackName" , &LocalTrack::GetTrackName)
      .endClass()
      .endNamespace();
  }

  template<> inline void LuaInject<msg::LocalCmd>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::LocalCmd>("LocalCmd")
      .addConstructor<void (*) ( int32_t  , const char * )>()
      .addData("msg_type"   , &LocalCmd::msg_type     , false)
      .addData("cmd_id"     , &LocalCmd::cmd_id         , false)
      //.addData("track_name" , &LocalCmd::track_name , false)
      .endClass()
      .endNamespace();
  }

  template<> inline void LuaInject<devs::core::JuScriptComponent>(lua_State *p_lua_state) {

    using namespace devs::core;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginClass<JuScriptComponent>("JuScriptComponent")
      .addFunction("BindInBroadcastBuffer" , &JuScriptComponent::BindInBroadcastBuffer)
      .addFunction("BindInCMD"  , &JuScriptComponent::BindInCMD)
      .addFunction("BindInJ2"   , &JuScriptComponent::BindInJ2)
      .addFunction("BindInJ3"   , &JuScriptComponent::BindInJ3)
      .addFunction("BindInJ7"   , &JuScriptComponent::BindInJ7)
      .addFunction("BindInLT"   , &JuScriptComponent::BindInLT)
      .addFunction("BindInSTS"  , &JuScriptComponent::BindInSTS)
      .addFunction("BindInTS"   , &JuScriptComponent::BindInTS)

      .addFunction("CorrelationTest"      , &JuScriptComponent::CorrelationTest)

      .addFunction("ExistLocalTrackInfo"  , &JuScriptComponent::ExistLocalTrackInfo)
      .addFunction("ExistRecvTrackInfo"   , &JuScriptComponent::ExistRecvTrackInfo)
      .addFunction("ExistR2"              , &JuScriptComponent::ExistR2)

      .addFunction("GetTS"              , &JuScriptComponent::GetTS)
      .addFunction("GetLocalTrackInfo"  , &JuScriptComponent::GetLocalTrackInfo)
      .addFunction("GetRecvTrackInfo"   , &JuScriptComponent::GetRecvTrackInfo)
      .addFunction("GetR2"              , &JuScriptComponent::GetR2)

      .addFunction("ViewLocalTrackDict" , &JuScriptComponent::ViewLocalTrackDict)
      .addFunction("ViewRecvTrackDict"  , &JuScriptComponent::ViewRecvTrackDict)
      .addFunction("ViewR2Dict"         , &JuScriptComponent::ViewR2Dict)

      .addFunction("SetR2" , &JuScriptComponent::SetR2)

      .endClass();
  }

  template<> inline void LuaInject<devs::handler::TrackInformation>(lua_State *p_lua_state) {
    using namespace devs::handler;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginClass<TrackInformation>("TrackInformation")
      .addData("track_number" , &TrackInformation::track_number)
      .addData("track_platform" , &TrackInformation::track_platform)
      .addData("track_quality" , &TrackInformation::track_quality)
      .addData("uSTN" , &TrackInformation::_uSTN)
      .addData("create_time" , &TrackInformation::create_time)
      .addFunction("GetJ3" , &TrackInformation::Get<msg::JointMsg3I>)
     .endClass();
  }

}