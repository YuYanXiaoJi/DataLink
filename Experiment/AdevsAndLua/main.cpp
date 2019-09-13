#pragma once

#include"calc_odd.hpp"
#include"clac_even.hpp"
#include"generator.hpp"
#include"lua_handler.hpp"
#include"script_component.hpp"
int main() {

  devs::Digraph dome;
  cc::Generator gener;

  cc::ScriptComponent sc_odd = cc::ScriptComponent("odd.lua" , dome , gener);
  cc::ScriptComponent sc_even = cc::ScriptComponent("even.lua" , dome , gener);
  cc::ScriptComponent sc_print = cc::ScriptComponent("print.lua" , dome , gener);

  devs::Simulator sim(&dome);
  while (sim.nextEventTime() < devs::TIME_MAX) {
    sim.execNextEvent();
  }
}