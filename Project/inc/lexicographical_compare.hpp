/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <jvermeer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:04:26 by jvermeer          #+#    #+#             */
/*   Updated: 2022/12/17 14:41:03 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{
	template <typename InputIt1, typename InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
    	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
    	{
    	    if (*first1 < *first2)
    	        return true;
    	    if (*first2 < *first1)
    	        return false;
    	}
    	return (first1 == last1) && (first2 != last2); // the only way is first1 < first2
	}

	template <typename InputIt1, typename InputIt2, typename Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
	    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	    {
	        if (comp(*first1, *first2))
	            return true;
	        if (comp(*first2, *first1))
	            return false;
	    }
	    return (first1 == last1) && (first2 != last2);
	}
}

#endif
