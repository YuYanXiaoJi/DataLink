#include "hub.hpp"
#include "global_time.hpp"
devs::Hub::Hub(Digraph & _digraph, const std::string & _name, uint64_t _uid) 
	:AtomicAbstract(_digraph, _name, _uid)
	, port_broadcast_send(util::NextUid())
	, port_broadcast_recv(util::NextUid())
{
	//push_buffer(0, port_abandon, next_tdma_frame());
}

void devs::Hub::add_ju(SptrJu sptr_ju)
{
	ary_ju.push_back(sptr_ju);

	//�󶨹㲥�˿�
	digraph.couple(this, this->port_broadcast_send, sptr_ju.get(), sptr_ju->port_broadcast_recv);	// HUB	-->	JU
	digraph.couple(sptr_ju.get(), sptr_ju->port_broadcast_send, this, this->port_broadcast_recv);	// JU	-->	HUB

	//��˽�ж˿�
	map_private_recv_port[sptr_ju->uid] = util::NextUid();	//���� HUB ��JU �󶨵Ķ˿�
	digraph.couple(this, map_private_recv_port[sptr_ju->uid], sptr_ju.get(), sptr_ju->port_private_recv);	//	HUB(private)->JU(private)
	

}

void devs::Hub::_PushNextTimeSlice()
{
	PortType port;
	if (ary_ju.empty())
		port = port_abandon;
	else {
		int idx = this->tdma_idx%ary_ju.size();
		port = map_private_recv_port[ary_ju[idx]->uid];
	}
	auto msg = msg::TimeSlice(tdma_idx*time_division_interval, (tdma_idx + 1)*time_division_interval);
	tdma_idx++;
	push_buffer(msg.begin_time, port, msg);
}

void devs::Hub::delta_int()
{
	priority_blob_queue.pop();
}

void devs::Hub::delta_ext(devs::TimeType e, const IO_Bag & xb)
{
	for (auto&iter : xb) {
		if (iter.port == this->port_broadcast_recv)
			push_buffer(global::global_msec, this->port_broadcast_send, iter.value);
		else
			assert(false/*ֻ���յ� ����ȫ��ת������Ϣ*/);
	}
}

void devs::Hub::output_func(IO_Bag & yb)
{
	auto&y = priority_blob_queue.top();
	yb.insert(y.io_buffer);

	if (y.io_buffer.value->at(0) == msg::Msg_TimeSilce)	
	{
		//�ж��Ƿ��͵���ʱ��Ƭ,�����,�ͽ��µ�ʱ��Ƭ���뷢�Ͷ�����
		this->_PushNextTimeSlice();
	}
}

devs::TimeType devs::Hub::ta()
{
	if (priority_blob_queue.empty())
		return TIME_MAX;
	return  global::distance(priority_blob_queue.top().schedule_time);
}


