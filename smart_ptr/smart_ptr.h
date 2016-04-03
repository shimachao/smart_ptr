#pragma once

// 模仿shared_ptr实现一个智能指针
template <typename T>
class smart_ptr
{
public:
	smart_ptr();
	explicit smart_ptr(T*);
	smart_ptr(const smart_ptr&);
	smart_ptr& operator=(const smart_ptr&);
	T& operator*() const;
	T* operator->() const;

	~smart_ptr();
	// 向bool的类型转换
	explicit operator bool() const;

	bool unique();

	T* get() const;

private:
	unsigned* m_use_count = nullptr;
	T* m_pobject = nullptr;
};

template <typename T>
smart_ptr::smart_ptr()
	:m_pobject(nullptr), m_use_count(new unsigned(1))
{
}


template <typename T>
smart_ptr::smart_ptr(T*p)
	:m_pobject(p), m_use_count(new unsigned(1))
{
}


template <typename T>
smart_ptr::smart_ptr(const smart_ptr& rhs)
	:m_pobject(rhs.m_pobject), m_use_count(rhs.m_use_count)
{
	*m_use_count++;
}


template <typename T>
smart_ptr& smart_ptr::operator =(const smart_ptr &rhs)
{
	// 递增右侧运算对象的引用计数
	++*rhs.m_use_count;
	// 递减本对象的引用计数
	if (--*m_use_count == 0)
	{
		// 如果管理的对象没有其他用户了，则释放对象分配的成员
		delete m_pobject;
		delete m_use_count;
	}

	m_use_count = rhs.m_use_count;
	m_pobject = rhs.m_pobject;

	return *this; // 返回本对象
}


template <typename T>
T& smart_ptr::operator*() const
{
	return m_pobject;
}


template <typename T>
T* smart_ptr::operator->() const
{
	return &this->operator*();
}


template <typename T>
smart_ptr::~smart_ptr()
{
	if (--(*m_use_count) == 0)
	{
		delete m_pobject;
		m_pobject = nullptr;
	}
}


template <typename T>
bool smart_ptr::unique()
{
	return *m_use_count == 1;
}


template <typename T>
T* smart_ptr::get() const
{
	return m_pobject;
}


template <typename T>
smart_ptr::operator bool() const
{
	return m_pobject != nullptr;
}
