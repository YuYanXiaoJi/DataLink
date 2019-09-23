#include"devs/core/ju.hpp"
#include"devs/core/hub.hpp"

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