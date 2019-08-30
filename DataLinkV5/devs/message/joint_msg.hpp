#pragma once
#include"msg_type.hpp"
#include"track_platform_type.hpp"
#include"../typedef.hpp"
#include<cstring>
#include<cstdint>
namespace devs::message {

	//���ַ�������Ŀռ�
	const std::size_t STR_MAX_LENGTH = 32; 

	struct JointMsgBase
	{

		uint8_t msg_type;
		char label[STR_MAX_LENGTH];
		char sub_label[STR_MAX_LENGTH];

		JointMsgBase(const char* in_label, const char* in_sub_label, uint8_t _msg_type =  Msg_JointMsgBase) {
			strcpy(label, in_label);
			strcpy(sub_label, in_sub_label);
			msg_type = _msg_type;
		}
	};

	struct JointMsg3I :
		public JointMsgBase
	{

		// ����Ŀ��
		char  track_number[STR_MAX_LENGTH];

		char  from_sut_name[STR_MAX_LENGTH];

		TrackPlatform	track_platform;

		// �ź����� Խ��Խ��
		int32_t track_quality;
		// STNָ��
		int32_t _uSTN;
		// ���ĵĴ���ʱ��
		TimeType	time_msec;

		JointMsg3I(
			const char* _track_number, const char* _from_sut_name,
			TrackPlatform _track_platform, int32_t _track_quality, TimeType _time_msec, int32_t uSTN)
			:JointMsgBase("J3", "0I", Msg_JointMsg3I)
		{
			strcpy(track_number, _track_number);
			strcpy(from_sut_name, _from_sut_name);
			_uSTN = uSTN;
			track_platform = _track_platform;
			track_quality = _track_quality;
			time_msec = _time_msec;
		}

		inline bool operator < (const JointMsg3I& obj) const {
			return track_number < obj.track_number;
		}
	};

	struct JointMsg7I :
		public JointMsgBase
	{

		// ����Ŀ��
		char  track_number[STR_MAX_LENGTH];

		char  from_sut_name[STR_MAX_LENGTH];
		uint8_t action;	//ACT

		// ���ĵĴ���ʱ��
		TimeType	time_msec;

		JointMsg7I(
			const char* _track_number, const char* _from_sut_name, uint8_t _action,
			TimeType _time_msec)
			:JointMsgBase("J7", "0I", Msg_JointMsg7I)
		{
			strcpy(track_number, _track_number);
			strcpy(from_sut_name, _from_sut_name);
			action = _action;
			time_msec = _time_msec;
		}

		inline bool operator < (const JointMsg7I& obj) const {
			return track_number < obj.track_number;
		}
	};

	struct JointMsg2I :
		public JointMsgBase
	{

		// ����Ŀ��
		char  track_number[STR_MAX_LENGTH];

		char  from_sut_name[STR_MAX_LENGTH];
		uint8_t _uNPSI;		// ������뵥Ԫ״̬��ʶ��

		// ���ĵĴ���ʱ��
		TimeType	time_msec;

		JointMsg2I(
			const char* _track_number, const char* _from_sut_name, uint8_t uNPSI,
			TimeType _time_msec)
			:JointMsgBase("J2", "0I", Msg_JointMsg2I)
		{
			strcpy(track_number, _track_number);
			strcpy(from_sut_name, _from_sut_name);
			_uNPSI = uNPSI;
			time_msec = _time_msec;
		}

		inline bool operator < (const JointMsg2I& obj) const {
			return track_number < obj.track_number;
		}
	};

}
