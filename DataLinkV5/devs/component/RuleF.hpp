#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
#include<list>
namespace devs::component {
  /*
    在有LT的前提下,接收 ACT=0 的 J7消息,
    等到 TS 触发时候.进行判断在此期间是否收到 对应的 J3 消息
    如果有:
      有R2,就释放R2
    如果没有:
      进行航迹的相关性判断(注释1)


    注释1:相关性判断全部设置为通过. 时间:2019年9月4日 
  */
  class RuleF
    :JuComponent
  {
  public:
    RuleF(Ju& ju, Digraph& digraph, const std::string&name, PortType uid);
    _FUNC_MakeShared_(RuleF);

    // 通过 JuComponent 继承
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;


  private:


    bool is_recv_ts=false;
    std::list<msg::JointMsg7I> j7ActZeroList;

  };
  _FUNC_CreatSptr_(RuleF);
}
