
buffer_list =List:new()

function Init()
	this:BindOdd();
	this:BindSend();
end


function Input(recvPort,value)
	if(recvPort=="Odd") then
		buffer_list:PushBack(value);
		--print("Odd Input:"..value.src)
	end
end

function Internal()
	buffer_list:PopFront();
end

function Output()
	i = buffer_list:Front();
	--val = val*3+1
	i.val=i.val*3+1;
	i.inc=i.inc+1;
	blob=Blob(i)
	--this:SendFunc("Send",i);
	--this:SendFuncBlob("Send",blob)
	this:SendFuncLuaRef("Send",i)
	--this:SendFuncBlob("Send",i)
end

function Ta( )
	if(buffer_list:Empty()) then
		return Const.kTimeMax; -- TIME MAX
	else
		return 0;
	end
end

