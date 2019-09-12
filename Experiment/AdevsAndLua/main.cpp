#pragma once

#include"calc_odd.hpp"
#include"clac_even.hpp"
#include"generator.hpp"

int main() {
  devs::Digraph dome;
  cc::Generator gener;

  cc::CalcEven even(dome,gener);
  cc::CalcOdd odd(dome, gener);


  devs::Simulator sim(&dome);
  while (sim.nextEventTime() < devs::TIME_MAX) {
    sim.execNextEvent();
  }
}