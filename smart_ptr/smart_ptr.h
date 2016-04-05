#pragma once

#include <functional>

// 模仿shared_ptr实现一个智能指针
template <typename T>
class smart_ptr
{
public:
	smart_ptr();
	explicit smart_ptr(T*);
	smart_ptr(const smart_ptr&);
	smart_ptr(T*, std::function<void(T*)>);
	smart_ptr& operator=(const smart_ptr&);
	T& operator*() const;
	T* operator->() const;

	~smart_ptr();
	// 向bool的类型转换
	explicit operator bool() const;

	bool unique();
	void reset();
	void reset(T* p);

	T* get() const;

private:
	unsigned* m_use_count = nullptr;
	T* m_pobject = nullptr;
	std::function<void(T*)> m_del = nullptr;
};

template <typename T>
smart_ptr<T>::smart_ptr()
	:m_pobject(nullptr), m_use_count(new unsigned(1))
{
}


template <typename T>
smart_ptr<T>::smart_ptr(T *p)
	:m_pobject(p), m_use_count(new unsigned(1))
{
}


template <typename T>
smart_ptr<T>::smart_ptr(T *p, std::function<void(T*)> del)
	:m_pobject(p), m_use_count(new unsigned(1)), m_del(del)
{
}


template <typename T>
smart_ptr<T>::smart_ptr(const smart_ptr& rhs)
	:m_pobject(rhs.m_pobject), m_use_count(rhs.m_use_count)
{
	*m_use_count++;
}


template <typename T>
smart_ptr<T>& smart_ptr<T>::operator =(const smart_ptr &rhs)
{
	// 递增右侧运算对象的引用计数
	++*rhs.m_use_count;
	// 递减本对象的引用计数
	if (--*m_use_count == 0)
	{
		// 如果管理的对象没有其他用户了，则释放对象分配的成员
		if (m_del)
		{
			m_del(m_pobject);
		}
		else
		{
			delete m_pobject;
		}

		delete m_use_count;
	}

	m_use_count = rhs.m_use_count;
	m_pobject = rhs.m_pobject;

	return *this; // 返回本对象
}


template <typename T>
T& smart_ptr<T>::operator*() const
{
	return *m_pobject;
}


template <typename T>
T* smart_ptr<T>::operator->() const
{
	return &this->operator*();
}


template <typename T>
smart_ptr<T>::~smart_ptr()
{
	if (--(*m_use_count) == 0)
	{
		if (m_del)
		{
			m_del(m_pobject);
		}
		else
		{
			delete m_pobject;
		}
		m_pobject = nullptr;
	}
}


template <typename T>
bool smart_ptr<T>::unique()
{
	return *m_use_count == 1;
}


template <typename T>
void smart_ptr<T>::reset()
{
	m_use_count--;

	if (m_use_count == 0)
	{
		if (m_del)
		{
			m_del(m_pobject);
		}
		else
		{
			delete m_pobject;
		}
	}

	m_pobject = nullptr;
	m_use_count = 1;
}


template <typename T>
void smart_ptr<T>::reset(T* p)
{
	m_use_count--;

	if (m_use_count == 0)
	{
		if (m_del)
		{
			m_del(m_pobject);
		}
		else
		{
			delete m_pobject;
		}
	}

	m_pobject = p;
	m_use_count = 1;
}


template <typename T>
T* smart_ptr<T>::get() const
{
	return m_pobject;
}


template <typename T>
smart_ptr<T>::operator bool() const
{
	return m_pobject != nullptr;
}
