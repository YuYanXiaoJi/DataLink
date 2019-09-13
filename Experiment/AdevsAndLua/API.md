#### 常数

namespace is *Const* , 使用方法 Const.Name 
1. 	kTimeMax , Max(TimeType) ,注意的是在lua中number 是 double类型.



#### Devs 接口

##### 1. Input(port,msg)

```c++
void External(const PortType &recvPort , const devs::SptrBlob sptrBlob){
    auto msg=sptrBlob->get<目标类型>();
    //...
    auto Input=luabrigde::GetGobal(L,"Input"); //获得Lua中的Input函数
    //...
    Input(recvPort,msg)//执行
}
```

注:关于 *External* 函数与 Adevs::delta_ext 关系请看 *AtomicAbstract* class

##### 2.Ta() & Internal() 

调用方式与 *Input* 函数类型

##### 3.Init()

起到类似构造函数的工作.主要是用于调用 BindXXX 函数用于绑定端口

##### 4.Output()

起到*output_func*相关的功能.

