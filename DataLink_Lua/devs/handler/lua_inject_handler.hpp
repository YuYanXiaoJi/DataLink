#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>

#include"../message/message.hpp"
namespace devs::lua_handler {
  template<typename _Ty> void LuaInject(lua_State *p_lua_state) { static_assert( false , "未实现该类型的 Inject" ); }


  

  template<> void LuaInject<msg::TimeSlice> (lua_State *p_lua_state) {
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

  template<> void LuaInject<msg::SubTimeSlice>(lua_State *p_lua_state) {
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

  template<> void LuaInject<msg::JointMsg2I>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::JointMsg2I>("JointMsg2I")
      .addData("msg_type"     , &JointMsg2I::msg_type     , false)
      .addData("track_number" , &JointMsg2I::track_number , false)
      .addData("uNPSI"        , &JointMsg2I::_uNPSI       , false)
      .addData("create_time"  , &JointMsg2I::create_time  , false)
      .addFunction("GetTrackName", &JointMsg2I::GetTrackName)
      .endClass()
      .endNamespace();
  }

  template<> void LuaInject<msg::JointMsg3I>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::JointMsg3I>("JointMsg3I")
      .addData("msg_type"       , &JointMsg3I::msg_type       , false)
      .addData("track_number"   , &JointMsg3I::track_number   , false)
      .addData("track_platform" , &JointMsg3I::track_platform , false)
      .addData("track_quality"  , &JointMsg3I::track_quality  , false)
      .addData("create_time"    , &JointMsg3I::create_time    , false)
      .addFunction("GetTrackName" , &JointMsg3I::GetTrackName)
      .endClass()
      .endNamespace();
  }

  template<> void LuaInject<msg::JointMsg7I>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::JointMsg7I>("JointMsg7I")
      .addData("msg_type"     , &JointMsg7I::msg_type     , false)
      .addData("track_number" , &JointMsg7I::track_number , false)
      .addData("action"       , &JointMsg7I::action       , false)
      .addData("create_time"  , &JointMsg7I::create_time  , false)
      .addFunction("GetTrackName" , &JointMsg7I::GetTrackName)
      .endClass()
      .endNamespace();
  }

  template<> void LuaInject<msg::LocalTrack>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::LocalTrack>("LocalTrack")
      .addData("msg_type"       , &LocalTrack::msg_type       , false)
      .addData("track_number"   , &LocalTrack::track_number   , false)
      .addData("track_platform" , &LocalTrack::track_platform , false)
      .addData("track_quality"  , &LocalTrack::track_quality  , false)
      .addData("create_time"    , &LocalTrack::create_time    , false)
      .addFunction("GetTrackName" , &LocalTrack::GetTrackName)
      .endClass()
      .endNamespace();
  }

  template<> void LuaInject<msg::LocalCmd>(lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginNamespace("Message")
      .beginClass<msg::LocalCmd>("LocalCmd")
      .addConstructor<void ( * ) ( int32_t  , const char * )>()
      .addData("msg_type" , &LocalCmd::msg_type     , false)
      .addData("cmd_id" , &LocalCmd::cmd_id         , false)
      .addData("track_name" , &LocalCmd::track_name , false)
      .endClass()
      .endNamespace();
  }
}