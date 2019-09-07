#include<Lua/lua.hpp>
#include<Lua/LuaBridge.hpp>
#include<string>
#include<cstdio>
class test_lua
{
public:
  test_lua()
  {
    m_test_string = "c++ test string";
  }
  ~test_lua()
  {
  }
  //test方法
  void test(int a, int b)
  {
    printf("c++ test function %d+%d=%d\n", a, b, a + b);
  }

  //属性set方法
  void SetName(std::string name)
  {
    m_name = name;
  }
  //属性get方法，注意需要后面加const
  std::string GetName() const
  {
    return m_name;
  }
  //供lua调用方法，返回多个参数方法
  int cFunc(lua_State* L)
  {
    //返回参数1
    lua_pushstring(L, "str1");
    //返回参数1
    lua_pushstring(L, "str2");
    //返回参数个数
    return 2;
  }
  std::string m_test_string;
  std::string m_name;
  static int m_static_data;
};
//test_lua静态变量定义（静态变量在类内只是声明）
int test_lua::m_static_data;
//test_lua子类
class test_lua_child :public test_lua
{
public:
  test_lua_child(std::string test)
    :m_test_child_string(test)
  {
    printf("call test_lua_child constructor\n");
  }
  ~test_lua_child()
  {
  }
  std::string m_test_child_string;
};


int main() {
  lua_State* lua_state = luaL_newstate();
  //加载Lua基本库
  luaL_openlibs(lua_state);
  luabridge::getGlobalNamespace(lua_state)
    .beginNamespace("test")
    .beginClass<test_lua>("test_lua")
    .addConstructor<void(*) (void)>()//无参构造函数的注册
    .addData("test_str", &test_lua::m_test_string)//注册变量到lua
    .addStaticData("static_data", &test_lua::m_static_data)//注册静态变量到lua
    .addFunction("test", &test_lua::test)//注册test、方法到lua（addStaticFunction静态函数注册也类似）
    .addProperty("name", &test_lua::GetName, &test_lua::SetName)//属性方法的注册（addStaticProperty静态属性方法也类似）
    .addCFunction("cFunc", &test_lua::cFunc)//注册返回多个参数给lua的方法
    .endClass()
    .deriveClass<test_lua_child, test_lua>("test_lua_child")//子类的注册
    .addConstructor<void(*) (std::string)>()//有参构造函数的注册
    .addData("test_child_string", &test_lua_child::m_test_child_string)//注册变量到lua
    .endClass()
    .endNamespace();

  //创建test_lua对象
  test_lua test;
  luabridge::setGlobal(lua_state, &test, "test_lua");//注册test_lua对象到lua

  //运行lua脚本
  luaL_dofile(lua_state, "1.lua");
  //关闭Lua
  lua_close(lua_state);


  
  return 0;
}