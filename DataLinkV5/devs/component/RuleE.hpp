#pragma once
#include"../ju_component.hpp"
#include"../../utility/utility.hpp"
namespace devs::component {
	class RuleE
		: JuComponent
	{
	public:
		struct _Event {
			TimeType	schedule_time;	//发送时间
			std::string track_name;		//目标

			_Event(TimeType st=TIME_MAX, const std::string& _track_name="") {
				schedule_time = st;
				track_name = _track_name;
			}

			inline bool operator <(const _Event& other)const
			{
				return schedule_time < other.schedule_time;
			}

			inline bool operator >(const _Event& other)const
			{
				return schedule_time > other.schedule_time;
			}

		};
	public:
		RuleE(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid);
		FUNC_MakeShared(RuleE);

		// 通过 JuComponent 继承
		virtual void delta_int() override;
		virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
		virtual void output_func(IO_Bag & yb) override;
		virtual devs::TimeType ta() override;
	private:
		util::MinPriorityQueue<_Event> priority_event_queue;
	};
	FUNC_CreatSptr(RuleE);
}