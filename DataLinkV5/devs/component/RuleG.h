#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {
  class RuleG
    : JuComponent
  {

  public:
    RuleG(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);
    _FUNC_MakeShared_(RuleG);

    // Í¨¹ý JuComponent ¼Ì³Ð
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;
  private:
    std::list<util::SptrBlob> at_sptr_blob_list;
  };
  _FUNC_CreatSptr_(RuleG);
}