#pragma once
#include <map>

// 自己模仿shared_ptr实现一个智能指针
template <typename T>
class smart_ptr
{
public:
	smart_ptr();
	~smart_ptr();

private:
	unsigned m_use_count = 0;
};

template <typename T>
smart_ptr::smart_ptr()
{
}

template <typename T>
smart_ptr::~smart_ptr()
{
}