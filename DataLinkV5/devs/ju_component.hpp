#pragma once
#include"atomic.hpp"
#include"ju.hpp"
#include"typedef.hpp"
#include"../utility/utility.hpp"

namespace devs {
	class JuComponent 
		:public AtomicAbstract
	{
	protected:
		JuComponent(Ju& ju, Digraph& _digraph, const std::string&_name, PortType _uid)
			:AtomicAbstract(_digraph, _name, _uid)
			, parent(ju)
			, port_self_send(util::NextUid())
			, port_self_recv_cmd(util::NextUid())
			, port_self_recv_at(util::NextUid())
			, port_self_recv_j3(util::NextUid())
			, port_self_recv_j7(util::NextUid())
			, port_self_recv_ts(util::NextUid())
		{
			digraph.couple(this, this->port_self_send, &ju, ju.port_self_recv); //发送给Ju

			digraph.couple(&ju, ju.port_self_send_cmd, this, this->port_self_recv_cmd);
			digraph.couple(&ju, ju.port_self_send_at, this, this->port_self_recv_at);
			digraph.couple(&ju, ju.port_self_send_j3, this, this->port_self_recv_j3);
			digraph.couple(&ju, ju.port_self_send_j7, this, this->port_self_recv_j7);
			digraph.couple(&ju, ju.port_self_send_ts, this, this->port_self_recv_ts);
		}
	public:
		// 通过 Atomic 继承
		virtual void delta_int() = 0;
		virtual void delta_ext(devs::TimeType e, const IO_Bag& xb) = 0;
		virtual void output_func(IO_Bag& yb) = 0;
		virtual devs::TimeType ta() = 0;

	public:
		Ju & parent;

		//与Component 传输使用
		const PortType		port_self_send;			//内部使用的接收端口

		const PortType		port_self_recv_cmd;		//CMD 转发
		const PortType		port_self_recv_at;		//Active Track 消息转发
		const PortType		port_self_recv_j3;		//J_3 消息转发
		const PortType		port_self_recv_j7;		//J_7 消息转发
		const PortType		port_self_recv_ts;		//TimeSlice 消息转发

	};
}