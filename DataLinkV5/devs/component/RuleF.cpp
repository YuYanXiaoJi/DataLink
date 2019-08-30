#include "RuleF.h"
devs::component::RuleF::RuleF(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid)
	:JuComponent(ju, _digraph, _name, _uid)
{

}

void devs::component::RuleF::delta_int()
{
	j7_sptr_blob_list.pop_front();
}

void devs::component::RuleF::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
	for (auto&x : xb) {
		if (x.port == this->port_self_recv_j7) {
			j7_sptr_blob_list.push_back(x.value);
		}
	}
}

void devs::component::RuleF::output_func(IO_Bag & yb)
{
	auto& j7 = j7_sptr_blob_list.front()->get<msg::JointMsg7I>();
	// F规则只处理ACT=0的情况
	if (j7.action != 0) return;
	auto track_name = util::TrackNumberHandler::GetName(j7.track_number);
	auto[is_exist_at, is_exist_rt, is_exist_r2] = parent.GetExist(track_name);

	if (is_exist_at  && is_exist_r2 == false) {
			yb.insert(IO_Type(port_self_send,
							  util::CreateSptrBlob(msg::LocalCmd(msg::CMD_SET_R2, track_name.c_str()))
			));
	}

}

devs::TimeType devs::component::RuleF::ta()
{
	return j7_sptr_blob_list.empty()*TIME_MAX;
}

