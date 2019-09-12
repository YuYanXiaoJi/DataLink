#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>
#include<string>
#include<cstdio>
#include<fstream>
#include<sstream>
class Integer {
public:
  Integer(std::int32_t val) {
    this->src = val;
    this->val = val;
    this->inc = 0;
  }

  std::int32_t src;
  std::int32_t val;
  std::int32_t inc;

  template<class... _Types>
  inline static auto MakeShared(_Types&&... _Args) {
    return std::make_shared<Integer>(_Args);
  }
}; 


int main() {
  
  lua_State* lua_state = luaL_newstate();
  luaL_openlibs(lua_state);

  luabridge::getGlobalNamespace(lua_state)
    .beginNamespace("Integer")
    .beginClass<Integer>("obj")
    .addData("src" , &Integer::src , false)
    .addData("val" , &Integer::val)
    .addData("inc" , &Integer::inc)
    .endClass()
    .endNamespace();

  Integer i(27);
  luabridge::setGlobal(lua_state, &i, "obj");

  
  luaL_dofile(lua_state , "integer.lua");
  luabridge::LuaRef v = luabridge::getGlobal(lua_state , "obj");
  v["inc"] = 6666;
  /*auto ret = 0;
  ret = luaL_dofile(lua_state , "List.lua");
  ret = luaL_dofile(lua_state,  "integer.lua");*/
  lua_close(lua_state);
  return 0;
}