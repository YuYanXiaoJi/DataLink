#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>

#include"../message/message.hpp"
namespace devs::lua_handler {
  template<typename _Ty> void LuaInject(lua_State *p_lua_state) { static_assert( false , "未实现该类型的 Inject" ); }

  template<> void LuaInject<msg::TimeSlice> (lua_State *p_lua_state) {
    using namespace devs::msg;
    luabridge::getGlobalNamespace(p_lua_state)
      .beginClass<msg::TimeSlice>("TimeSlice")
      .addConstructor<void(*)( std::int32_t )>()
      .addData("begin_time" , &TimeSlice::begin_time , false)
      .addData("end_time" , &TimeSlice::end_time)
      .addData("type" , &TimeSlice::msg_type)
      .endClass();
  }
}