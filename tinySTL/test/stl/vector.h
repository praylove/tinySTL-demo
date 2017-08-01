#pragma once
#ifndef _VECTOR_H
#define _VECTOR_H

#include <memory>

template <typename T>
class Vector
{
public:
	typedef T* iterator;

	//defualt constructor
	Vector() :c(0)
	{
	}

	//fill construct
	explicit Vector(size_t n,const T& val = T())
	{
		c = n;
		_beg = a.allocate(c);
		_end = _beg + c;
		for (auto it = _beg; it != _end; ++it)
		{
			a.construct(it, val);
		}
	}

	//copy construct partly
	explicit Vector(iterator first, iterator last)
	{
		c = last - first;
		_beg = a.allocate(c);
		_end = _beg + c;
		for (auto it1 = _beg, it2 = first; it1 != _end; ++it1, ++it2)
		{
			a.construct(it1, *it2);
		}
	}

	//initializer constructor
	Vector(std::initializer_list<T> i1)
	{
		c = i1.size();
		_beg = a.allocate(c);
		_end = _beg + c;
		auto  it2 = i1.begin();
		for (auto it1 = _beg; it1 != _end; ++it1, ++it2)
		{
			a.construct(it1, *it2);
		}
	}

	//copy constructor
	Vector(Vector& v)
	{
		if (*this == v)
			return *this;
		a.deallocate(_beg, c);
		c = v.size();
		_beg = a.allocate(c);
		_end = _beg + c;
		for (auto it1 = _beg, it2 = v.begin(); it1 != _end; ++it1, ++it2)
		{
			a.construct(it1, *it2);
		}
	}

	//move constructor
	Vector(Vector&& v)
	{
		std::swap(a, v.geta());
		c = v.size();
		_beg = v.begin();
		_end = v.end();
	}

	//destructor
	~Vector()
	{
		a.deallocate(_beg, c);
	}
	
	Vector& operator=(const Vector& v)
	{
		if (*this == v)
			return *this;
		a.deallocate(_beg, c);
		c = v.size();
		_beg = a.allocate(c);
		_end = _beg + c;
		for (auto it1 = _beg, it2 = v.begin(); it1 != _end; ++it1, ++it2)
		{
			a.construct(it1, *it2);
		}
	}

	Vector& operator=(Vector&& v)
	{
		std::swap(a, v.geta());
		c = v.size();
		_beg = v.begin();
		_end = v.end();
	}

	T operator[](size_t pos)
	{
		return *(_beg + pos);
	}

	bool operator==(Vector& v)
	{
		if (c != v.size())
			return false;
		for (auto it1 = _beg, it2 = v.begin(); it1 != _end(); ++it)
		{
			if (*it1 != *it2)
				return false;
		}

		return true;
	}

	iterator begin()
	{
		return _beg;
	}

	iterator end()
	{
		return _end;
	}

	int size()
	{
		return c;
	}

	int max_size()
	{
		return a.max_size();
	}

	std::allocator<T> geta()
	{
		return a;
	}

	T front()
	{
		return *(_beg);
	}

	T back()
	{
		return *(_end - 1);
	}

	bool empty()
	{
		return c == 0;
	}

	void insert(iterator it, T val)
	{
		if (c == a.max_size())
		{
			allocator<T> temp;
			iterator _nbeg = temp.allocate(c * 2);

			for (auto it1 = _beg, it2 = _nbeg; it1 != _end; ++it1, ++it2)
			{
				temp.construct(it2, *it1);
			}
			a.deallocate(_beg, c);
			a = temp;
			_end = _beg + c;
		}
		for (auto it3 = _end; it3 != it; --it3)
		{
			a.construct(it3, *(it3 - 1));
		}
		a.construct(it, val);
		++c;
		++_end;
	}

	void erase(iterator it)
	{
		while (it != _end)
		{
			a.construct(it, *(it + 1));
			++it;
		}
		a.destroy(it);
		--_end;
	}

	void push_back(T val)
	{
		insert(_end, val);
	}

	void pop_back()
	{
		erase(_end - 1);
	}
private:
	size_t c;
	std::allocator<T> a;
	iterator _beg;
	iterator _end;
};


#endif // !_VECTOR_H
