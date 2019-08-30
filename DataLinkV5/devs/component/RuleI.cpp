#include "RuleI.h"
devs::component::RuleI::RuleI(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid)
	:JuComponent(ju, _digraph, _name, _uid)
{

}

void devs::component::RuleI::delta_int()
{
	j3_sptr_blob_list.pop_front();
}

void devs::component::RuleI::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
	for (auto&x : xb) {
		if (x.port == this->port_self_recv_j3) {
			j3_sptr_blob_list.push_back(x.value);
		}
	}
}

void devs::component::RuleI::output_func(IO_Bag & yb)
{
	auto& j3 = j3_sptr_blob_list.front()->get<msg::JointMsg3I>();
	auto track_name = util::TrackNumberHandler::GetName(j3.track_number);
	auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);
	if (is_exist_at && is_exist_rt && is_exist_r2) {
		if (parent.dict_active_track[track_name].track_quality< j3.track_quality||(parent.dict_active_track[track_name].track_quality == j3.track_quality&&parent._uSTN<j3._uSTN)) {
			yb.insert(IO_Type(port_self_send,
							  util::CreateSptrBlob(msg::LocalCmd(msg::CMD_RM_R2, track_name.c_str()))
			));
		}
	}
}

devs::TimeType devs::component::RuleI::ta()
{
	return j3_sptr_blob_list.empty()*TIME_MAX;
}

