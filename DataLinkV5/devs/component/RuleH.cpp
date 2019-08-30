#include "RuleH.h"

devs::component::RuleH::RuleH(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid)
	:JuComponent(ju, _digraph, _name, _uid)
{

}

void devs::component::RuleH::delta_int()
{
	j2_sptr_blob_list.pop_front();
}

void devs::component::RuleH::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
	for (auto&x : xb) {
		if (x.port == this->port_self_recv_j2) {
			j2_sptr_blob_list.push_back(x.value);
		}
	}
}

void devs::component::RuleH::output_func(IO_Bag & yb)
{
	auto& j2 = j2_sptr_blob_list.front()->get<msg::JointMsg2I>();
	auto track_name = util::TrackNumberHandler::GetName(j2.track_number);
	auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);
	if (is_exist_at && is_exist_r2 == false) {
		// HπÊ‘Ú
		if (2 == j2._uNPSI || 3 == j2._uNPSI || 6 == j2._uNPSI) {
			yb.insert(IO_Type(port_self_send,
							  util::CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2, track_name.c_str()))
			));
		}
	}
}

devs::TimeType devs::component::RuleH::ta()
{
	return j2_sptr_blob_list.empty()*TIME_MAX;
}

