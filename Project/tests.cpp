/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <jvermeer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:33:31 by jvermeer          #+#    #+#             */
/*   Updated: 2022/12/16 23:01:35 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque>
#include <iostream>
#include <list>
#include <string>
#include <stdlib.h>
// #include <type_traits> // C++11

#if STANDARD
#include <map>
#include <stack>
#include <vector>
#include <set>
namespace ft = std;
#else
#include "inc/map.hpp"
#include "inc/set.hpp"
#include "inc/stack.hpp"
#include "inc/vector.hpp"
#endif

template <typename T>
void printvector(ft::vector<T> &v)
{
	std::cout << "capacity: " << v.capacity() << " / size: " << v.size() << " / value: ";
	for (typename ft::vector<T>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main()
{
	try
	{
		{
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
			std::cout << "Operator= overloading tests:" << std::endl;
			std::cout << std::endl;
			ft::vector<int> vec(4, 4);
			std::cout << "Create vec: ";
			printvector<int>(vec);
			std::cout << std::endl;
			ft::vector<int> vec2(2, 2);
			vec = vec2;
			std::cout << "      Create vec2: ";
			printvector<int>(vec2);
			std::cout << "vec = vec2 || vec: ";
			printvector<int>(vec);
			std::cout << "vec2 = vec ||vec2: ";
			printvector<int>(vec2);
			ft::vector<int> vec3(8, 8);
			vec = vec3;
			std::cout << "      Create vec3: ";
			printvector<int>(vec3);
			std::cout << "vec = vec3 || vec: ";
			printvector<int>(vec);
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "RESIZE() tests:" << std::endl;
			std::cout << std::endl;
			ft::vector<int> vec(10, 1);
			std::cout << "Create vec: ";
			printvector<int>(vec);
			std::cout << std::endl;
			vec.insert(vec.begin(), 3);
			std::cout << "vec: ";
			printvector<int>(vec);
			vec.erase(vec.end() - 1);
			std::cout << "vec: ";
			printvector<int>(vec);
			std::cout << "resize(5)" << std::endl;
			vec.resize(5);
			std::cout << "vec: ";
			printvector<int>(vec);
			std::cout << "resize(6)" << std::endl;
			vec.resize(6);
			std::cout << "vec: ";
			printvector<int>(vec);
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "RESERVE exception's test:" << std::endl;
			ft::vector<int> bar;
			try
			{
				bar.reserve(bar.max_size() * 2);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "ERASE() & INSERT() tests:" << std::endl;
			std::cout << std::endl;
			ft::vector<std::string> vec;
			std::cout << "vec: ";
			printvector<std::string>(vec);
			vec.insert(vec.begin(), "1");
			std::cout << "insert(begin, 1)"
					  << " ||  vec: ";
			printvector<std::string>(vec);
			vec.erase(vec.begin());
			std::cout << "erase(begin)    "
					  << " ||  vec: ";
			printvector<std::string>(vec);
			vec.insert(vec.end(), "2");
			std::cout << "insert(end, 2)  "
					  << " ||  vec: ";
			printvector<std::string>(vec);
			vec.erase(vec.end() - 1);
			std::cout << "erase(end - 1)  "
					  << " ||  vec: ";
			printvector<std::string>(vec);
			vec.insert(vec.end(), 2, "5");
			std::cout << "insert(end, 2, 5)"
					  << "||  vec: ";
			printvector<std::string>(vec);
			vec.erase(vec.end() - 1);
			std::cout << "erase(end - 1)  "
					  << " ||  vec: ";
			printvector<std::string>(vec);
			vec.erase(vec.begin());
			std::cout << "erase(begin)    "
					  << " ||  vec: ";
			printvector<std::string>(vec);
			std::cout << std::endl;
			ft::vector<int> vec2(9);
			for (unsigned long int i = 0; i < vec2.size(); ++i)
				vec2[i] = (vec2.size() - i) * 3;
			std::cout << "vec2: ";
			printvector<int>(vec2);
			vec2.erase(vec2.end() - 1);
			std::cout << "erase(end - 1)  "
					  << " ||  vec: ";
			printvector<int>(vec2);
			vec2.erase(vec2.begin());
			std::cout << "erase(begin)    "
					  << " ||  vec: ";
			printvector<int>(vec2);
			vec2.erase(vec2.begin() + 2, vec2.begin() + 6);
			std::cout << "erase(beg +2,+6) "
					  << "||  vec: ";
			printvector<int>(vec2);
			vec2.insert(vec2.begin() + 1, 5, 1);
			std::cout << "insert(beg+1,5,1)"
					  << "||  vec: ";
			printvector<int>(vec2);
			vec2.erase(vec2.begin(), vec2.end());
			std::cout << "erase(beg, end)  "
					  << "||  vec: ";
			printvector<int>(vec2);
			std::cout << '\n';
			ft::vector<ft::vector<int>> erase_in_me;
			for (int i = 0; i < 15; i++)
			{
				ft::vector<int> j(1, i);
				erase_in_me.push_back(j);
			}
			for (size_t i = 0; i < erase_in_me.size(); i++)
				std::cout << erase_in_me.at(i).front() << ' ';
			std::cout << '\n';
			erase_in_me.erase(erase_in_me.begin() + 13);
			for (size_t i = 0; i < erase_in_me.size(); i++)
				std::cout << erase_in_me.at(i).front() << ' ';
			std::cout << '\n';
			erase_in_me.erase(erase_in_me.begin() + 2, erase_in_me.begin() + 6);
			for (size_t i = 0; i < erase_in_me.size(); i++)
				std::cout << erase_in_me.at(i).front() << ' ';
			std::cout << '\n';
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "RANDOM_ACCESS_ITERATOR tests:" << std::endl;
			ft::vector<int> v;
			for (int y = 0; y <= 30; y++)
				v.push_back(y);
			std::cout << "X it	:	";
			ft::vector<int>::iterator it;
			std::cout << it.base() << std::endl;
			std::cout << "it = vector.begin()+10: ";
			it = v.begin() + 10;
			std::cout << *it << std::endl;
			std::cout << "X it2(it + 3):	";
			ft::vector<int>::const_iterator it2(it + 3);
			std::cout << *it2 << std::endl;
			std::cout << "it2 = it:	";
			it2 = it;
			std::cout << *it2 << std::endl;
			std::cout << "it == it2:	";
			if (it == it2)
				std::cout << "it == it2" << std::endl;
			std::cout << "it != it3:	";
			ft::vector<int>::const_iterator it3;
			if (it != it3)
				std::cout << "it != it3" << std::endl;
			std::cout << "*it	:	";
			std::cout << *it << std::endl;
			std::cout << "*it = 15:	";
			*it = 15;
			std::cout << *it << std::endl;
			std::cout << "*it = 10:	";
			*it = 10;
			std::cout << *it << std::endl;
			std::cout << "++it	:	";
			std::cout << *++it << std::endl;
			std::cout << "it++	:	";
			std::cout << *it++ << std::endl;
			std::cout << "*it++	:	";
			*it++;
			std::cout << *it << std::endl;
			std::cout << "--it	:	";
			std::cout << *--it << std::endl;
			std::cout << "it--	:	";
			std::cout << *it-- << std::endl;
			std::cout << "*it--	:	";
			*it--;
			std::cout << *it << std::endl;
			std::cout << "it + 1	:	";
			std::cout << *(it + 1) << std::endl;
			std::cout << "1 + it	:	";
			std::cout << *(1 + it) << std::endl;
			std::cout << "*it++	:	";
			*it++;
			std::cout << *it << std::endl;
			std::cout << "it - 1	:	";
			std::cout << *(it - 1) << std::endl;
			std::cout << "it - it2:	";
			std::cout << it - it2 << std::endl;
			it2 = it;
			std::cout << "it2 <= it:	";
			if (it2 <= it)
				std::cout << "YES" << std::endl;
			std::cout << "--it2 < it:	";
			if (--it2 < it)
				std::cout << "YES" << std::endl;
			std::cout << "++it2 >= it:	";
			if (++it2 >= it)
				std::cout << "YES" << std::endl;
			std::cout << "++it2 > it:	";
			if (++it2 > it)
				std::cout << "YES" << std::endl;
			std::cout << "it += 2	:	";
			it += 2;
			std::cout << *it << std::endl;
			std::cout << "it -= 2	:	";
			it -= 2;
			std::cout << *it << std::endl;
			std::cout << "it[2] = 8:	";
			it[2] = 8;
			std::cout << it[2] << std::endl;
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "REVERSE_ITERATOR tests:" << std::endl;
			ft::vector<int> v;
			for (int y = 1; y <= 30; y++)
				v.push_back(y);
			ft::vector<int>::reverse_iterator rit;
			std::cout << "X rit	:		" << std::endl;
			std::cout << "rit = vector.rbegin():	";
			rit = v.rbegin();
			std::cout << *rit << std::endl;
			std::cout << "rit[0]	";
			std::cout << rit[2] << std::endl;
			std::cout << "*rit	" << *rit << std::endl;
			std::cout << "*rit++	" << *rit++ << std::endl;
			std::cout << "*rit	" << *rit << std::endl;
			std::cout << "*++rit	" << *++rit << std::endl;
			std::cout << "*rit	" << *rit << std::endl;
			std::cout << "*rit--	" << *rit-- << std::endl;
			std::cout << "*rit	" << *rit << std::endl;
			std::cout << "*--rit	" << *--rit << std::endl;
			std::cout << "*rit	" << *rit << std::endl;
			rit += 10;
			std::cout << "rit += 10	" << *rit << std::endl;
			rit -= 5;
			std::cout << "rit -= 5	" << *rit << std::endl;
			std::cout << "*(rit + 5)	" << *(rit + 5) << std::endl;
			std::cout << "*(rit - 1)	" << *(rit - 1) << std::endl;
			std::cout << "*rit		" << *rit << std::endl;
			std::cout << std::endl
					  << "Create x, y and z: " << std::endl;
			ft::vector<int>::reverse_iterator x(v.rbegin());
			ft::vector<int>::reverse_iterator y(x);
			ft::vector<int>::reverse_iterator z(v.rbegin() + 1);
			std::cout << std::boolalpha
					  << "*x == " << *x << std::endl		   // 30
					  << "*y == " << *y << std::endl		   // 30
					  << "*z == " << *z << std::endl		   // 29
					  << "x == y ? " << (x == y) << std::endl  // true
					  << "x != y ? " << (x != y) << std::endl  // false
					  << "x <  y ? " << (x < y) << std::endl   // false
					  << "x <= y ? " << (x <= y) << std::endl  // true
					  << "x == z ? " << (x == z) << std::endl  // false
					  << "x != z ? " << (x != z) << std::endl  // true
					  << "x <  z ? " << (x < z) << std::endl   // true
					  << "x <= z ? " << (x <= z) << std::endl  // true
					  << "x >  z ? " << (x > z) << std::endl   // true
					  << "x >= z ? " << (x >= z) << std::endl; // true
			x += 10;
			std::cout << "x += 10" << std::endl;
			std::cout << "*x	= " << *x << std::endl; // 20
			std::cout << "x + 5	= " << *(x + 5) << std::endl;
			std::cout << "*x	= " << *x << std::endl; // 20
			std::cout << "x - 5	= " << *(x - 5) << std::endl;
			std::cout << "*x	= " << *x << std::endl; // 20
			x -= 3;
			std::cout << "x -= 3" << std::endl;
			std::cout << "*x	= " << *x << std::endl; // 23
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "LEXICOGRAPHICAL_COMPARE tests:" << std::endl;
			ft::vector<int> v1;
			ft::vector<int> v2;
			std::cout << std::boolalpha << "empty v1 & v2	|| lex: " << ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << std::endl;
			for (int y = 1; y <= 10; y++)
				v2.push_back(y);
			std::cout << std::boolalpha << "empty v1	|| lex: " << ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << std::endl;
			for (int y = 1; y <= 10; y++)
				v1.push_back(y);
			std::cout << std::endl;

			std::cout << std::boolalpha << "v1  = v2 || lex: " << ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << std::endl;
			std::cout << std::boolalpha << "v1 <= v2 || lex: " << ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << std::endl;
			v2[9] = 11;
			std::cout << std::boolalpha << "v1  < v2 || lex: " << ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << std::endl;
			v2[9] = 10;
			std::cout << std::boolalpha << "v1 >= v2 || lex: " << ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << std::endl;
			v1[9] = 11;
			std::cout << std::boolalpha << "v1  > v2 || lex: " << ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()) << std::endl;
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "VECTOR_OPERATOR tests:" << std::endl;
			ft::vector<int> v1;
			ft::vector<int> v2;
			std::cout << "///// empty v1 & v2 /////" << std::endl;
			std::cout << std::boolalpha << "v1 == v2	" << (v1 == v2) << std::endl;
			std::cout << std::boolalpha << "v1 != v2	" << (v1 != v2) << std::endl;
			std::cout << std::boolalpha << "v1 <= v2	" << (v1 <= v2) << std::endl;
			std::cout << std::boolalpha << "v1 >= v2	" << (v1 >= v2) << std::endl;
			std::cout << std::boolalpha << "v1  < v2	" << (v1 < v2) << std::endl;
			std::cout << std::boolalpha << "v1  > v2	" << (v1 > v2) << std::endl;
			for (int y = 1; y <= 10; y++)
			{
				v1.push_back(y);
				v2.push_back(y);
			}
			std::cout << std::endl;
			std::cout << "///// v1 == v2 /////" << std::endl;
			std::cout << std::boolalpha << "v1 == v2	" << (v1 == v2) << std::endl;
			std::cout << std::boolalpha << "v1 != v2	" << (v1 != v2) << std::endl;
			std::cout << std::boolalpha << "v1 <= v2	" << (v1 <= v2) << std::endl;
			std::cout << std::boolalpha << "v1 >= v2	" << (v1 >= v2) << std::endl;
			std::cout << std::boolalpha << "v1  < v2	" << (v1 < v2) << std::endl;
			std::cout << std::boolalpha << "v1  > v2	" << (v1 > v2) << std::endl;
			std::cout << std::endl;
			std::cout << "///// v1 < v2 /////" << std::endl;
			v2[9] = 11;
			std::cout << std::boolalpha << "v1 == v2	" << (v1 == v2) << std::endl;
			std::cout << std::boolalpha << "v1 != v2	" << (v1 != v2) << std::endl;
			std::cout << std::boolalpha << "v1 <= v2	" << (v1 <= v2) << std::endl;
			std::cout << std::boolalpha << "v1 >= v2	" << (v1 >= v2) << std::endl;
			std::cout << std::boolalpha << "v1  < v2	" << (v1 < v2) << std::endl;
			std::cout << std::boolalpha << "v1  > v2	" << (v1 > v2) << std::endl;
			std::cout << std::endl;
			std::cout << "///// v1 > v2 /////" << std::endl;
			v1[9] = 12;
			std::cout << std::boolalpha << "v1 == v2	" << (v1 == v2) << std::endl;
			std::cout << std::boolalpha << "v1 != v2	" << (v1 != v2) << std::endl;
			std::cout << std::boolalpha << "v1 <= v2	" << (v1 <= v2) << std::endl;
			std::cout << std::boolalpha << "v1 >= v2	" << (v1 >= v2) << std::endl;
			std::cout << std::boolalpha << "v1  < v2	" << (v1 < v2) << std::endl;
			std::cout << std::boolalpha << "v1  > v2	" << (v1 > v2) << std::endl;
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			// CPP++ 11 must be enable to test it

			// std::cout << "IS_INTEGRAL tests:" << std::endl;
			// std::cout << std::boolalpha
			// << "char: " << ft::is_integral<char>::value << std::endl;
			// << "const char: " << ft::is_integral<const char>::value << std::endl
			// << "int: " << ft::is_integral<int>::value << std::endl
			// << "const int: " << ft::is_integral<const int>::value << std::endl
			// << "string: " << ft::is_integral<char *>::value << std::endl;
			// std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "SWAP tests:" << std::endl;
			ft::vector<int> v1(9, 1);
			ft::vector<int> v2(5, 2);
			ft::vector<int>::iterator i1 = v1.begin();
			ft::vector<int>::iterator i2 = v2.begin();
			std::cout << "Create v1: ";
			printvector(v1);
			std::cout << "Create v1: ";
			printvector(v2);
			std::cout << "i1 = v1.begin() : ";
			std::cout << "i1 = " << *i1 << std::endl;
			std::cout << "i1 = v1.begin() : ";
			std::cout << "i2 = " << *i2 << std::endl;
			v1.swap(v2);
			std::cout << "// SWAP //" << std::endl;
			std::cout << "v1 : ";
			printvector(v1);
			std::cout << "v2 : ";
			printvector(v2);
			std::cout << "i1 = " << *i1 << std::endl;
			std::cout << "i2 = " << *i2 << std::endl;
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "CAPACITY tests:" << std::endl;
			ft::vector<int> v1(10, 1);
			printvector<int>(v1);
			v1.erase(v1.begin());
			printvector<int>(v1);
			v1.insert(v1.begin() + 2, 5, 9);
			printvector<int>(v1);
			int tab[4] = {2, 2, 2, 2};
			v1.insert(v1.begin() + 2, tab, tab + 4);
			v1.push_back(24);
			printvector<int>(v1);
			v1.erase(v1.begin(), v1.end());
			printvector<int>(v1);
			v1.insert(v1.begin(), 40, 9);
			printvector<int>(v1);
			v1.insert(v1.begin(), 39, 1);
			std::cout << std::endl;

			ft::vector<int> tes(65, 7);
			std::cout << "s: " << tes.size() << ", c: " << tes.capacity() << std::endl;
			tes.reserve(12);
			std::cout << "s: " << tes.size() << ", c: " << tes.capacity() << std::endl;
			tes.reserve(66);
			std::cout << "s: " << tes.size() << ", c: " << tes.capacity() << std::endl;
			tes.reserve(128);
			std::cout << "s: " << tes.size() << ", c: " << tes.capacity() << std::endl;
			tes.reserve(1023);
			std::cout << "s: " << tes.size() << ", c: " << tes.capacity() << std::endl;
			tes.reserve(10252);
			std::cout << "s: " << tes.size() << ", c: " << tes.capacity() << std::endl;

			ft::vector<int> test(1, 1);
			ft::vector<int> test2(5, 5);
			test.insert(test.begin(), 200, 12);
			printvector<int>(test);
			test.insert(test.begin() + 12, 200, 30);
			printvector<int>(test);
			test.insert(test.end(), 12, 50);
			printvector<int>(test);
			test.insert(test.end() - 1, 0, 60);
			printvector<int>(test);
			test.insert(test.end() - 1, 1, 70);
			printvector<int>(test);
			test.insert(test.begin() + 412, test2.begin(), test2.end());
			printvector<int>(test);
			test.insert(test.begin() + 6, test2.begin(), test2.end());
			printvector<int>(test);
			test.insert(test.end(), test2.begin(), test2.end());
			printvector<int>(test);
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "PAIR tests:" << std::endl;
			ft::pair<int, int> p1 = ft::make_pair(10, 10);
			{
				ft::pair<int, int> p2(p1);
				std::cout << "p1(" << p1.first << ", " << p1.second << ") | "
						  << "p2(" << p2.first << ", " << p2.second << ")" << std::endl;
				std::cout << std::boolalpha
						  << "p1 == p2 ? " << (p1 == p2) << std::endl
						  << "p1 != p2 ? " << (p1 != p2) << std::endl
						  << "p1 <  p2 ? " << (p1 < p2) << std::endl
						  << "p1 <= p2 ? " << (p1 <= p2) << std::endl
						  << "p1 >  p2 ? " << (p1 > p2) << std::endl
						  << "p1 >= p2 ? " << (p1 >= p2) << std::endl;
				std::cout << std::endl;
			}
			{
				ft::pair<int, int> p2 = ft::make_pair(9, 11);
				std::cout << "p1(" << p1.first << ", " << p1.second << ") | "
						  << "p2(" << p2.first << ", " << p2.second << ")" << std::endl;
				std::cout << std::boolalpha
						  << "p1 == p2 ? " << (p1 == p2) << std::endl
						  << "p1 != p2 ? " << (p1 != p2) << std::endl
						  << "p1 <  p2 ? " << (p1 < p2) << std::endl
						  << "p1 <= p2 ? " << (p1 <= p2) << std::endl
						  << "p1 >  p2 ? " << (p1 > p2) << std::endl
						  << "p1 >= p2 ? " << (p1 >= p2) << std::endl;
				std::cout << std::endl;
			}
			{
				ft::pair<int, int> p2 = ft::make_pair(11, 9);
				std::cout << "p1(" << p1.first << ", " << p1.second << ") | "
						  << "p2(" << p2.first << ", " << p2.second << ")" << std::endl;
				std::cout << std::boolalpha
						  << "p1 == p2 ? " << (p1 == p2) << std::endl
						  << "p1 != p2 ? " << (p1 != p2) << std::endl
						  << "p1 <  p2 ? " << (p1 < p2) << std::endl
						  << "p1 <= p2 ? " << (p1 <= p2) << std::endl
						  << "p1 >  p2 ? " << (p1 > p2) << std::endl
						  << "p1 >= p2 ? " << (p1 >= p2) << std::endl;
				std::cout << std::endl;
			}
			{
				ft::pair<int, int> p2 = ft::make_pair(10, 9);
				std::cout << "p1(" << p1.first << ", " << p1.second << ") | "
						  << "p2(" << p2.first << ", " << p2.second << ")" << std::endl;
				std::cout << std::boolalpha
						  << "p1 == p2 ? " << (p1 == p2) << std::endl
						  << "p1 != p2 ? " << (p1 != p2) << std::endl
						  << "p1 <  p2 ? " << (p1 < p2) << std::endl
						  << "p1 <= p2 ? " << (p1 <= p2) << std::endl
						  << "p1 >  p2 ? " << (p1 > p2) << std::endl
						  << "p1 >= p2 ? " << (p1 >= p2) << std::endl;
				std::cout << std::endl;
			}
			{
				ft::pair<int, int> p2 = ft::make_pair(10, 11);
				std::cout << "p1(" << p1.first << ", " << p1.second << ") | "
						  << "p2(" << p2.first << ", " << p2.second << ")" << std::endl;
				std::cout << std::boolalpha
						  << "p1 == p2 ? " << (p1 == p2) << std::endl
						  << "p1 != p2 ? " << (p1 != p2) << std::endl
						  << "p1 <  p2 ? " << (p1 < p2) << std::endl
						  << "p1 <= p2 ? " << (p1 <= p2) << std::endl
						  << "p1 >  p2 ? " << (p1 > p2) << std::endl
						  << "p1 >= p2 ? " << (p1 >= p2) << std::endl;
			}
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			// value_compare is PROTECTED //
			// std::cout << "VALUE_COMPARE tests:" << std::endl;
			// ft::pair<int, int> p1 = ft::make_pair(10, 11);
			// ft::pair<int, int> p2 = ft::make_pair(10, 11);
			// ft::map<int, int>::value_compare v;
			//
			// ** USING myless<> template function ** //
			// ft::map<int, int, myless<int> >::value_compare v2;
			//
			// std::cout << std::boolalpha
			// << v(p1, p2) << std::endl
			// << v2(p1, p2) << std::endl;
			// std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "BINARY_ITERATOR tests:" << std::endl;
			ft::map<int, int> map;
			for (int y = 1; y <= 20; y++)
				map.insert(ft::make_pair(y, y * 2));
			std::cout << "Declare iterator: it(begin)" << std::endl;
			ft::map<int, int>::iterator it(map.begin());
			std::cout << "(*it).first:	" << (*it).first << std::endl;
			std::cout << "operator= overload test: it = begin + 1" << std::endl;
			it = ++map.begin();
			std::cout << "it->first:	" << it->first << std::endl;

			std::cout << "Declare const_it: cit(it)" << std::endl;
			ft::map<int, int>::const_iterator cit(it);
			std::cout << "cit->first:	" << cit->first << std::endl;
			std::cout << "cit = it" << std::endl;
			cit = it;
			std::cout << "cit->first:	" << cit->first << std::endl;
			std::cout << "cit == it ? ";
			if (cit == it)
				std::cout << "YES" << std::endl;
			std::cout << "++cit" << std::endl;
			++cit;
			std::cout << "it->first:	" << it->first << std::endl;
			std::cout << "cit->first:	" << cit->first << std::endl;
			std::cout << "cit != it ? ";
			if (cit != it)
				std::cout << "YES" << std::endl;
			std::cout << "it->second:	" << it->second << std::endl;
			std::cout << "it->second = 12;" << std::endl;
			it->second = 12;
			std::cout << "it->second:	" << it->second << std::endl;
			++it;
			++it;
			++it;
			std::cout << "it	:	";
			std::cout << it->first << std::endl;
			std::cout << "++it	:	";
			std::cout << (++it)->first << std::endl;
			std::cout << "it++	:	";
			std::cout << (it++)->first << std::endl;
			std::cout << "it	:	";
			std::cout << it->first << std::endl;
			std::cout << "--it	:	";
			std::cout << (--it)->first << std::endl;
			std::cout << "it--	:	";
			std::cout << (it--)->first << std::endl;
			std::cout << "*it--	:	";
			std::cout << (*it--).first << std::endl;
			std::cout << "*--it	:	";
			std::cout << (*--it).first << std::endl;
			std::cout << "*it++	:	";
			std::cout << (*it++).first << std::endl;
			std::cout << "*++it	:	";
			std::cout << (*++it).first << std::endl;
			std::cout << "it = begin() | while it != end() :" << std::endl;
			it = map.begin();
			while (it != map.end())
				std::cout << (it++)->first << " ";
			std::cout << std::endl;
			std::cout << "it = end() | while it != begin() :" << std::endl;
			while (it != map.begin())
				std::cout << (--it)->first << " ";
			std::cout << std::endl;
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "INSERT & CONSTRUCTORS tests:" << std::endl;
			ft::map<int, int> map1;
			for (int y = 1; y <= 10; ++y)
				map1.insert(ft::make_pair(y, y * 2));

			std::cout << "insert(first, last):" << std::endl;
			ft::map<int, int> map2;
			map2.insert(map1.begin(), map1.end());
			ft::map<int, int>::iterator it2 = map2.begin();
			while (it2 != map2.end())
				std::cout << (it2++)->first << " ";
			std::cout << std::endl;

			std::cout << "construct(first, last):" << std::endl;
			ft::map<int, int> map3(map1.begin(), map1.end());
			ft::map<int, int>::iterator it3 = map3.begin();
			while (it3 != map3.end())
				std::cout << (it3++)->first << " ";
			std::cout << std::endl;

			std::cout << "construct(map):" << std::endl;
			ft::map<int, int> map4(map1);
			ft::map<int, int>::iterator it4 = map4.begin();
			while (it4 != map4.end())
				std::cout << (it4++)->first << " ";
			std::cout << std::endl;

			std::cout << "bool when insert existing elem: ";
			std::cout << std::boolalpha << map1.insert(ft::make_pair(5, 10)).second << std::endl;
			std::cout << "iter on map with return iterator (when failing):" << std::endl;
			ft::map<int, int>::iterator check_fail = map1.insert(ft::make_pair(5, 10)).first;
			while (check_fail != map1.end())
				std::cout << (check_fail++)->first << " ";
			std::cout << std::endl;

			std::cout << "Insert with hint : ";
			ft::map<int, int> mm;
			for (int y = 1; y <= 10; ++y)
				mm.insert(ft::make_pair(y, y * 2));
			ft::map<int, int>::iterator hint = mm.begin();
			++hint;
			++hint;
			++hint;
			++hint;
			++hint;
			std::cout << "iterator = " << hint->first << std::endl;
			std::cout << "insert -5: ";
			mm.insert(hint, ft::make_pair(-5, 15));
			ft::map<int, int>::iterator begin = mm.begin();
			while (begin != mm.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			std::cout << "insert  6: ";
			mm.insert(hint, ft::make_pair(6, 15));
			begin = mm.begin();
			while (begin != mm.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			std::cout << "insert 55: ";
			mm.insert(hint, ft::make_pair(55, 15));
			mm.insert(mm.begin(), ft::pair<int, int>(66, 22));
			mm.insert(mm.end(), ft::pair<int, int>(66, 23));

			begin = mm.begin();
			while (begin != mm.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "INSERT(iterator hint, value) tests:" << std::endl;
			ft::map<int, std::string> map;
			map.insert(ft::make_pair(42, "test"));
			ft::map<int, std::string>::iterator begin = map.begin();
			while (begin != map.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;

			map.insert(ft::make_pair(50, "test"));
			begin = map.begin();
			while (begin != map.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;

			map.insert(ft::make_pair(35, "test"));
			begin = map.begin();
			while (begin != map.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;

			map.insert(map.begin(), ft::make_pair(55, "test"));
			begin = map.begin();
			while (begin != map.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;

			map.insert(map.end(), ft::make_pair(65, "test"));
			begin = map.begin();
			while (begin != map.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}

		{
			std::cout << "ERASE deep tests:" << std::endl;
			ft::map<int, int> map;
			for (int y = 200; y >= 70; y -= 10)
				map.insert(ft::make_pair(y, y));
			std::cout << std::endl;
			map.erase(map.begin());
			map.erase(map.begin()->first);
			map[1] = 12;
		}
		{
			ft::map<int, int> mp;
			for (int i = 0; i < 10; ++i)
				mp.insert(ft::pair<int, int>(i, i));

			ft::map<int, int>::iterator begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(++mp.begin());
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(mp.begin());
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(--mp.end());
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(++mp.begin(), ++(++(++mp.begin())));
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(mp.begin(), ++(++(++mp.begin())));
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			std::cout << "/////////////////////////" << std::endl;
			mp.erase(--(--(--mp.end())), --mp.end());
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(mp.begin(), mp.end());
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
		}
		{
			ft::map<int, int> mp;
			for (int i = 0; i < 6; ++i)
				mp.insert(ft::pair<int, int>(i, i));

			ft::map<int, int>::iterator begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(2);
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(3);
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(0);
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(5);
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp[-1] = 152;
			mp[10] = 888;
			mp[10] = 94;
			mp.erase(0);
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			mp.erase(1);
			begin = mp.begin();
			while (begin != mp.end())
				std::cout << (begin++)->first << " ";
			std::cout << std::endl;
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
		{
			std::cout << "MAP_OPERATOR tests:" << std::endl;
			ft::map<int, int> m1;
			ft::map<int, int> m2;
			std::cout << "///// empty m1 & m2 /////" << std::endl;
			std::cout << std::boolalpha << "m1 == m2	" << (m1 == m2) << std::endl;
			std::cout << std::boolalpha << "m1 != m2	" << (m1 != m2) << std::endl;
			std::cout << std::boolalpha << "m1 <= m2	" << (m1 <= m2) << std::endl;
			std::cout << std::boolalpha << "m1 >= m2	" << (m1 >= m2) << std::endl;
			std::cout << std::boolalpha << "m1  < m2	" << (m1 < m2) << std::endl;
			std::cout << std::boolalpha << "m1  > m2	" << (m1 > m2) << std::endl;
			for (int y = 1; y <= 10; y++)
			{
				m1.insert(ft::make_pair(y, y * 2));
				m2.insert(ft::make_pair(y, y * 2));
			}
			std::cout << std::endl;
			std::cout << "///// m1 == m2 /////" << std::endl;
			std::cout << std::boolalpha << "m1 == m2	" << (m1 == m2) << std::endl;
			std::cout << std::boolalpha << "m1 != m2	" << (m1 != m2) << std::endl;
			std::cout << std::boolalpha << "m1 <= m2	" << (m1 <= m2) << std::endl;
			std::cout << std::boolalpha << "m1 >= m2	" << (m1 >= m2) << std::endl;
			std::cout << std::boolalpha << "m1  < m2	" << (m1 < m2) << std::endl;
			std::cout << std::boolalpha << "m1  > m2	" << (m1 > m2) << std::endl;
			std::cout << std::endl;
			std::cout << "///// m1 < m2 /////" << std::endl;
			m2.erase(9);
			std::cout << std::boolalpha << "m1 == m2	" << (m1 == m2) << std::endl;
			std::cout << std::boolalpha << "m1 != m2	" << (m1 != m2) << std::endl;
			std::cout << std::boolalpha << "m1 <= m2	" << (m1 <= m2) << std::endl;
			std::cout << std::boolalpha << "m1 >= m2	" << (m1 >= m2) << std::endl;
			std::cout << std::boolalpha << "m1  < m2	" << (m1 < m2) << std::endl;
			std::cout << std::boolalpha << "m1  > m2	" << (m1 > m2) << std::endl;
			std::cout << std::endl;
			std::cout << "///// m1 > m2 /////" << std::endl;
			m1.erase(5);
			std::cout << std::boolalpha << "m1 == m2	" << (m1 == m2) << std::endl;
			std::cout << std::boolalpha << "m1 != m2	" << (m1 != m2) << std::endl;
			std::cout << std::boolalpha << "m1 <= m2	" << (m1 <= m2) << std::endl;
			std::cout << std::boolalpha << "m1 >= m2	" << (m1 >= m2) << std::endl;
			std::cout << std::boolalpha << "m1  < m2	" << (m1 < m2) << std::endl;
			std::cout << std::boolalpha << "m1  > m2	" << (m1 > m2) << std::endl;
			std::cout << "//////////////////////////////////////////////////////////////" << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}