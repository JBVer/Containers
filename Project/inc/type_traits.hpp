/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <jvermeer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:12:53 by jvermeer          #+#    #+#             */
/*   Updated: 2022/12/16 16:17:21 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <cstddef>

namespace ft{

/////////////////////////////////////////////////////
// ENABLE_IF :
/////////////////////////////////////////////////////

	// When bool is false, 'type' isn't defines:
	// The template/function who wants to access will inevitably crashes
	template<bool B, class T = void>
	struct enable_if {};
 
	// When bool is true, 'type' is define from 'T'and available:
	// The compiler will not remove this substitution from the Overload Set
	template<class T>
	struct enable_if<true, T> 
	{
		typedef T type;
	};

/////////////////////////////////////////////////////
// STD:iterator_traits:
/////////////////////////////////////////////////////

    // Iterator Tags:
    // These are empty types, used to distinguish different iterators.  The
    // distinction is not made by what they contain, but simply by what they
    // are.  Different underlying algorithms can then be used based on the
    // different operations supported by different iterator types.
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template <class Iter>
    struct iterator_traits
    {
        typedef typename Iter::value_type			value_type;
        typedef typename Iter::difference_type		difference_type;
        typedef typename Iter::iterator_category	iterator_category;
        typedef typename Iter::pointer				pointer;
        typedef typename Iter::reference			reference;
    };

    template <class T>
    struct iterator_traits<T*>
    {
        typedef T							value_type;
        typedef std::ptrdiff_t				difference_type;
        typedef random_access_iterator_tag	iterator_category;
        typedef T*							pointer;
        typedef T&							reference;
    };

    template <class T>
    struct iterator_traits<const T*>
	{
        typedef T							value_type;
        typedef std::ptrdiff_t				difference_type;
        typedef random_access_iterator_tag	iterator_category;
        typedef const T*					pointer;
        typedef const T&					reference;
    };

/////////////////////////////////////////////////////
// REMOVE_CV:
/////////////////////////////////////////////////////

		// --- REMOVE_CONST --- //
	template <typename T>
	struct remove_const { typedef T type; };

	template <typename T>
	struct remove_const<const T> { typedef T type; };


		// --- REMOVE_CV --- //
	template <typename T>
	struct remove_cv { typedef T type; };

	template <typename T>
	struct remove_cv<const T> { typedef T type; };

	template <typename T>
	struct remove_cv<volatile T> { typedef T type; };

	template <typename T>
	struct remove_cv<const volatile T> { typedef T type; };

/////////////////////////////////////////////////////
// IS_INTEGRAL:
/////////////////////////////////////////////////////

	// --- IS_INTEGRAL_ASSIST --- //
	template <class T>
	struct is_integral_assist { static const bool value = false; };

	// Specializations of 'is_integral_assist' template struct:
	// No template parameters because we're explicitly specifying the type 
	template<>
	struct is_integral_assist<bool> { static const bool value = true; };

	template<>
	struct is_integral_assist<char> { static const bool value = true; };

	template<>
	struct is_integral_assist<wchar_t> { static const bool value = true; };

	template<>
	struct is_integral_assist<signed char> { static const bool value = true; };

	template<>
	struct is_integral_assist<short int> { static const bool value = true; };

	template<>
	struct is_integral_assist<int> { static const bool value = true; };

	template<>
	struct is_integral_assist<long int> { static const bool value = true; };

	template<>
	struct is_integral_assist<long long int> { static const bool value = true; };

	template<>
	struct is_integral_assist<unsigned char> { static const bool value = true; };

	template<>
	struct is_integral_assist<unsigned short int> { static const bool value = true; };

	template<>
	struct is_integral_assist<unsigned int> { static const bool value = true; };

	template<>
	struct is_integral_assist<unsigned long int> { static const bool value = true; };

	template<>
	struct is_integral_assist<unsigned long long int> { static const bool value = true; };


	// --- IS_INTEGRAL --- //
	template <class T>
	struct is_integral { static const bool value = is_integral_assist< typename remove_cv<T>::type >::value; };

}

#endif
