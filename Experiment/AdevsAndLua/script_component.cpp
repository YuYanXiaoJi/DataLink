#include "script_component.hpp"
#include "integer.hpp"
#include<Lua/LuaBridge.hpp>
#include"lua_handler.hpp"
#include<functional>

cc::ScriptComponent::ScriptComponent(const string &filename , devs::Digraph &digrapg , Generator &parent)
  :Component(digrapg, parent)
{
  this->m_pLuaState = luaL_newstate();
  luaL_openlibs(m_pLuaState);
  luaL_dofile(m_pLuaState , "List.lua");

  luaL_dofile(m_pLuaState , filename.c_str());


  lua_handler::Inject<Integer>(this->m_pLuaState);
  lua_handler::Inject<Blob>(this->m_pLuaState);
  lua_handler::Inject<devs::TimeType>(this->m_pLuaState);
  lua_handler::Inject<cc::ScriptComponent>(this->m_pLuaState);

  luabridge::setGlobal(this->m_pLuaState , &( *this ) , "this");
  




  luaL_dofile(m_pLuaState , filename.c_str()); //load lua file

  //get  func;
  auto m_luaRefInit = luabridge::getGlobal(m_pLuaState , "Init");

  if(m_luaRefInit.isFunction())
    m_luaRefInit();
 
  //run init
  
}

void cc::ScriptComponent::Input(const devs::PortType &recvPort , const SptrBlob sptrBlob)
{
  auto m_luaRefInput = luabridge::getGlobal(m_pLuaState , "Input");
  if(m_luaRefInput.isFunction())
    m_luaRefInput(recvPort , sptrBlob->get<Integer>());
}

void cc::ScriptComponent::Internal()
{

  auto m_luaRefInternal = luabridge::getGlobal(m_pLuaState , "Internal");
  if(m_luaRefInternal.isFunction())
    m_luaRefInternal();
}

void cc::ScriptComponent::Output(devs::IO_Bag &yb)
{
  p_yb = &yb;

  auto m_luaRefOutput = luabridge::getGlobal(m_pLuaState , "Output");
  if(m_luaRefOutput.isFunction())
    m_luaRefOutput();

  p_yb = nullptr;
}

devs::TimeType cc::ScriptComponent::Ta()
{
  auto m_luaRefTa = luabridge::getGlobal(m_pLuaState , "Ta");
  if(m_luaRefTa.isFunction()) {
    auto ret_ref=m_luaRefTa();
    return  ret_ref.cast<devs::TimeType>();
  }
  return devs::TIME_MAX;
}

void cc::ScriptComponent::SendFunc(devs::PortType sendPort , Integer info)
{
  p_yb->insert({ sendPort,Blob::MakeShared(info)});
}

void cc::ScriptComponent::SendFuncBlob(devs::PortType sendPort , Blob info)
{
  SendFunc(sendPort , info.get<Integer>());
}

void cc::ScriptComponent::SendFuncLuaRef(devs::PortType sendPort , luabridge::LuaRef info)
{
  if(info["type"].cast<uint8_t>()== MsgType::MSG_Integer)
    SendFunc(sendPort , info.cast<Integer>());
}



