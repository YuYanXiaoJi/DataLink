#include "reporting_responsibility.hpp"
#include "../global_time.hpp"
devs::component::R2::R2(Ju & ju, Digraph & _digraph, const std::string & _name, PortType _uid)
	:JuComponent(ju, _digraph, _name, _uid)
{
}

void devs::component::R2::delta_int()
{
	local_cmd_list.pop_front();
}

void devs::component::R2::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
	for (auto&x : xb) {
		if (x.port == port_self_recv_cmd) {
			auto& cmd = x.value->get<msg::LocalCmd>();
			local_cmd_list.push_back(cmd);
		}
	}
}

void devs::component::R2::output_func(IO_Bag & yb)
{
	auto&cmd = local_cmd_list.front();
	if (cmd.cmd_id == msg::CMD_RM_R2 ) {
		parent.dict_r2.erase(cmd.track_name);
	}
	else if (cmd.cmd_id == msg::CMD_SET_R2) {
		if (parent.dict_r2.exist(cmd.track_name)==false) {
			parent.dict_r2[cmd.track_name] = global::global_msec;
			
			//立即广播出去,无视 TimeSlice 的限制
			yb.insert(IO_Type(
				port_self_send_to_transpond,
				util::CreateSptrBlob(
					parent.dict_active_track[cmd.track_name].get<msg::JointMsg3I>()
				)
			));

		}

	}
}

devs::TimeType devs::component::R2::ta()
{
	return local_cmd_list.empty()*TIME_MAX;
}
