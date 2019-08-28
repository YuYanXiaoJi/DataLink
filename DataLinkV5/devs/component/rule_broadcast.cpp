#include "rule_broadcast.hpp"
#include"../handler.hpp"
#include<algorithm>
devs::component::RuleBroadcast::RuleBroadcast(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
	:JuComponent(ju,_digraph,_name,_uid)
{
}

void devs::component::RuleBroadcast::delta_int()
{
	is_recv_ts = false;
}

void devs::component::RuleBroadcast::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
	for (auto&x : xb) {
		if (x.port == port_self_recv_ts) {
			is_recv_ts = true;
		}
	}
}

void devs::component::RuleBroadcast::output_func(IO_Bag & yb)
{
	auto& ts = parent.time_silce;
	for (auto[track_name, last_broadcast_time]/*[key,value] c++17*/ : parent.dict_r2) {
		auto& attn = parent.dict_active_track[track_name];
		auto broadcast_interval = GetMinBroadcastInterval(attn.track_platform);
		auto next_broadcast_time_min = broadcast_interval + last_broadcast_time;

		//只要 next_broadcast_time_min 小于 ts.end 就可以发.
		//在根据 ts.begin 确定具体在哪个时间 发 
		if (next_broadcast_time_min < ts.end_time) {
			auto next_broadcast_time = std::max(next_broadcast_time_min, ts.begin_time);
			parent.dict_r2[track_name] = next_broadcast_time;	//更新时间

			//广播 J3i
			yb.insert(IO_Type(
				port_self_send_to_transpond,
				util::CreateSptrBlob(
					parent.dict_active_track[track_name].get<msg::JointMsg3I>()
				)
			));
		}
	}
	//std::cout << "time_silce:" << parent.time_silce.begin_time << "\t" << parent.time_silce.end_time << std::endl;
}

devs::TimeType devs::component::RuleBroadcast::ta()
{
	return (is_recv_ts == false)*TIME_MAX;
}
