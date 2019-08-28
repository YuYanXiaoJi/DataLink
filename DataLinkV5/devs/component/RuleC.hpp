#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {
	class RuleC
		: JuComponent
	{

	public:
		RuleC(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);
		FUNC_MakeShared(RuleC);

		// Í¨¹ý JuComponent ¼Ì³Ð
		virtual void delta_int() override;
		virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
		virtual void output_func(IO_Bag & yb) override;
		virtual devs::TimeType ta() override;
	private:
		bool is_recv_ts = false;
	};
	FUNC_CreatSptr(RuleC);
}