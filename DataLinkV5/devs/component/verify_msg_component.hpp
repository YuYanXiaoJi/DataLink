#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {
  class VerifyMsgComponent
    : JuComponent
  {
  public:
    VerifyMsgComponent(Ju& ju, Digraph& digraph, const std::string&name, PortType uid);

    _FUNC_MakeShared_(VerifyMsgComponent)

    // Í¨¹ý JuComponent ¼Ì³Ð
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;
  };

  _FUNC_CreatSptr_(VerifyMsgComponent);
}
