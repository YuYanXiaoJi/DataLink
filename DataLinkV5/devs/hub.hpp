#pragma once
#include"atomic.hpp"
#include"typedef.hpp"
#include"message/message.hpp"
#include"../utility/utility.hpp"
#include"ju.hpp"
namespace devs {
	
	class Hub
		:public AtomicAbstract
	{
	public:
		struct ScheduleBufferNode;
	public:
		Hub(Digraph& _digraph, const std::string&_name, uint64_t _uid);

		
		template<class Ty>void push_buffer(TimeType schedule_time, PortType send_port, const Ty& msg) {
			priority_blob_queue.push(
				ScheduleBufferNode(
					schedule_time, IO_Type(send_port,util::CreateSptrBlob(msg))
				)
			);
		}
		template<> inline void push_buffer(TimeType schedule_time, PortType send_port, const util::SptrBlob& msg);

		void add_ju(SptrJu sptr_ju);

	public:
		// 通过 AtomicAbstract 继承
		virtual void delta_int() override;
		virtual void delta_ext(devs::TimeType e, const IO_Bag & xb) override;
		virtual void output_func(IO_Bag & yb) override;
		virtual devs::TimeType ta() override;

	public:
		//广播端口(双向)
		const	PortType	port_broadcast_send;	//广播发送端口	
		const	PortType	port_broadcast_recv;	//广播转发端口
		const	PortType	port_abandon = -1;		//用于抛弃一些无效消息

		//私有端口(单向)
		std::map<uint64_t, PortType> map_private_recv_port; 	//map<uid,private_send_port> 
		std::vector<SptrJu>			 ary_ju;					//Ju 容器

	protected:
		util::MinPriorityQueue<ScheduleBufferNode> priority_blob_queue;

		TimeType	time_division_interval	= 100 ; //TDMA  时间片大小  (ms)
		int			tdma_idx				= 0;	//在 _PushNextTimeSlice 函数中自动更新

	private:
		void _PushNextTimeSlice();	//将生成的下一的 时间片 推入 priority_blob_queue
	};

}



struct devs::Hub::ScheduleBufferNode
{
	TimeType	schedule_time;//发送时间
	IO_Type		io_buffer;

	ScheduleBufferNode(TimeType _schedule_time, IO_Type _io_buffer) {
		schedule_time = _schedule_time;
		io_buffer = _io_buffer;
	}

	ScheduleBufferNode(TimeType _schedule_time, PortType _port, util::SptrBlob _sptr_blob) {
		schedule_time = _schedule_time;
		io_buffer = IO_Type(_port, _sptr_blob);
	}

	bool operator < (const ScheduleBufferNode& other)const {
		return schedule_time < other.schedule_time;
	}

	bool operator > (const ScheduleBufferNode& other)const {
		return schedule_time > other.schedule_time;
	}
};

template<>
inline void devs::Hub::push_buffer(TimeType schedule_time, PortType send_port, const util::SptrBlob & msg)
{
	priority_blob_queue.push(
		ScheduleBufferNode(
			schedule_time, IO_Type(send_port, msg)
		)
	);
}