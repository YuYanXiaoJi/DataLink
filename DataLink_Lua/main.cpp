#include"devs/core/ju.hpp"
#include"devs/core/hub.hpp"

int main() {
  devs::Digraph dome;
  devs::core::Hub hub = devs::core::Hub(dome , "123");
  auto ju_1 = devs::core::Ju::make_shared(dome , "ju_1" ,10 );

  hub.AddJu(ju_1);

  devs::Simulator sim = devs::Simulator(&dome);

  while(devs::Time::Update(sim.nextEventTime()) < 500'000)
    sim.execNextEvent();
  return 0;
}