#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {
	class RuleA
		: JuComponent
	{

	public:
		RuleA(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);

		// Í¨¹ý JuComponent ¼Ì³Ð
		virtual void delta_int() override;
		virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
		virtual void output_func(IO_Bag & yb) override;
		virtual devs::TimeType ta() override;

		static inline std::shared_ptr<RuleA> 
			make_shared(Ju& ju, Digraph& digraph, const std::string&name, PortType uid)
		{
			return std::make_shared<RuleA>(ju, digraph, name, uid);
		}
	public:
		std::list<IO_Type> buffer_list;
	};

	inline auto CreatSptrRuleA(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid) {
		return RuleA::make_shared(ju,_digraph, _name, _uid);
	}
}