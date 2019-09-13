--元类
Vector = { m_size = 0 ,m_ary = {} }

--派生类的方法 new
function Vector:new ( )
o = {}
setmetatable(o , self)
self.__index = self
self.m_size = 0;
self.m_ary = {};
return o
end

-- 派生类的方法 printArea
function Vector:Size()
	return self.m_size;
end

function Vector:PushBack(value)
self.m_ary[self.m_size] = value;
self.m_size = self.m_size + 1;
end


function Vector:At(index)
if index<0 and index>=self.m_size then
error("index is bad!")
end
return self.m_ary[index];
end

function Vector:Insert( index ,value )
if index<0 and index>self.m_size then
	error("index is bad!")
end
error("the function isn't building")
end


function Vector:Empty()
return self.m_size == 0;
end