#include"devs/core/ju.hpp"
#include"devs/core/hub.hpp"

int main() {
  devs::Digraph dome;
  devs::core::Hub hub = devs::core::Hub(dome , "123");
  auto ju_1 = devs::core::Ju::make_shared(dome , "ju_1" ,10 );

  hub.AddJu(ju_1);

  devs::Simulator sim = devs::Simulator(&dome);

  int64_t total_time = 200;
  while(devs::Time::Update(sim.nextEventTime()) < total_time)
    sim.execNextEvent();
  return 0;
}