buffer = List:new();

function Init()
    this:BindInBroadcastBuffer()
end

function Input(sig,msg)
    --print(sig)
    if(sig==Enum.SigI_BB) then
        buffer:PushBack(msg)
    end
end


function Internal()
    
end

function Ta()
    local current_time = Func.Now() -- get current time
    local ts  = this:GetTS()

    if( (ts.begin_time <= current_time) and (current_time <ts.end_time )  and ( buffer:Empty()==false )  ) then
        return 0
    else
        return Enum.TIME_MAX
    end

end

function Output()

    while( buffer:Empty()==false ) do
        local msg = buffer:Front()
        buffer:PopFront()
        print(Func.Now(),"CoreBroadcastComponent S:",Func.GetMsgName(msg:GetMsgType()))
        this:ImmediateBroadcast(msg)
        
    end

end