

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


