#include "RuleA.hpp"
using namespace util;
devs::component::RuleA::RuleA(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
	:JuComponent(ju, _digraph,_name,_uid)
{

}

void devs::component::RuleA::delta_int()
{
	buffer_list.pop_front();
}

void devs::component::RuleA::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
	for (auto&x : xb) {
		if(x.port==port_self_recv_at)
			buffer_list.push_back(x);
	}
}

void devs::component::RuleA::output_func(IO_Bag & yb)
{
	auto& x = buffer_list.front();
	auto& blob = *x.value;
	auto& msg = blob.get<msg::ActiveTrack>();
	auto track_name = TrackNumberHandler::GetName(msg.track_number);

	auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);
	if (is_exist_r2 == false && is_exist_rt == false && is_exist_at == true)
	{
		IO_Type y;
		y.port = port_self_send;
		y.value = CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2, track_name.c_str()));
		yb.insert(y);
	}
}

devs::TimeType devs::component::RuleA::ta()
{
	return buffer_list.empty()*TIME_MAX;
}
