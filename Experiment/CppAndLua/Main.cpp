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
  Integer(std::int32_t val=-1) {
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

  std::string to_string() {
    return std::to_string(src);
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
    .addFunction("__tostring",&Integer::to_string)
    .addData("src" , &Integer::src , false)
    .addData("val" , &Integer::val)
    .addData("inc" , &Integer::inc)
    .endClass()
    .endNamespace();
}
lua_State *lua_state;

luabridge::LuaRef view_map() {
  std::map<std::string , Integer> dict;
  dict["a"] = Integer(1);
  dict["b"] = Integer(2);
  dict["c"] = Integer(3);

  luabridge::LuaRef table(lua_state , luabridge::newTable(lua_state));//= luabridge::newTable(lua_state);
  for(auto [key , value] : dict) {
    std::string k = key;
    table[k] = value;
  }

  return table;
}

int main() {
  
  lua_state = luaL_newstate();
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

  luabridge::getGlobalNamespace(lua_state)
    .addFunction("view_map" , view_map);
    
  

  luaL_dofile(lua_state , "1.lua");
  /*luaL_dofile(lua_state , "integer.lua");
  luabridge::LuaRef v = luabridge::getGlobal(lua_state , "i");
  v["inc"] = 6666;

  auto ref_print = luabridge::getGlobal(lua_state , "IntPrint");
  ref_print(i);

  auto s = v.cast<Integer>();


  auto ary = luabridge::getGlobal(lua_state , "ary");
  for(auto i : { 0,1,2,3,4 })
    std::cout << ary[i].cast<int>();*/
  /*auto ret = 0;
  ret = luaL_dofile(lua_state , "List.lua");
  ret = luaL_dofile(lua_state,  "integer.lua");*/
  lua_close(lua_state);
  return 0;
}