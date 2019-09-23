#include"devs/core/ju.hpp"
#include"devs/core/hub.hpp"

#if 0
int main() {
  devs::Digraph dome;
  devs::core::Hub hub = devs::core::Hub(dome , "123");
  auto ju_1 = devs::core::Ju::make_shared(dome , "ju_1" ,10 );
  auto ju_2 = devs::core::Ju::make_shared(dome , "ju_2" , 10);
  hub.AddJu(ju_1);
  hub.AddJu(ju_2);
  devs::Simulator sim = devs::Simulator(&dome);


  auto at_1 = devs::msg::LocalTrack(
    devs::handler::TrackNumberHandler::Create("Ultraman").c_str() ,
    devs::msg::Platform_AIR , 8 , 1000
  );

  hub.PushBuffer(1000 , hub.map_private_port[ju_1->uid] , at_1);

  int64_t total_time = 100'000;
  while(devs::Time::Update(sim.nextEventTime()) < total_time)
    sim.execNextEvent();
  return 0;
}
#elif 1
//ÑéÖ¤ Message to Lua 
#include"devs/message/message.hpp"
#include"devs/handler/lua_inject_handler.hpp"

#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>

using namespace devs::message;
using namespace devs;
int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  lua_handler::LuaInject<msg::TimeSlice>(L);
  lua_handler::LuaInject<msg::SubTimeSlice>(L);
  lua_handler::LuaInject<msg::JointMsg2I>(L);
  lua_handler::LuaInject<msg::JointMsg3I>(L);
  lua_handler::LuaInject<msg::JointMsg7I>(L);
  lua_handler::LuaInject<msg::LocalTrack>(L);
  lua_handler::LuaInject<msg::LocalCmd>(L);



}

#endif