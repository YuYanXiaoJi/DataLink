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
  //test����
  void test(int a, int b)
  {
    printf("c++ test function %d+%d=%d\n", a, b, a + b);
  }

  //����set����
  void SetName(std::string name)
  {
    m_name = name;
  }
  //����get������ע����Ҫ�����const
  std::string GetName() const
  {
    return m_name;
  }
  //��lua���÷��������ض����������
  int cFunc(lua_State* L)
  {
    //���ز���1
    lua_pushstring(L, "str1");
    //���ز���1
    lua_pushstring(L, "str2");
    //���ز�������
    return 2;
  }
  std::string m_test_string;
  std::string m_name;
  static int m_static_data;
};
//test_lua��̬�������壨��̬����������ֻ��������
int test_lua::m_static_data;
//test_lua����
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
  //����Lua������
  luaL_openlibs(lua_state);
  luabridge::getGlobalNamespace(lua_state)
    .beginNamespace("test")
    .beginClass<test_lua>("test_lua")
    .addConstructor<void(*) (void)>()//�޲ι��캯����ע��
    .addData("test_str", &test_lua::m_test_string)//ע�������lua
    .addStaticData("static_data", &test_lua::m_static_data)//ע�ᾲ̬������lua
    .addFunction("test", &test_lua::test)//ע��test��������lua��addStaticFunction��̬����ע��Ҳ���ƣ�
    .addProperty("name", &test_lua::GetName, &test_lua::SetName)//���Է�����ע�ᣨaddStaticProperty��̬���Է���Ҳ���ƣ�
    .addCFunction("cFunc", &test_lua::cFunc)//ע�᷵�ض��������lua�ķ���
    .endClass()
    .deriveClass<test_lua_child, test_lua>("test_lua_child")//�����ע��
    .addConstructor<void(*) (std::string)>()//�вι��캯����ע��
    .addData("test_child_string", &test_lua_child::m_test_child_string)//ע�������lua
    .endClass()
    .endNamespace();

  //����test_lua����
  test_lua test;
  luabridge::setGlobal(lua_state, &test, "test_lua");//ע��test_lua����lua

  //����lua�ű�
  luaL_dofile(lua_state, "1.lua");
  //�ر�Lua
  lua_close(lua_state);


  
  return 0;
}