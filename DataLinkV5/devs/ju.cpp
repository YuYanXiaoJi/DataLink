#include "ju.hpp"
#include"ju_component.hpp"
#include"component/RuleA.hpp"
std::shared_ptr<devs::Ju> devs::Ju::make_shared(devs::Digraph & _digraph, const std::string & _name, uint64_t _uid)
{
	return std::make_shared<devs::Ju>(_digraph, _name, _uid);
}

devs::Ju::Ju(Digraph & _digraph, const std::string & _name, uint64_t _uid)
	:AtomicAbstract(_digraph, _name, _uid)
	, port_self_recv(util::NextUid())
	, port_self_send_cmd(util::NextUid())
	, port_self_send_at(util::NextUid())
	, port_self_send_j3(util::NextUid())
	, port_self_send_j7(util::NextUid())
	, port_self_send_ts(util::NextUid())
	, port_private_recv(util::NextUid())
	, port_broadcast_send(util::NextUid())
	, port_broadcast_recv(util::NextUid())
{
	
	AddComponent("RuleA", component::CreatSptrRuleA(*this, digraph, "RuleA", util::NextUid()));
}


//
std::tuple<bool, bool, bool> devs::Ju::GetExist(const std::string & track_name)
{
	bool is_exist_r2 = dict_r2.exist(track_name);
	bool is_exist_at = dict_active_track.exist(track_name);
	bool is_exist_rt = dict_recv_track.exist(track_name);
	return { is_exist_at, is_exist_rt, is_exist_r2 };
}

void devs::Ju::AddComponent(const std::string & name, std::any sptr_component)
{
	//auto ptr = std::any_cast<std::shared_ptr<JuComponent>>(sptr_component);
	map_component[name] = sptr_component;
}



void devs::Ju::delta_int()
{
	buffer_list.pop_front();
}

void devs::Ju::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
	for (auto&iter : xb) {

		auto& blob = *iter.value;
		switch (blob[0])
		{
		case msg::Msg_ActiveTrack:
		{
			auto& msg = blob.get<msg::ActiveTrack>();
			auto track_name = util::TrackNumberHandler::GetName(msg.track_number);
			dict_active_track[track_name] = TrackInformation(msg, this->name);
			break;
		}
		case msg::Msg_JointMsg3I:
		{
			auto& msg = blob.get<msg::JointMsg3_0I>();
			if (msg.from_sut_name == this->name) {
				return; // 自己的发出的消息.无视
			}
			auto track_name = util::TrackNumberHandler::GetName(msg.track_number);
			dict_recv_track[track_name] = TrackInformation(msg);
			break;
		}
		case msg::Msg_JointMsg7I:
		{
			auto& msg = blob.get<msg::JointMsg7_0I>();
			if (msg.from_sut_name == this->name) {
				return; // 自己的发出的消息.无视
			}
			break;
		}
		default:
			break;
		}

		//最后再推入 buffer 
		buffer_list.push_back(iter);
	}
}

void devs::Ju::output_func(IO_Bag & yb)
{
	auto&y = buffer_list.front();
	auto& blob = *y.value;
	switch (blob[0])
	{
	case msg::Msg_ActiveTrack:
	{
		std::cout << name << "\t" << "Message::ActiveTrack" << std::endl;
		yb.insert(IO_Type{ port_self_send_at,y.value });
		break;
	}

	case msg::Msg_JointMsg3I:
	{
		std::cout << name << "\t" << "Message::JointMsg3I" << std::endl;
		yb.insert(IO_Type{ port_self_send_j3,y.value });
		break;
	}
	case msg::Msg_JointMsg7I:
	{
		std::cout << name << "\t" << "Message::JointMsg7I" << std::endl;
		yb.insert(IO_Type{ port_self_send_j7,y.value });
		break;
	}
	case msg::Msg_LocalMsg:
	{
		std::cout << name << "\t" << "Message::LocalMsg" << std::endl;
		yb.insert(IO_Type{ port_self_send_ts,y.value });
		break;
	}
	case msg::Msg_TimeSilce:
	{
		std::cout << name << "\t" << "Message::TimeSilce" << std::endl;
		yb.insert(IO_Type{ port_self_send_at,y.value });
		break;
	}
	default:
	{
		std::cout << name << "\t" << "Message::Unkown" << std::endl;
		break;
	}
	}
}

devs::TimeType devs::Ju::ta()
{
	return buffer_list.empty()*TIME_MAX;
}

