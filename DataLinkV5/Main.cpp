

#include"devs/hub.hpp"
#include"devs/ju.hpp"
#include"devs/message/message.hpp"
#include"devs/global_time.hpp"
#include"utility/utility.hpp"

#include<iostream>

int main() {
	devs::Digraph dome;
	devs::Hub hub = devs::Hub(dome, "123", 666);
	auto ju_1 = devs::CreatSptrJu(dome, "ju_1", 100);
	auto ju_2 = devs::CreatSptrJu(dome, "ju_2", 200);

	hub.add_ju(ju_1);
	hub.add_ju(ju_2);

	auto at_1 = devs::msg::ActiveTrack(
		util::TrackNumberHandler::Create("Ultraman").c_str(),
		devs::msg::Platform_AIR, 10, 1000
	);

	/*auto at_2 = devs::msg::ActiveTrack(
		util::TrackNumberHandler::Create("UFO").c_str(),
		devs::msg::Platform_AIR, 8, 1000
	);*/

	auto j30i_1 = devs::msg::JointMsg3I(
		util::TrackNumberHandler::Create("Ultraman").c_str(),
		"ju-3", devs::msg::Platform_AIR, 8, 400);

	hub.push_buffer(1100, hub.port_broadcast_send, j30i_1);
	hub.push_buffer(10000, hub.map_private_recv_port[ju_1->uid], at_1);
	
	//hub.push_buffer(1500, hub.map_private_recv_port[ju_2->uid], at_2);

	devs::Simulator sim = devs::Simulator(&dome);
	//sim.execUntil(100'000'000);
	while ((devs::global::global_msec = sim.nextEventTime()) < 100'000) {
		sim.execNextEvent();
	}


	return 0;
}