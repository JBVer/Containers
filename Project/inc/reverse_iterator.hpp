/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <jvermeer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:20:05 by jvermeer          #+#    #+#             */
/*   Updated: 2022/12/17 14:41:56 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <cstddef>
#include "type_traits.hpp"

namespace ft
{
	
template<typename Iter>
class reverse_iterator
{
public:
	typedef ft::iterator_traits<Iter> _traits_;
	typedef typename _traits_::value_type			value_type;
	typedef typename _traits_::difference_type		difference_type;
    typedef typename _traits_::iterator_category	iterator_category;
	typedef typename _traits_::pointer				pointer;
	typedef typename _traits_::reference			reference;
	typedef typename std::size_t					size_type;

    /////////////////////////////////////////////////////
    // Default constructor & destructor:
    /////////////////////////////////////////////////////

	reverse_iterator(): _current() {};
	~reverse_iterator() {};

    /////////////////////////////////////////////////////
    // Param & Copy constructors:
    /////////////////////////////////////////////////////

	explicit reverse_iterator(Iter x): _current(x) {};

	template <class U>
	reverse_iterator(const reverse_iterator<U> & other)
	{
		_current = other.base();
	};

    /////////////////////////////////////////////////////
    // Operator overloads:
    /////////////////////////////////////////////////////

	template <class U>
	reverse_iterator & operator=(const reverse_iterator<U> & other)
	{
		_current = other.base();
		return *this;
	};

	reference operator*() const
	{
		Iter ret = _current;
		return *(--ret);
	};

	pointer operator->() const
	{
		Iter ret = _current;
		return (--ret).operator->();
	};

	reference operator[] (difference_type n)
	{
		Iter ret = _current;
		for (; n >= 0; --n)
			--ret;
		return *ret;
	};

	reverse_iterator &operator++()
	{
		--_current;
		return *this;
	};

	reverse_iterator operator++(int)
	{
		reverse_iterator tmp(this->base());
		--_current;
		return tmp;
	};

	reverse_iterator &operator--()
	{
		++_current;
		return *this;
	};

	reverse_iterator operator--(int)
	{
		reverse_iterator tmp(this->base());
		++_current;
		return tmp;
	};

	reverse_iterator operator+(difference_type n) const
	{
		return reverse_iterator(_current - n);
	};

	reverse_iterator operator-(difference_type n) const
	{
		return reverse_iterator(_current + n);
	};

	reverse_iterator & operator+=(difference_type n)
	{
		_current = _current - n;
		return *this;
	};

	reverse_iterator & operator-=(difference_type n)
	{
		_current = _current + n;
		return *this;
	};


	Iter base() const
	{
		return _current;
	};

private:
	Iter _current;
};

template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() == rhs.base() ? 1 : 0;
};

template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() != rhs.base() ? 1 : 0;
};

template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() > rhs.base() ? 1 : 0;
};

template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() >= rhs.base() ? 1 : 0;
};

template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() < rhs.base() ? 1 : 0;
};

template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() <= rhs.base() ? 1 : 0;
};

template <class Iter>
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> & it)
{
	return reverse_iterator<Iter>(it.base() - n);
};

template <class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return rhs.base() - lhs.base();
};

}

#endif