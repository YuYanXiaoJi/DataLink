#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {
  class RuleF
    : JuComponent
  {

  public:
    RuleF(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);
    _FUNC_MakeShared_(RuleF);

    // Í¨¹ý JuComponent ¼Ì³Ð
    virtual void delta_int() override;
    virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
    virtual void output_func(IO_Bag & yb) override;
    virtual devs::TimeType ta() override;
  private:
    std::list<util::SptrBlob> j7_sptr_blob_list;
  };
  _FUNC_CreatSptr_(RuleF);
}