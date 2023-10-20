/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy_bidirectional_iterator.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <jvermeer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:21:27 by jvermeer          #+#    #+#             */
/*   Updated: 2022/12/16 23:10:35 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEGACY_BIDIRECTIONAL_ITERATOR_HPP
#define LEGACY_BIDIRECTIONAL_ITERATOR_HPP

#include <cstddef>
#include "map.hpp"
#include "pair.hpp"
#include "type_traits.hpp"

namespace ft
{

template< typename Pair, typename Node >
class legacy_bidirectional_iterator
{
public:
	typedef typename std::size_t					size_type;
	typedef typename std::ptrdiff_t					difference_type;
    typedef bidirectional_iterator_tag				iterator_category;
	typedef Pair									value_type;
	typedef value_type *							pointer;
	typedef value_type &							reference;
	typedef Node *									node_pointer;


    /////////////////////////////////////////////////////
    // Constructors & destructor:
    /////////////////////////////////////////////////////

	legacy_bidirectional_iterator(node_pointer ptr = NULL): _current(ptr)
	{
	};
	
	~legacy_bidirectional_iterator() {};

	legacy_bidirectional_iterator(const legacy_bidirectional_iterator< typename remove_cv<Pair>::type, Node > &it): _current(it.base())
	{
	};

    /////////////////////////////////////////////////////
    // Operator overloads:
    /////////////////////////////////////////////////////

	legacy_bidirectional_iterator & operator=(const legacy_bidirectional_iterator< typename remove_cv<Pair>::type, Node > &rhs)
	{
		_current = rhs.base();
		return *this;
	};

	template <typename U>
	bool operator==(const legacy_bidirectional_iterator< U, Node > &rhs) const
	{
		return _current == rhs.base();
	}
	
	template <typename U>
	bool operator!=(const legacy_bidirectional_iterator< U, Node > &rhs) const
	{
		return _current != rhs.base();
	}
	
	reference operator*() const
	{
		return *_current->pair;
	};

	pointer operator->() const
	{
		return _current->pair;
	}

	legacy_bidirectional_iterator &operator++()
	{
		this->_current = incrementIter(_current);
		return *this;
	};

	legacy_bidirectional_iterator operator++(int)
	{
		legacy_bidirectional_iterator tmp = *this;
		++*this;
		return tmp;
	};

	legacy_bidirectional_iterator &operator--()
	{
		this->_current = decrementIter(_current);
		return *this;
	};

	legacy_bidirectional_iterator operator--(int)
	{
		legacy_bidirectional_iterator tmp = *this;
		--*this;
		return tmp;
	};

	node_pointer base() const
	{
		return  _current;
	};

private:

	node_pointer	_current;

	bool isNullNode(node_pointer node)
	{
		return !node->left;
	}

	bool isLeft(node_pointer node)
	{
		return node->parent->left == node;
	}

	node_pointer incrementIter(node_pointer tmp)
	{
		if (isNullNode(tmp->right) && tmp->right->parent == tmp)
			return tmp->right;
		if (!isNullNode(tmp->right))
		{
			tmp = tmp->right;
			while (!isNullNode(tmp->left))
				tmp = tmp->left;
			return tmp;
		}
		else
		{
			while (!isLeft(tmp))
				tmp = tmp->parent;
			return tmp->parent;
		}
	}

	node_pointer decrementIter(node_pointer tmp)
	{
		if (isNullNode(tmp))
			return tmp->parent;
		if (!isNullNode(tmp->left))
		{
			tmp = tmp->left;
			while (!isNullNode(tmp->right))
				tmp = tmp->right;
			return tmp;
		}
		else
		{
			node_pointer endNode = tmp;
			while (tmp->parent && isLeft(tmp))
				tmp = tmp->parent;
			if (!tmp->parent)
				return endNode;
			return tmp->parent;
		}
	}
};
}

#endif