/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <jvermeer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:58:50 by jvermeer          #+#    #+#             */
/*   Updated: 2022/12/17 14:41:46 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <cstddef>
#include "type_traits.hpp"

namespace ft
{

template<typename T>
class random_access_iterator
{
public:
	typedef ft::iterator_traits<T*> _traits_;
	typedef typename _traits_::value_type			value_type;
	typedef typename _traits_::difference_type		difference_type;
    typedef typename _traits_::iterator_category	iterator_category;
	typedef typename _traits_::pointer				pointer;
	typedef typename _traits_::reference			reference;
	typedef typename std::size_t					size_type;

    /////////////////////////////////////////////////////
    // Constructors & destructor:
    /////////////////////////////////////////////////////

	random_access_iterator(pointer ptr = NULL): _current(ptr) {};
	
	~random_access_iterator() {};

	random_access_iterator(const random_access_iterator< typename remove_cv<T>::type > &it): _current(it.operator->()) {};

    /////////////////////////////////////////////////////
    // Operator overloads:
    /////////////////////////////////////////////////////

	random_access_iterator & operator=(const random_access_iterator< typename remove_cv<T>::type > &rhs)
	{
		_current = rhs.base();
		return *this;
	};

	bool operator==(const random_access_iterator<const T> &rhs) const
	{
		return _current == rhs.base() ? 1 : 0;
	}
	
	bool operator!=(const random_access_iterator<const T> &rhs) const
	{
		return _current != rhs.base() ? 1 : 0;
	}
	
	reference operator*() const
	{
		return *_current;
	};

	pointer operator->() const
	{
		return _current;
	}

	random_access_iterator &operator++()
	{
		this->_current++;
		return *this;
	};

	random_access_iterator operator++(int)
	{
		random_access_iterator tmp = *this;
		++*this;
		return tmp;
	};

	random_access_iterator &operator--()
	{
		this->_current--;
		return *this;
	};

	random_access_iterator operator--(int)
	{
		random_access_iterator tmp = *this;
		--*this;
		return tmp;
	};

	random_access_iterator operator+(difference_type const & n) const
	{
		return  random_access_iterator(base() + n);
	};
	
	difference_type operator+(random_access_iterator< const T > const & rhs) const
	{
		return  this->base() + rhs.base();
	};

	random_access_iterator operator-(difference_type const & n) const
	{
		return  random_access_iterator(base() - n);
	};

	difference_type operator-(random_access_iterator< const T > const & rhs) const
	{
		return  this->base() - rhs.base();
	};

	bool operator<(const random_access_iterator< const T > &rhs) const
	{
		return _current < rhs.base() ? 1 : 0;
	}

	bool operator>(const random_access_iterator< const T > &rhs) const
	{
		return _current > rhs.base() ? 1 : 0;
	}

	bool operator<=(const random_access_iterator< const T > &rhs) const
	{
		return _current <= rhs.base() ? 1 : 0;
	}
	
	bool operator>=(const random_access_iterator< const T > &rhs) const
	{
		return _current >= rhs.base() ? 1 : 0;
	}

	random_access_iterator &operator+=(difference_type const & n)
	{
		_current = _current + n;
		return *this;
	};

	random_access_iterator &operator-=(difference_type const & n)
	{
		_current = _current - n;
		return *this;
	};

	reference operator[](difference_type index) const
	{
		return _current[index];
	};

	pointer base() const
	{
		return  _current;
	};

protected:
	pointer	_current;
};

// Within class, operator+ can only be unary or binary operator.
// Must be implemented outside the class definition.
// *this is an implicit argument, this template function has 3 parameters.
template <typename T>
random_access_iterator<T> operator+(typename ft::iterator_traits<T*>::difference_type const & n, random_access_iterator<T> const &rhs)
{
	return  random_access_iterator<T>(rhs.base() + n);
};
}

#endif