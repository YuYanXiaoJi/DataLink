#pragma once
namespace devs {
	enum PortType
	{
		port_abandon = -1,		//��������һЩ��Ч��Ϣ

		port_broadcast_send,	//�㲥���Ͷ˿�	
		port_broadcast_recv,	//�㲥ת���˿�
		port_private_recv,		//��㲥1v1���ն˿�


		port_self_recv,			//�ڲ�ʹ�õĽ��ն˿�
		port_self_recv_to_transpond,//���� component����Ϣ,��ͨ��port_broadcast_sendת����ȥ
		port_self_send_cmd,		//CMD ת��
		port_self_send_at,		//Active Track ��Ϣת��
		port_self_send_j3,		//J_3 ��Ϣת��
		port_self_send_j7,		//J_7 ��Ϣת��
		port_self_send_j2,		//J_2 ��Ϣת��
		port_self_send_ts,		//TimeSlice ��Ϣת��

		

	};


}