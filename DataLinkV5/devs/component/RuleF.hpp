#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
#include<list>
namespace devs::component {
  /*
    ����LT��ǰ����,���� ACT=0 �� J7��Ϣ,
    �ȵ� TS ����ʱ��.�����ж��ڴ��ڼ��Ƿ��յ� ��Ӧ�� J3 ��Ϣ
    �����:
      ��R2,���ͷ�R2
    ���û��:
      ���к�����������ж�(ע��1)


    ע��1:������ж�ȫ������Ϊͨ��. ʱ��:2019��9��4�� 
  */
  class RuleF
    :JuComponent
  {
  public:
    RuleF(Ju& ju, Digraph& digraph, const std::string&name, PortType uid);
    _FUNC_MakeShared_(RuleF);

    // ͨ�� JuComponent �̳�
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
