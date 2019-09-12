#include "script_component.hpp"

#include<Lua/LuaBridge.hpp>
cc::ScriptComponent::ScriptComponent(const string &filename , devs::Digraph &digrapg , Generator &parent)
  :Component(digrapg, parent)
{
  this->m_pluaState = luaL_newstate();
  luaL_openlibs(m_pluaState);
}

void cc::ScriptComponent::External(const devs::PortType &recvPort , const devs::SptrBlob sptrBlob)
{
}

void cc::ScriptComponent::Internal()
{
}

void cc::ScriptComponent::Output(devs::IO_Bag &yb)
{
}

devs::TimeType cc::ScriptComponent::Ta()
{
  return devs::TimeType();
}

