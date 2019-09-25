
function Init()
	--this:BindInTS();	-- °ó¶¨ TimeSlice
	--print("Bind TS")

	---

	this:BindInLT();
    this:BindInCMD();
end

function Input(msg)

	print(Func.Now().."\tPrintComponent R:"..Func.GetMsgName(msg.msg_type).."\t..lua")
end

function Internal()

end

function Output()

end

function Ta( )
	return Enum.TIME_MAX
end