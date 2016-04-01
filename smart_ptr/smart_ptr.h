#pragma once
#include <map>

// 模仿shared_ptr实现一个智能指针
template <typename T>
class smart_ptr
{
public:
	smart_ptr();
	explicit smart_ptr(T*);
	~smart_ptr();

	T* get();

private:
	unsigned m_use_count = 0;
	T* m_pobject = nullptr;
};

template <typename T>
smart_ptr::smart_ptr()
{
}


template <typename T>
smart_ptr::smart_ptr(T*p)
{
	m_pobject = p;
	m_use_count = 1;
}


template <typename T>
smart_ptr::~smart_ptr()
{
	if (m_use_count > 0)
	{
		m_use_count--;
	}

	if (m_use_count == 0 && m_pobject)
	{
		delete m_pobject;
		m_pobject = nullptr;
	}
}


template <typename T>
T* smart_ptr::get()
{
	return m_pobject;
}
