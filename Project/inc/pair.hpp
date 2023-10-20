/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <jvermeer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:05:04 by jvermeer          #+#    #+#             */
/*   Updated: 2022/12/16 15:51:23 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

#include "type_traits.hpp"

namespace ft {

	template<typename T1, typename T2>
	struct pair
	{
	public:
		typedef T1	first_type;
		typedef T2	second_type;
	
		first_type	first;
		second_type	second;
	
		pair(): first(0), second(0) {};
	
		pair(const T1 & x, const T2 & y): first(x), second(y) {};
	
		template<class U1, class U2>
		pair(const pair<U1, U2> & p): first(p.first), second(p.second) {};
	
		pair & operator=(const pair< typename remove_cv<T1>::type, T2 > & other)
		{
			first = other.first;
			second = other.second;
			return *this;
		};
	};
	
	template< class T1, class T2 >
	ft::pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return ft::pair<T1, T2>(t, u);
	};
	
	template< class T1, class T2 >
	bool operator==(const ft::pair<T1,T2> & lhs, const ft::pair<T1,T2> & rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	};
	
	template< class T1, class T2 >
	bool operator!=(const ft::pair<T1,T2> & lhs, const ft::pair<T1,T2> & rhs)
	{
		return !(lhs == rhs);
	};
	
	template< class T1, class T2 >
	bool operator<(const ft::pair<T1,T2> & lhs, const ft::pair<T1,T2> & rhs)
	{
		if (lhs.first == rhs.first)
			return lhs.second < rhs.second;
		return lhs.first < rhs.first;
	};
	
	template< class T1, class T2 >
	bool operator<=(const ft::pair<T1,T2> & lhs, const ft::pair<T1,T2> & rhs)
	{
		return (lhs < rhs) || (lhs == rhs);
	};
	
	template< class T1, class T2 >
	bool operator>(const ft::pair<T1,T2> & lhs, const ft::pair<T1,T2> & rhs)
	{
		return !(lhs <= rhs);
	};
	
	template< class T1, class T2 >
	bool operator>=(const ft::pair<T1,T2> & lhs, const ft::pair<T1,T2> & rhs)
	{
		return !(lhs < rhs);
	};
	
}
#endif