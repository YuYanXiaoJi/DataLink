#pragma once
#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>
#include"integer.hpp"
#include"script_component.hpp"
#include"typedef.hpp"
#include"blob.hpp"
namespace cc::lua_handler {


  template<typename _Ty> void Inject(lua_State *pLuaState) {
    static_assert( false , "this class no define its inject func" );
  }



  template<> inline void Inject<Integer>(lua_State *pLuaState) {
    luabridge::getGlobalNamespace(pLuaState)
      .beginClass<Integer>("Integer")
      .addConstructor<void( * )( std::int32_t )>()
      .addData("src" , &Integer::src , false)
      .addData("type" ,&Integer::type , false)
      .addData("val" , &Integer::val)
      .addData("inc" , &Integer::inc)
      .addStaticData("t",&Integer::t,false)
      .endClass();
  }
  template<> inline void Inject<Blob>(lua_State *pLuaState) {
    luabridge::getGlobalNamespace(pLuaState)
      .beginClass<Blob>("Blob")
      .addConstructor<void( * )( const Integer & )>()
      .endClass();
  }


  template<> inline void Inject<cc::ScriptComponent>(lua_State *pLuaState) {
    luabridge::getGlobalNamespace(pLuaState)
      .beginClass<cc::ScriptComponent>("ScriptComponent")
      .addFunction("BindOdd" , &cc::ScriptComponent::BindOdd)
      .addFunction("BindEven" , &cc::ScriptComponent::BindEven)
      .addFunction("BindPrint" , &cc::ScriptComponent::BindPrint)
      .addFunction("BindSend" , &cc::ScriptComponent::BindSend)
      .addFunction("SendFunc" , &cc::ScriptComponent::SendFunc)
      .addFunction("SendFuncBlob" , &cc::ScriptComponent::SendFuncBlob)
      .addFunction("SendFuncLuaRef" , &cc::ScriptComponent::SendFuncLuaRef)
      .endClass();
  }

  template<> inline void Inject<devs::TimeType>(lua_State *pLuaState) {
    luabridge::getGlobalNamespace(pLuaState)
      .beginNamespace("Const")
      .addVariable("kTimeMax" , &devs::TIME_MAX , false)
      .endNamespace();
  }
}