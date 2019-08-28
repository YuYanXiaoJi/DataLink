#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {

	// 只处理 set_r2 & rm_r2
	class R2 
		: JuComponent
	{

	public:
		R2(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);

		FUNC_MakeShared(R2);

		// 通过 JuComponent 继承
		virtual void delta_int() override;
		virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
		virtual void output_func(IO_Bag & yb) override;
		virtual devs::TimeType ta() override;

		
	public:
		std::list<msg::LocalCmd> local_cmd_list;
	};
	//const auto CreatSptrRuleA = RuleA::make_shared;
	FUNC_CreatSptr(R2);
}