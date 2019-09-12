-- 元类
List = {m_front = 0, m_size = 0, m_back = -1 ,m_ary={}}

-- 派生类的方法 new
function List:new ()
  o = {}
  setmetatable(o, self)
  self.__index = self
  self.m_front	=  0;
  self.m_back	= -1;
  self.m_size	=  0;
  self.m_ary	= {};
  return o
end

-- 派生类的方法 printArea
function List:Size ()
  print("List size",self.m_size)
end

function List:PushFront(value)
  self.m_front = self.m_front-1;
  self.m_ary[self.m_front]=value;
  self.m_size=self.m_size+1;
end

function List:PushBack(value)
  self.m_back = self.m_back-1;
  self.m_ary[self.m_back]=value;
  self.m_size=self.m_size+1;
end

function List:PopFront()
	if self.m_size == 0 then
		error("List is empty!")
	end
	self.m_ary[self.m_front]=nil;
	self.m_front=self.m_front+1;
	self.m_size=self.m_size-1;
end

function List:PopBack()
	if self.m_size == 0 then
		error("List is empty!")
	end
	self.m_ary[self.m_back]=nil;
	self.m_back=self.m_back-1;
	self.m_size=self.m_size-1;
end

function List:Front()
	if self.m_size == 0 then
		error("List is empty!")
	end
	return self.m_ary[self.m_front];
end

function List:Back()
	if self.m_size == 0 then
		error("List is empty!")
	end
	return self.m_ary[self.m_back];
end

function List:Empty()
	return self.m_size == 0 ;	
end