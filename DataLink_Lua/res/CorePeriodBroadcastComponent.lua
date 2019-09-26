is_local_ts=false

function Init()
    this:BindInSTS()
end

function Input(msg)
    if(msg.msg_type==Enum.Msg_SubTimeSlice) then
        --print(Func.Now().."\tCPBC R:"..Func.GetMsgName(msg.msg_type).."\t..lua")
        is_local_ts=true
    end
end


function Internal()
    is_local_ts=false
end

function Ta()
    if(is_local_ts==false) then
        return Enum.TIME_MAX
    else
        return 0
    end
end

function Output()
    local current_time = Func.Now() -- get current time
    local ts  = this:GetTS()
    for track_name , last_broadcast_time in pairs(this:ViewR2Dict()) do -- key: string  ; value :number
        local ltn=this:GetLocalTrackInfo(track_name)
        local broadcast_interval_min= Func.GetMinBroadcastInterval(ltn.track_platform)
        local pre_next_broadcast_time_min = broadcast_interval_min + last_broadcast_time

        if( (pre_next_broadcast_time_min<= current_time) or (last_broadcast_time==0) ) then
            this:SetR2(track_name,current_time)
            local j3_msg = ltn:GetJ3(true)
            --print("debug",type(j3_msg))
            this:SecureBroadcast(j3_msg)
        end
    end


end