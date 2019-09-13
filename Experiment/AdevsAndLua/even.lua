
buffer_list =List:new()

function Init()
	this:BindEven();
	this:BindSend();
end


function Input(recvPort,value)
	if(recvPort=="Even") then
		buffer_list:PushBack(value);
		--print("Even Input:"..value.src)
	end
end

function Internal()
	buffer_list:PopFront();
end

function Output()
	i = buffer_list:Front();
	--val = val*3+1
	i.val=i.val/2;
	i.inc=i.inc+1;
	this:SendFunc("Send",i);
end

function Ta( )
	if(buffer_list:Empty()) then
		return Const.kTimeMax; -- TIME MAX
	else
		return 0;
	end
end

