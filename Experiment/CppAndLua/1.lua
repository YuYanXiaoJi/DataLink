--lua ��ӡlua script
print("lua script") 
--���ó�Ա����m_test_string(test_strΪע�������)
print(test_lua.test_str)
--����c++��̬��������Ҫ����test�����ռ䣩
test.test_lua.static_data=12
print("static_data: "..test.test_lua.static_data)
--����c++��test_lua����name
test_lua.name="name_property";
print("name: "..test_lua.name);
--lua����c++����test_luaΪc++����lua��ע����������test����
test_lua:test(3,4)

--����c++���÷������ض��ֵ
local ret1,ret2 = test_lua:cFunc()
print("ret1="..ret1.." ret2="..ret2)

--����test_lua_child����
local test_lua_child = test.test_lua_child("test_string")
--���������
print("child string:"..test_lua_child.test_child_string);
--���ø����name����
test_lua_child.name="child_name_property";
print("name:"..test_lua_child.name);

--lua �����ӷ�
function lua_add_function(a,b)
    print("lua_add_function") 
    return a+b;
end

--lua �����ַ����ӷ���..������﷨��
function lua_add_str_function(a,b)
    print("lua_add_str_function") 
    return a..b;
end
