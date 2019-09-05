#pragma once
namespace devs {
	enum PortType
	{
		port_abandon = -1,		//用于抛弃一些无效消息

		port_broadcast_send,	//广播发送端口	
		port_broadcast_recv,	//广播转发端口
		port_private_recv,		//与广播1v1接收端口


		port_self_recv,			//内部使用的接收端口
		port_self_recv_to_transpond,//接收 component的消息,在通过port_broadcast_send转发出去
		port_self_send_cmd,		//CMD 转发
		port_self_send_at,		//Active Track 消息转发
		port_self_send_j3,		//J_3 消息转发
		port_self_send_j7,		//J_7 消息转发
		port_self_send_j2,		//J_2 消息转发
		port_self_send_ts,		//TimeSlice 消息转发

		

	};


}