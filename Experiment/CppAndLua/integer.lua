


function IntPrint( obj )
	print(obj.val)
	print(obj.inc)
	print(obj.src)
end

IntPrint(i);

local j = Msg.Integer(100)
IntPrint(j);



ary={1,2,3,4,5,6};

--[[
while(obj.val ~= 1 )
do
	if(obj.val%2==1)
	then 
		obj.val = obj.val*3+1
	else
		obj.val = obj.val/2
	end
	obj.inc = obj.inc+1
end
--]]

