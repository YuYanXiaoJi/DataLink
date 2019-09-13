
buffer_list =List:new()

function Init()
	this:BindOdd();
	this:BindEven();
	this:BindPrint();
	this:BindSend();
end


function Input(recvPort,value)
	if(recvPort=="Odd") then
		buffer_list:PushBack(value);
		print("Input:"..value.src)
	end
end

function Internal()
	buffer_list:PopFront();
end

function Output()
	i = buffer_list:Front();
	i.val=1;
	this:SendFunc("Send",i);
end

function Ta( )
	if(buffer_list:Empty()) then
		return Const.kTimeMax; -- TIME MAX
	else
		return 0;
	end
end

