#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>

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



using namespace devs::message;
using namespace devs;
int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  lua_handler::LuaInject<msg::TimeSlice>(L);
  auto ts = msg::TimeSlice(0 , 999);
  luabridge::setGlobal(L , &ts , "ts");

  lua_handler::LuaInject<msg::SubTimeSlice>(L);
  auto sts = msg::SubTimeSlice(ts , 666);
  luabridge::setGlobal(L , &sts , "sts");

  lua_handler::LuaInject<msg::JointMsg2I>(L);
  auto j2 = msg::JointMsg2I("yd-00000001" , 77 , 200);
  luabridge::setGlobal(L , &j2 , "j2");

  lua_handler::LuaInject<msg::JointMsg3I>(L);
  auto j3 = msg::JointMsg3I("yd-00000002" , TrackPlatform::Platform_AIR , 66 , 300 , 77);
  luabridge::setGlobal(L , &j3 , "j3");


  lua_handler::LuaInject<msg::JointMsg7I>(L);
  auto j7 = msg::JointMsg7I("yd-00000003" , 0 , 700);
  luabridge::setGlobal(L , &j7 , "j7");

  lua_handler::LuaInject<msg::LocalTrack>(L);
  auto lt = msg::LocalTrack("yd-00000004" , TrackPlatform::Platform_LAND , 33 , 888);
  luabridge::setGlobal(L , &lt , "lt");

  lua_handler::LuaInject<msg::LocalCmd>(L);
  auto cmd = msg::LocalCmd(100 , "yd");
  luabridge::setGlobal(L , &cmd , "cmd");

  luaL_dofile(L , "res/VerifyMessage.lua");
}

#endif