#pragma once

#include"calc_odd.hpp"
#include"clac_even.hpp"
#include"generator.hpp"

int main() {
  devs::Digraph dome;
  cc::CalcEven even;
  cc::CalcOdd odd;
  cc::Generator gener;

  dome.couple(&gener, gener.sendOdd, &odd, odd.recvOdd);
  dome.couple(&gener, gener.sendEven, &even, even.recvEven);

  dome.couple(&odd, odd.send, &gener, gener.recv);
  dome.couple(&even, even.send, &gener, gener.recv);


  devs::Simulator sim(&dome);
  while (sim.nextEventTime() < devs::TIME_MAX) {
    sim.execNextEvent();
  }
}