#include "RuleE.hpp"
#include"../handler.hpp"
#include "../global_time.hpp"
#include "../../utility/utility.hpp"
devs::component::RuleE::RuleE(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
	:JuComponent(ju, _digraph, _name, _uid)
{
}

void devs::component::RuleE::delta_int()
{
	priority_event_queue.pop();
}

devs::TimeType devs::component::RuleE::ta()
{
	if (priority_event_queue.empty())
		return TIME_MAX;
	return global::distance(priority_event_queue.top().schedule_time);
}


void devs::component::RuleE::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
	for (auto&x : xb) 
	{
		if (x.port == this->port_self_recv_at) {
			auto&msg = x.value->get<msg::ActiveTrack>();
			auto track_number = util::TrackNumberHandler::GetName(msg.track_number);
			
			//判断队列中是否存在
			auto iter = priority_event_queue.find(
				[track_number](const _Event&e)->bool {return e.track_name == track_number;});
			if (iter == priority_event_queue.end())
			{	//不存在
				auto wait_time = GetMinBroadcastInterval(msg.track_platform);
				priority_event_queue.push(_Event(global::global_msec, track_number));
			}
		}

		if (x.port == this->port_self_recv_j3) {
			auto&msg = x.value->get<msg::JointMsg3I>();
			auto track_number = util::TrackNumberHandler::GetName(msg.track_number);

			//判断队列中是否存在
			auto iter = priority_event_queue.find(
				[track_number](const _Event&e)->bool {return e.track_name == track_number; });
			if (iter != priority_event_queue.end())
			{	//存在
				priority_event_queue.remove(iter);
			}
		}

	}
}


void devs::component::RuleE::output_func(IO_Bag & yb)
{
	auto e = priority_event_queue.top();
	
	yb.insert(IO_Type(port_self_recv_cmd,
		util::CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2, e.track_name.c_str()))
	));
	
}

