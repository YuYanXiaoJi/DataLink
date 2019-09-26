## LinkData  For LUA API

### 常量,枚举与非成员函数说明

#### Enum Class

该类型目前(begin:20190926),是包括 常量与枚举类型,在C++中是在EnumWrapper 中进行包装.
在Lua中调用方式如下:

```c++
local x = Enum.$NAME //伪
local y = Enum.Msg_JointMsg2I
```

具体内容如下:

#####  消息的枚举类型:

Type: INT32

- Msg_JointMsg2I
- Msg_JointMsg3I
- Msg_JointMsg7I
- Msg_JointMsgBase
- Msg_LoaclCmd
- Msg_LocalTrack
- Msg_SubTimeSlice
- Msg_TimeSlice

#####  目标平台枚举类型:

Type: INT32

- Platform_AIR
- Platform_LAND
- Platform_MARITIME
- Platform_UNDEFINED

#####  LocalCmd 命令id 枚举类型: 

Type: INT32

- CMD_SET_R2
- CMD_RM_R2
- CMD_BROADCAST_J3
- CMD_BROADCAST_J7

#####  常量:

- TIME_MAX 		Type: INT64



#### Function Class

在C++中是在FuncWrapper 中进行包装.


函数列表:

- Now()

  return a int64_t type number . the number is current simulation system time.

  ```c++
  current_time = Func.Now()
  ```

- GetMsgName( msg_type )

  input:  	msg_type 是消息报文的类型.

  return 该消息类型的名字

  ```c++
  name_str = Func.GetMsgName( Enum.Msg_JointMsg2I) 
  -- name_str="JointMsg2I"
  ```

- GetMinBroadcastInterval( track_plotform )

  input:	track_plotform  是航迹所在的平台.

  return:  该平台最小的再次广播的时间间隔.

  ```c++
  interval = Func.GetMinBroadcastInterval( Enum.Platform_AIR) 
  -- interval=12'000   
  ```

- GetWaitInterval(track_plotform)

  input:	track_plotform  是航迹所在的平台.

  return:  该平台的消息超时时间
  
  

### 消息报文类型

#### TimeSlice

时间片类型.由HUB以轮转的方式发出.

- msg_type(const) = Msg_TimeSlice
- begin_time(int64_t)
- end_time(int64_t) 

####  SubTimeSlice

为了体现能在时间片内触发的事件.我们创造了SubTimeSlice这个类型,是将TimeSlice继续拆分为更为细小的时间片

- msg_type(const) = Msg_SubTimeSlice
- begin_time(int64_t)   来至于对应的 TimeSlice 的 begin_time
- end_time(int64_t)      来至于对应的 TimeSlice 的 end_time
- current_time(int64_t)

#### JointMsg2I

- msg_type(const) = Msg_JointMsg2I
- create_time (int64_t)
- uNPSI
- *GetTrackName()*

  是用于获得 TrackName.

  ```c++
  track_name= j2i:GetTrackName()
  ```


#### JointMsg3I

- msg_type(const) = Msg_JointMsg3I
- create_time (int64_t)
- track_platform
- track_quality

- *GetTrackName()*

  是用于获得 TrackName.

  ```c++
  track_name= j3i:GetTrackName()
  ```

#### JointMsg7I

- msg_type(const) = Msg_JointMsg7I
- create_time (int64_t)
- action
- *GetTrackName()*
  是用于获得 TrackName.
  
  ```c++
  track_name= j7i:GetTrackName()
  ```
  
#### LocalTrack

- msg_type(const) = Msg_LocalTrack
- create_time (int64_t)
- track_platform
- track_quality
- *GetTrackName()*
  是用于获得 TrackName.
  
  ```c++
  track_name= j7i:GetTrackName()
  ```

#### LocalCmd

- msg_type(const) = Msg_LocalCmd
- cmd_id
- GetTrackName() <span style="color: red"> 未实现</span>
	由于 LuaBridge 不支持 添加 char*类型的 成员变量. 所以通过函数的方式将char* 赋值到 string 返回.



### JU 

#### TrackInformation

- track_number

- track_platform

- track_quality

- uSTN

- create_time

- GetJ3(is_create_new)

  ```c++
  j3i = track_info.GetJ3(true)
  ```

  

#### JuScriptComponent

