/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <jvermeer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:01:45 by jvermeer          #+#    #+#             */
/*   Updated: 2022/11/29 12:33:17 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

template < typename T, typename Container = ft::vector<T> >
class stack
{
public:

	/////////////////////////////////////////////////////
	// Typedefs:
	/////////////////////////////////////////////////////

	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;

	/////////////////////////////////////////////////////
	// Constructors & Destructor:
	/////////////////////////////////////////////////////

	explicit stack(const Container & cont = Container()): c(cont) {};

	stack(const stack & other): c(other.c) {};

	~stack() {};
	
	/////////////////////////////////////////////////////
	// General member functions:
	/////////////////////////////////////////////////////

	stack & operator=(const stack & other)
	{
		c = other.c;
	};

	/////////////////////////////////////////////////////
	// Element access:
	/////////////////////////////////////////////////////

	reference top()
	{
		return c.back();
	};

	const_reference top() const
	{
		return c.back();
	};

	/////////////////////////////////////////////////////
	// Capacity:
	/////////////////////////////////////////////////////

	bool empty() const
	{
		return c.empty();
	};

	size_type size() const
	{
		return c.size();
	};
	
	/////////////////////////////////////////////////////
	// Modifiers:
	/////////////////////////////////////////////////////

	void push(const value_type & value)
	{
		c.push_back(value);
	};

	void pop()
	{
		c.pop_back();
	};

	// Subject: "For non-member overloads, the keyword friend is allowed"
	// Cppreference : "The comparison is done by applying the corresponding operator to the underlying containers"

	template <class U, class Cont>
	friend bool operator==(const ft::stack<U,Cont> & lhs, const ft::stack<U,Cont> & rhs);

	template <class U, class Cont>
	friend bool operator!=(const ft::stack<U,Cont> & lhs, const ft::stack<U,Cont> & rhs);

	template <class U, class Cont>
	friend bool operator<(const ft::stack<U,Cont> & lhs, const ft::stack<U,Cont> & rhs);

	template <class U, class Cont>
	friend bool operator<=(const ft::stack<U,Cont> & lhs, const ft::stack<U,Cont> & rhs);

	template <class U, class Cont>
	friend bool operator>(const ft::stack<U,Cont> & lhs, const ft::stack<U,Cont> & rhs);

	template <class U, class Cont>
	friend bool operator>=(const ft::stack<U,Cont> & lhs, const ft::stack<U,Cont> & rhs);

protected:
	Container c;
};

template <class T, class Container>
bool operator==(const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs)
{
	return lhs.c == rhs.c;
};

template <class T, class Container>
bool operator!=(const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs)
{
	return lhs.c != rhs.c;
};

template <class T, class Container>
bool operator<(const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs)
{
	return lhs.c < rhs.c;
};

template <class T, class Container>
bool operator<=(const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs)
{
	return lhs.c <= rhs.c;
};

template <class T, class Container>
bool operator>(const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs)
{
	return lhs.c > rhs.c;
};

template <class T, class Container>
bool operator>=(const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs)
{
	return lhs.c >= rhs.c;
};

}

#endif