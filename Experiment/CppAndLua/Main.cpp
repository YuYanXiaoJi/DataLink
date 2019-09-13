#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>
#include<string>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
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

template<typename _Ty>
void Inject(lua_State *pLuaState) {
  static_assert( false,"this class no define its inject func");
}

template<typename _Ty>
_Ty Get(lua_State *pLuaState) {
  static_assert( false , "this class no define its inject func" );
}

template<>
void Inject<Integer>(lua_State *pLuaState) {
  luabridge::getGlobalNamespace(pLuaState)
    .beginNamespace("Msg")
    .beginClass<Integer>("Integer")
    .addConstructor<void(*)(std::int32_t)>()
    .addData("src" , &Integer::src , false)
    .addData("val" , &Integer::val)
    .addData("inc" , &Integer::inc)
    .endClass()
    .endNamespace();
}





int main() {
  
  lua_State* lua_state = luaL_newstate();
  luaL_openlibs(lua_state);

  /*
  luabridge::getGlobalNamespace(lua_state)
    .beginNamespace("Integer")
    .beginClass<Integer>("obj")
    .addData("src" , &Integer::src , false)
    .addData("val" , &Integer::val)
    .addData("inc" , &Integer::inc)
    .endClass()
    .endNamespace();
*/
  Inject<Integer>(lua_state);

  Integer i(27);
  luabridge::setGlobal(lua_state, &i, "i");

  
  luaL_dofile(lua_state , "integer.lua");
  luabridge::LuaRef v = luabridge::getGlobal(lua_state , "i");
  v["inc"] = 6666;

  auto ref_print = luabridge::getGlobal(lua_state , "IntPrint");
  ref_print(i);

  auto s = v.cast<Integer>();


  auto ary = luabridge::getGlobal(lua_state , "ary");
  for(auto i : { 0,1,2,3,4 })
    std::cout << ary[i].cast<int>();
  /*auto ret = 0;
  ret = luaL_dofile(lua_state , "List.lua");
  ret = luaL_dofile(lua_state,  "integer.lua");*/
  lua_close(lua_state);
  return 0;
}