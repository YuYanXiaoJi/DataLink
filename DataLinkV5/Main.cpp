

#include"devs/hub.hpp"
#include"devs/ju.hpp"
#include"devs/message/message.hpp"
#include"devs/time.hpp"
#include"utility/utility.hpp"

#include<iostream>

int main() {
  devs::Digraph dome;
  devs::Hub hub = devs::Hub(dome, "123", 666);
  auto ju_1 = devs::CreatSptrJu(dome, "ju_1", 100,10);
  auto ju_2 = devs::CreatSptrJu(dome, "ju_2", 200,10);

  hub.add_ju(ju_1);
  hub.add_ju(ju_2);

  auto at_1 = devs::msg::LocalTrack(
    devs::TrackNumberHandler::Create("Ultraman").c_str(),
    devs::msg::Platform_AIR, 8, 1000
  );

  auto at_2 = devs::msg::LocalTrack(
    devs::TrackNumberHandler::Create("Ultraman").c_str(),
    devs::msg::Platform_AIR, 4, 1000
  );

  auto j30i_1 = devs::msg::JointMsg3I(
    devs::TrackNumberHandler::Create("Ultraman").c_str(),
    "ju-3", devs::msg::Platform_AIR, 8, 400,10);

  hub.push_buffer(10000, hub.map_private_recv_port[ju_1->uid], at_1);
  //hub.push_buffer(11000, hub.port_broadcast_send, j30i_1);
  hub.push_buffer(1500, hub.map_private_recv_port[ju_2->uid], at_2);

  devs::Simulator sim = devs::Simulator(&dome);



  while (devs::Time::update(sim.nextEventTime()) < 50'000)
    sim.execNextEvent();
  return 0;
}