
function Init()
	this:BindPrint();
end


function Input(recvPort,value)
	if(recvPort=="Print") then
		print("ret:"..value.src.."\tinc:"..value.inc.."\ttype"..value.type.."\tT"..Integer.t)
	end
end

function Internal()

end

function Output()

end

function Ta( )
	return Const.kTimeMax; -- TIME MAX
end

