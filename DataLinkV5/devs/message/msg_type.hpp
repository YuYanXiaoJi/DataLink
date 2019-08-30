#pragma once
namespace devs::message {
	enum MsgType
	{
		Msg_JointMsgBase,
		Msg_JointMsg3I, 
		Msg_JointMsg7I,
		Msg_JointMsg2I,
		//////////////////////
		Msg_ActiveTrack,
		Msg_MissingTrack,
		Msg_TimeSilce,
		//////////////////////
		Msg_LocalMsg,
		//////////////////////
		Msg_VerifyMsg,
		Msg_VerifyCalc,
	};
}