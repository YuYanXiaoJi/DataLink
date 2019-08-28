#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {
	class RuleA
		: JuComponent
	{

	public:
		RuleA(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);

		// ͨ�� JuComponent �̳�
		virtual void delta_int() override;
		virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
		virtual void output_func(IO_Bag & yb) override;
		virtual devs::TimeType ta() override;

		//static inline std::shared_ptr<RuleA> 
		//	make_shared(Ju& ju, Digraph& digraph, const std::string&name, PortType uid)
		//{
		//	return std::make_shared<RuleA>(ju, digraph, name, uid);
		//}
		FUNC_MakeShared(RuleA)
	public:
		std::list<IO_Type> buffer_list;
	};
	//const auto CreatSptrRuleA = RuleA::make_shared;
	FUNC_CreatSptr(RuleA);
}