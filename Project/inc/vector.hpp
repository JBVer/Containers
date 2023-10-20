// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <jvermeer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:10:34 by jvermeer          #+#    #+#             */
/*   Updated: 2022/11/05 17:06:39 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>	
#include "lexicographical_compare.hpp"
#include "type_traits.hpp"
#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"

namespace ft
{
	
template < typename T, typename Allocator = std::allocator<T> >
class vector
{
public:

	/////////////////////////////////////////////////////
	// Typedefs:
	/////////////////////////////////////////////////////

	typedef typename std::ptrdiff_t							difference_type;
	typedef typename std::size_t							size_type;
	typedef typename Allocator::reference 					reference;
	typedef typename Allocator::const_reference				const_reference;
	typedef T 												value_type;
	typedef Allocator										allocator_type;
	typedef typename Allocator::pointer						pointer;
	typedef typename Allocator::const_pointer				const_pointer;
	typedef ft::random_access_iterator< value_type >		iterator;
	typedef ft::random_access_iterator< const value_type >	const_iterator;
	typedef ft::reverse_iterator< iterator >				reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >			const_reverse_iterator;

	/////////////////////////////////////////////////////
	// Constructors & Destructor:
	/////////////////////////////////////////////////////

	explicit vector (const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _first(NULL), _alloc(alloc) {};

	explicit vector (size_type count, const_reference value = value_type(), const allocator_type & alloc = allocator_type())
	{
		_alloc = alloc;
		_first = _alloc.allocate(count);
		_size = count;
		_capacity = count;
		for (size_type i = 0; i < count; i++)
			_alloc.construct(_first + i, value);
	};

	template <class InputIt>
	vector (typename enable_if<!is_integral<InputIt>::value, InputIt>::type first, InputIt last, const allocator_type & alloc = allocator_type())
	{
		size_type dif = 0;
		for(InputIt tmp = first; tmp != last; tmp++)
			++dif;
		_alloc = alloc;
		_first = _alloc.allocate(dif);
		_size = dif;
		_capacity = dif;
		for (size_type i = 0; i < dif; i++)
			_alloc.construct(_first + i, *first++);
	};

	vector (const vector & other): _size(0), _capacity(0), _first(NULL), _alloc(other.get_allocator())
	{
		*this = other;
	};

	~vector ()
	{
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(_first + i);
		if (_first)
			_alloc.deallocate(_first, _capacity);
	}

	/////////////////////////////////////////////////////
	// General member functions:
	/////////////////////////////////////////////////////

	vector & operator= (const vector & x)
	{
		if (_size)
			this->clear();
		this->reserve(x.size());
		_size = x._size;
		_alloc = x._alloc;
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(_first + i, x[i]);
		return *this;
	};

	void assign (size_type count, const T & value)
	{
		vector tmp(count, value);
		*this = tmp;
	};

	template <class InputIt>
	void assign (InputIt first, InputIt last)
	{
		vector tmp;

		tmp.insert(tmp.begin(), first, last);
		*this = tmp;
	};

	allocator_type get_allocator() const
	{
		return allocator_type();
	};

	/////////////////////////////////////////////////////
	// Element access:
	/////////////////////////////////////////////////////

	reference at(size_type pos)
	{
		if (pos >= _size)
			throw std::out_of_range("Out of range");
		return _first[pos];
	};

	const_reference at (size_type pos) const
	{
		if (pos >= _size)
			throw std::out_of_range("Out of range");
		return _first[pos];
	};

	reference operator[] (size_type index)
	{
		return _first[index];
	};

	const_reference operator[] (size_type index) const
	{
		return _first[index];
	};

	reference front()
	{
		return *_first;
	};

	const_reference front() const
	{
		return *_first;
	};

	reference back()
	{
		return *(_first + _size - 1);
	};

	const_reference back() const
	{
		return *(_first + _size - 1);
	};

	pointer data()
	{
		return _first;
	};

	/////////////////////////////////////////////////////
	// Iterators:
	/////////////////////////////////////////////////////

	iterator begin ()
	{
		return iterator(_first);
	};
	
	const_iterator begin() const
	{
		return const_iterator(_first);
	};

	iterator end ()
	{
		return iterator(_first + _size);
	};

	const_iterator end() const
	{
		return const_iterator(_first + _size);
	};
	
    reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	};
	
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	};

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	};
	
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	};

	/////////////////////////////////////////////////////
	// Capacity:
	/////////////////////////////////////////////////////

	bool empty() const
	{
		return !size();
	}

	size_type size () const
	{
		return _size;
	};

	size_type max_size () const
	{
		return _alloc.max_size();
	};

	void reserve (size_type n)
	{
		if (n > _capacity)
		{
			if (n > max_size())
				throw std::length_error("vector::reserve");
			pointer tmp = _first;
			size_type old_cap = _capacity;
			_capacity = n;
			_first = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(_first + i, tmp[i]);
				_alloc.destroy(tmp + i);
			}
			if (old_cap)
				_alloc.deallocate(tmp, old_cap);
		}
	};

	size_type capacity () const
	{
		return _capacity;
	};

	/////////////////////////////////////////////////////
	// Modifiers:
	/////////////////////////////////////////////////////

	void clear()
	{
		erase(begin(), end());
	}

	iterator insert (iterator position, const_reference val)
	{
		size_type pos = 0;
		for (size_type i = 0; position - i != vector::begin(); i++)
			pos++;
		insert(position, 1, val);
		return iterator(_first + pos);		
	};

	iterator insert (iterator position, size_type n, const_reference val)
	{
		if (n)
		{
			size_type beg = 0;
			for (size_type i = 0; position - i != vector::begin(); i++)
				beg++;
			reserve(return_new_capacity(_size, _capacity, n));
			_size += n;
			position = iterator(_first + beg);
			iterator end(_first + _size - 1);
			while (end != position + n - 1)
			{
				_alloc.construct(end.base(), *(end - n));
				_alloc.destroy(end.base() - n);
				end--;
			}
			for (size_type i = 0; i < n; i++)
				_alloc.construct((position + i).base(), val);
		}
		return position;
	};

	template <class InputIt>
	iterator insert (iterator position, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
	{
		size_type beg = 0;
		size_type n = 0;
		InputIt tmp = first;
		for (; tmp != last; ++tmp)
			++n;
		for (size_type i = 0; position - i != begin(); i++)
			beg++;
		reserve(return_new_capacity(_size, _capacity, n));
		_size += n;
		position = iterator(_first + beg);
		iterator end(_first + _size - 1);
		while (end != position + n - 1)
		{
			_alloc.construct(end.base(), *(end - n));
			_alloc.destroy(end.base() - n);
			end--;
		}
		for (size_type i = 0; i < n; i++)
			_alloc.construct((position + i).base(), *first++);
		return position;
	};

	iterator erase (iterator pos)
	{
		return erase(pos, pos + 1);
	};

	iterator erase (iterator first, iterator last)
	{
		difference_type d = last.base() - first.base();
		iterator ret(first.base());
		for (difference_type i = 0; first + i != last; i++)
			_alloc.destroy((first + i).base());
		while (last != end())
		{
			_alloc.construct(first++.base(), *last);
			_alloc.destroy(last++.base());
		}
		_size -= d;
		return ret;
	};

	void push_back (const value_type& val)
	{
		reserve(return_new_capacity(_size, _capacity, 1));
		_alloc.construct(_first + _size, val);
		++_size;
	};

	void pop_back ()
	{
		erase(iterator(_first + _size - 1));
	}

	void resize (size_type n, value_type val = value_type())
	{
		if (n < _size)
			for (size_type i = 0; n + i < _size; i++)
				_alloc.destroy(_first + n + i);
		else
		{
			if (n > _capacity)
				reserve(return_new_capacity(_size, _capacity, n - _size));
			for (size_type i = 0; _size + i < n; i++)
				_alloc.construct(_first + _size + i, val);
		}
		_size = n;
	};

	void swap (vector & other)
	{
		pointer ptrswap = this->_first;
		size_type sizeswap = this->_size;
		size_type capaswap = this->_capacity;
		allocator_type allocswap = this->_alloc;
		this->_first = other._first;
		this->_alloc = other._alloc;
		this->_capacity = other._capacity;
		this->_size = other._size;
		other._first = ptrswap;
		other._alloc = allocswap;
		other._capacity = capaswap;
		other._size = sizeswap;
	};

private:
    size_type		_size;
    size_type		_capacity;
	pointer			_first;
	allocator_type	_alloc;

	size_type return_new_capacity (size_type &size, size_type &capacity, size_type elems)
	{
		if (size == capacity)
		{
			if (elems <= capacity)
				return (capacity * 2);
			else
				return (capacity + elems);
		}
		else
		{
			if (size + elems <= capacity)
				return (capacity);
			if (size + elems <= size * 2)
				return (size * 2);
			else
				return (size + elems);
		};
	}
};

template <class T, class Alloc>
bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return 
	!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())
	&& !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
};

template <class T, class Alloc>
bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs == rhs);
};

template <class T, class Alloc>
bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};

template <class T, class Alloc>
bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs > rhs);
};

template <class T, class Alloc>
bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
};

template <class T, class Alloc>
bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs < rhs);
};

template <class T, class Alloc>
void swap (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
{
	lhs.swap(rhs);
};
}

#endif