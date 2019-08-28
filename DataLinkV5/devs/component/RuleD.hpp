#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {
	class RuleD
		: JuComponent
	{

	public:
		RuleD(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);
		FUNC_MakeShared(RuleD);

		// ͨ�� JuComponent �̳�
		virtual void delta_int() override;
		virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
		virtual void output_func(IO_Bag & yb) override;
		virtual devs::TimeType ta() override;
	private:
		std::list<util::SptrBlob> j3_sptr_blob_list;
	};
	FUNC_CreatSptr(RuleD);
}