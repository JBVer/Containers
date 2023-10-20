/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <jvermeer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:16:27 by jvermeer          #+#    #+#             */
/*   Updated: 2022/12/17 14:39:00 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include <cstddef>
#include "map.hpp"
#include "pair.hpp"
#include "legacy_bidirectional_iterator.hpp"
#include "lexicographical_compare.hpp"
#include "type_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template< typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator< Key > >
class set
{
private:

	/////////////////////////////////////////////////////
	// Node struct:
	/////////////////////////////////////////////////////
	typedef struct	s_node
	{
		bool						color;
		Key 	*					pair;
		s_node	*					left;
		s_node	*					right;
		s_node	*					parent;
	}				node;

public:

	/////////////////////////////////////////////////////
	// Typedefs:
	/////////////////////////////////////////////////////
	typedef const Key								key_type;
	typedef const Key								value_type;
	typedef typename std::size_t					size_type;
	typedef typename std::ptrdiff_t					difference_type;
	typedef Compare									key_compare;
	typedef Allocator								allocator_type;
	typedef value_type &							reference;
	typedef const value_type &						const_reference;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;
	typedef node *									node_pointer;
	typedef typename Allocator::template rebind<node>::other				allocator_rebind;
	typedef ft::legacy_bidirectional_iterator< value_type, node >			iterator;
	typedef ft::legacy_bidirectional_iterator< const value_type, node >		const_iterator;
	typedef ft::reverse_iterator< iterator >								reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >							const_reverse_iterator;

	/////////////////////////////////////////////////////
	// Member classes / value_compare:
	/////////////////////////////////////////////////////

	class value_compare
	{
		friend class set;
	protected:
		Compare comp;
		value_compare(Compare c): comp(c) {}
	public:
		bool operator()(const value_type& lhs, const value_type& rhs) const { return comp(lhs, rhs); }
	};

	/////////////////////////////////////////////////////
	// Constructors & Destructor:
	/////////////////////////////////////////////////////

	set(): _size(0), _cmp(key_compare()), _alloc(allocator_type())
	{
		_end = _alloc_node.allocate(1);
		_end->color = BLACK;
		_end->parent = NULL;
		_end->left = NULL;
		_end->right = NULL;
		_root = _end;
	};

	explicit set(const key_compare & comp, const Allocator & alloc = Allocator()): _size(0), _cmp(comp), _alloc(alloc)
	{
		_end = _alloc_node.allocate(1);
		_end->color = BLACK;
		_end->parent = NULL;
		_end->left = NULL;
		_end->right = NULL;
		_root = _end;
	};

	template< class InputIt >
	set(InputIt first, InputIt last, const key_compare & comp = key_compare(), const Allocator & alloc = Allocator()): _size(0), _cmp(comp), _alloc(alloc)
	{
		_end = _alloc_node.allocate(1);
		_end->color = BLACK;
		_end->parent = NULL;
		_end->left = NULL;
		_end->right = NULL;
		_root = _end;
		insert(first, last);
	};

	set( const set& other ): _size(0), _cmp(other.key_comp()), _alloc(other.get_allocator())  
	{
		_end = _alloc_node.allocate(1);
		_end->color = BLACK;
		_end->parent = NULL;
		_end->left = NULL;
		_end->right = NULL;
		_root = _end;
		*this = other;
	};

	~set()
	{
		clear();
		_alloc_node.deallocate(_end, 1);
	};

	/////////////////////////////////////////////////////
	// General member functions:
	/////////////////////////////////////////////////////

	set & operator=( const set& other )
	{
		clear();
		insert(other.begin(), other.end());
		return *this;
	};

	allocator_type get_allocator() const
	{
		return allocator_type();
	};

	/////////////////////////////////////////////////////
	// Element access:
	/////////////////////////////////////////////////////

	reference at( const Key & key )
	{
		node_pointer ret = search(key);
		if (ret != NULL)
			return *ret->pair;
		throw std::out_of_range("set::at");
	};

	const_reference at( const Key & key ) const
	{
		node_pointer ret = search(key);
		if (ret != NULL)
			return *ret->pair;
		throw std::out_of_range("set::at");
	};

	reference operator[]( const Key& key )
	{
		node_pointer ret = search(key);
		if (ret != NULL)
			return *ret->pair;
		return (*(insert(key).first));
	};

	/////////////////////////////////////////////////////
	// Iterators:
	/////////////////////////////////////////////////////

	iterator begin()
	{
		node_pointer tmp = _root;
		while (tmp != _end && tmp->left != _end)
			tmp = tmp->left;
		return iterator(tmp);
	};

	const_iterator begin() const
	{
		node_pointer tmp = _root;
		while (tmp != _end && tmp->left != _end)
			tmp = tmp->left;
		return const_iterator(tmp);
	};

	iterator end()
	{
		return iterator(_end);
	};

	const_iterator end() const
	{
		return const_iterator(_end);
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
		std::allocator< char > tmp;
		size_type max_size = tmp.max_size();
		size_type struct_node = sizeof(node); // - sizeof(value_type *); // To reproduce real max_size
		size_type pair = sizeof(value_type);
		return max_size / (pair + struct_node);
	};

	/////////////////////////////////////////////////////
	// Modifiers:
	/////////////////////////////////////////////////////

	void clear()
	{
		clearFromRoot(_root);
		_root = _end;
		_size = 0;
	};

	ft::pair<iterator, bool> insert( const value_type& value )
	{
		bool bool_ret = true;
		node_pointer node_ret = insertNode(_root, initNewNode(value), &bool_ret);
		if (bool_ret)
			_size++;
		return (ft::make_pair(iterator(node_ret), bool_ret));
	}

	iterator insert( iterator pos, const value_type& value )
	{
		bool bool_ret = true;
		node_pointer node_ret;
		node_pointer hint = pos.base();
		if (hint == _end && _root != _end)
			node_ret = insertNode(_root, initNewNode(value), &bool_ret);
		else if (hint != _root && _cmp(*hint->pair, value) && _cmp(*_root->pair, *hint->pair)) // hint < value && root < hint
			node_ret = insertNode(hint, initNewNode(value), &bool_ret);
		else if (hint != _root && _cmp(value, *hint->pair) && _cmp(*hint->pair, *_root->pair)) // value < hint && hint < root
			node_ret = insertNode(hint, initNewNode(value), &bool_ret);
		else
			node_ret = insertNode(_root, initNewNode(value), &bool_ret);
		if (bool_ret)
			_size++;
		return (iterator(node_ret));
	};

	template< class InputIt >
	void insert( InputIt first, InputIt last )
	{
		while (first != last)
			insert(*first++);
	};

	void erase( iterator pos )
	{
		node_pointer keyNode = search(*pos);
		if (keyNode)
			eraseNode(keyNode);
	};

	void erase( iterator first, iterator last )
	{
		iterator tmp;
		node_pointer keyNode;
		while (first != last)
		{
			tmp = first++;
			keyNode = search(*tmp);
			if (keyNode)
				eraseNode(keyNode);
		}
		
	};

	size_type erase( const Key& key )
	{
		node_pointer keyNode = search(key);
		if (keyNode)
		{
			eraseNode(keyNode);
			return 1;
		}
		return 0;
	};

	void swap( set& other )
	{
		size_type sizeswap = this->_size;
		value_compare cmpswap = this->_cmp;
		allocator_type allocswap = this->_alloc;
		node_pointer rootswap = this->_root;
		node_pointer endswap = this->_end;
		this->_size = other._size;
		this->_cmp = other._cmp;
		this->_alloc = other._alloc;
		this->_root = other._root;
		this->_end = other._end;
		other._size = sizeswap;
		other._cmp = cmpswap;
		other._alloc = allocswap;
		other._root = rootswap;
		other._end = endswap;
	};

	/////////////////////////////////////////////////////
	// Lookup:
	/////////////////////////////////////////////////////

	size_type count( const Key& key ) const
	{
		node_pointer ret = search(key);
		if (!ret)
			return 0;
		return 1;
	};

	iterator find( const Key& key )
	{
		node_pointer ret = search(key);
		if (!ret)
			return end();
		return iterator(ret);
	};

	const_iterator find( const Key& key ) const
	{
		node_pointer ret = search(key);
		if (!ret)
			return end();
		return const_iterator(ret);
	};

	ft::pair<iterator,iterator> equal_range( const Key& key )
	{
		return ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));
	};

	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
	{
		return ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
	};

	iterator lower_bound( const Key& key )
	{
		Compare lessfunc;
		iterator ret = begin();
		while (ret != end() && lessfunc(*ret, key))
			++ret;
		return ret;
	};

	const_iterator lower_bound( const Key& key ) const
	{
		Compare lessfunc;
		const_iterator ret = begin();
		while (ret != end() && lessfunc(*ret, key))
			++ret;
		return ret;
	};

	iterator upper_bound( const Key& key )
	{
		Compare lessfunc;
		iterator ret = begin();
		while (ret != end() && !lessfunc(key, *ret))
			++ret;
		return ret;
	};

	const_iterator upper_bound( const Key& key ) const
	{
		Compare lessfunc;
		const_iterator ret = begin();
		while (ret != end() && !lessfunc(key, *ret))
			++ret;
		return ret;
	};	
	
	/////////////////////////////////////////////////////
	// Observers:
	/////////////////////////////////////////////////////

	key_compare key_comp() const
	{
		return key_compare();
	};
	
	value_compare value_comp() const
	{
		return value_compare(key_compare());
	};

private:
	size_type			_size;
	value_compare		_cmp;
	allocator_type		_alloc;
	allocator_rebind	_alloc_node;
	node_pointer		_root;
	node_pointer		_end;

	/////////////////////////////////////////////////////
	// Red Black Tree managing tools:
	/////////////////////////////////////////////////////

	node_pointer search( const Key & key ) const
	{
		if (_root != _end)
		{
			node_pointer	search = _root;
			while (search != _end)
			{
				if (_cmp(key, *search->pair))
					search = search->left;
				else if (_cmp(*search->pair, key))
					search = search->right;
				else
					return search;
			}
		}
		return NULL;
	}
	
	void leftRotate(node_pointer oldup)
	{
		node_pointer newup = oldup->right;

		oldup->right = _end;
		if (newup->left != _end)
		{
			oldup->right = newup->left;
			newup->left->parent = oldup;
		}
		if (oldup == _root)
			_root = newup;
		else if (isLeft(oldup))
			oldup->parent->left = newup;
		else
			oldup->parent->right = newup;
		newup->parent = oldup->parent;
		oldup->parent = newup;
		newup->left = oldup;
	}

	void rightRotate(node_pointer oldup)
	{
		node_pointer newup = oldup->left;

		oldup->left = _end;
		if (newup->right != _end)
		{
			oldup->left = newup->right;
			newup->right->parent = oldup;
		}
		if (oldup == _root)
			_root = newup;
		else if (isLeft(oldup))
			oldup->parent->left = newup;
		else
			oldup->parent->right = newup;
		newup->parent = oldup->parent;
		oldup->parent = newup;
		newup->right = oldup;
	}

	node_pointer gp(node_pointer grandchild)
	{
		return grandchild->parent->parent;
	}

	node_pointer uncle(node_pointer nephew)
	{
		return gp(nephew)->right == nephew->parent ? gp(nephew)->left : gp(nephew)->right;
	}

	node_pointer returnSibling(node_pointer node, node_pointer parent)
	{
		return parent->left == node ? parent->right : parent->left;
	}

	bool isLeft(node_pointer node)
	{
		return node->parent->left == node;
	}

	bool isRed(node_pointer node)
	{
		return node->color == RED;
	}

	void swapColor(node & lhs, node & rhs)
	{
		bool swap = lhs.color;
		lhs.color = rhs.color;
		rhs.color = swap;
	}

	void maintainAfterInsert(node_pointer current)
	{
		if (_root == current)
			current->color = BLACK;
		else if (current->color == RED && current->parent->color == RED)
		{
			if (uncle(current)->color == RED)
			{
				current->parent->color = BLACK;
				uncle(current)->color = BLACK;
				gp(current)->color = RED;
				maintainAfterInsert(gp(current));
			}
			else
			{
				if (isLeft(current->parent) && isLeft(current))
				{
					swapColor(*current->parent, *gp(current));
					rightRotate(gp(current));
					maintainAfterInsert(current->parent);
				}
				else if (!isLeft(current->parent) && !isLeft(current))
				{
					swapColor(*current->parent, *gp(current));
					leftRotate(gp(current));
					maintainAfterInsert(current->parent);
				}	
				else if (isLeft(current->parent) && !isLeft(current))
				{
					leftRotate(current->parent);
					swapColor(*current->parent, *current);
					rightRotate(current->parent);
					maintainAfterInsert(current);
				}	
				else if (!isLeft(current->parent) && isLeft(current))
				{
					rightRotate(current->parent);
					swapColor(*current->parent, *current);
					leftRotate(current->parent);
					maintainAfterInsert(current);
				}	
			}
		}
	}

	node_pointer initNewNode(const value_type & data)
	{
		node_pointer newNode = _alloc_node.allocate(1);
		newNode->parent = NULL;
		newNode->left = _end;
		newNode->right = _end;
		newNode->pair = _alloc.allocate(1);
		_alloc.construct(newNode->pair, data);
		return newNode;
	}

	node_pointer insertNode(node_pointer begin, node_pointer newNode, bool * ret)
	{
		bool bigger = true;
		if (_root == _end)
			_root = newNode;
		else
		{
			node_pointer	endnode = begin;
			node_pointer	tmp = begin;
			while (endnode != _end)
			{
				tmp = endnode;

				if (_cmp(*newNode->pair, *endnode->pair))
				{
					bigger = false;
					endnode = endnode->left;
				}
				else if (_cmp(*endnode->pair, *newNode->pair))
					endnode = endnode->right;
				else
				{
					*ret = false;
					_alloc.destroy(newNode->pair);
					_alloc.deallocate(newNode->pair, 1);
					_alloc_node.deallocate(newNode, 1);
					return endnode;
				}
			}
			if (_cmp(*tmp->pair, *newNode->pair))
				tmp->right = newNode;
			else
				tmp->left = newNode;
			newNode->parent = tmp;
			newNode->color = RED;
		}
		if (bigger)
			_end->parent = newNode;
		maintainAfterInsert(newNode);
		return newNode;
	}

	void clearFromRoot(node_pointer root)
	{
		if (root != _end)
		{
			if (root->left != _end)
				clearFromRoot(root->left);
			if (root->right != _end)	
				clearFromRoot(root->right);
			_alloc.destroy(root->pair);
			_alloc.deallocate(root->pair, 1);
			_alloc_node.deallocate(root, 1);
		}
	}

	void deleteNode(node_pointer deathNode)
	{
		_alloc.destroy(deathNode->pair);
		_alloc.deallocate(deathNode->pair, 1);
		_alloc_node.deallocate(deathNode, 1);
	}

	void maintainAfterErase(node_pointer current, node_pointer parent)
	{
		if (current == _root)
			current->color = BLACK;
		else
		{
			node_pointer sibling = returnSibling(current, parent);
			if (sibling != _end && !isRed(sibling) && (isRed(sibling->left) || isRed(sibling->right)))// sibling = black | at least of red
			{
				if (!isLeft(sibling) && isRed(sibling->right)) // sibling is right + right-child is RED
				{
					sibling->parent->color = BLACK;
					swapColor(*sibling, *sibling->right);
					leftRotate(parent);
				}
				else if (isLeft(sibling) && isRed(sibling->left)) // sibling is left + left-child is RED
				{
					sibling->parent->color = BLACK;
					swapColor(*sibling, *sibling->left);
					rightRotate(parent);
				}
				else if (isLeft(sibling) && !isRed(sibling->left)) // sibling is left + right-child is red BECAUSE left-child is Black
				{
					swapColor(*sibling, *sibling->right);
					leftRotate(sibling);
					maintainAfterErase(sibling, sibling->parent);
				}
				else if (!isLeft(sibling) && !isRed(sibling->right)) // sibling is right + left-child is red BECAUSE right is black
				{
					swapColor(*sibling, *sibling->left);
					rightRotate(sibling);
					maintainAfterErase(sibling, sibling->parent);
				}
			}
			else if (!isRed(sibling)) // sibling is black | both child are black
			{
				if (sibling != _end)
					sibling->color = RED;
				if (isRed(parent))
					parent->color = BLACK;
				else
					maintainAfterErase(parent, parent->parent);
			}
			else // sibling is red
			{
				sibling->color = BLACK;
				sibling->parent->color = RED;
				if (isLeft(sibling))
					rightRotate(sibling->parent);
				else
					leftRotate(sibling->parent);
				maintainAfterErase(current, parent);
			}
		}
	}

	void deleteParent(node_pointer parent, node_pointer child, node ** retChild) // No child /OR/ only 1 child
	{
		if (parent != _root && isLeft(parent))
		{
			if (child != _end)
			{
				*retChild = child;
				child->parent = parent->parent;
				parent->parent->left = child;
			}
			else
				parent->parent->left = _end;
		}
		else if (parent != _root)
		{
			if (child != _end)
			{
				*retChild = child;
				child->parent = parent->parent;
				parent->parent->right = child;
			}
			else
				parent->parent->right = _end;
		}
		else
		{
			_root = child;
			child->parent = NULL;
			*retChild = child;
		}
	}

	node_pointer getVictim(node_pointer dementor, node ** retChild)
	{
		if (dementor->left != _end && dementor->right != _end)
		{
			node_pointer victim = dementor;
			victim = victim->left;
			while (victim->right != _end)
				victim = victim->right;
			_alloc.destroy(dementor->pair);
			_alloc.construct(dementor->pair, *victim->pair);
			if (victim->left != _end)
				deleteParent(victim, victim->left, retChild);
			else
				deleteParent(victim, _end, retChild);
			return victim;
		}
		else if (dementor->left != _end && dementor->right == _end)
			deleteParent(dementor, dementor->left, retChild);
		else if (dementor->left == _end && dementor->right != _end)
			deleteParent(dementor, dementor->right, retChild);
		else if (dementor->left == _end && dementor->right == _end)
			deleteParent(dementor, _end, retChild);
		return dementor;
	}

	void eraseNode(node_pointer deathNode)
	{
		node_pointer child = _end;
		deathNode = getVictim(deathNode, &child);
		
		if (_end->parent == deathNode)
			_end->parent = deathNode->parent;
		if (child == _root)
			deleteNode(deathNode);
		else if (deathNode->color == RED || child->color == RED)
		{
			deleteNode(deathNode);
			child->color = BLACK;
		}
		else // child is DOUBLE BLACK
		{
			maintainAfterErase(child, deathNode->parent);
			deleteNode(deathNode);
		}
		--_size;
	};

	/////////////////////////////////////////////////////
	// DEBUG FUNCTIONS:
	/////////////////////////////////////////////////////

	void printTree(node_pointer root, std::string indent, bool last) const
	{
		if (root != _end)
		{
			std::cout << indent;
			if (last)
			{
				std::cout << "R----";
				indent += "   ";
			} 
			else 
			{
				std::cout << "L----";
				indent += "|  ";
			}
			std::string sColor = root->color ? "BLACK" : "RED";
			std::cout << *root->pair << "(" << sColor << ")" << std::endl;
			printTree(root->left, indent, false);
			printTree(root->right, indent, true);
		}
	}

	void printNode(node_pointer node) const
	{
		if (node == _end)
			std::cout << "Main	: key(END) | color:" << node->color << std::endl;
		else
		{
		std::cout << "Main	: key(" << *node->pair << ") | T(" << *node->pair << ") | color:" << node->color << std::endl;
		if (node->parent)
			std::cout << "Parent	: key(" << *node->parent->pair << ") | T(" << *node->parent->pair << ") | color:" << node->parent->color << std::endl;
		else
			std::cout << "Parent	: END" << std::endl;
		if (node->left != _end)
			std::cout << "Left	: key(" << *node->left->pair << ") | T(" << *node->left->pair << ") | color:" << node->left->color << std::endl;
		else
			std::cout << "Left	: END" << std::endl;
		if (node->right != _end)
			std::cout << "Right	: key(" << *node->right->pair << ") | T(" << *node->right->pair << ") | color:" << node->right->color << std::endl;
		else
			std::cout << "Right	: END" << std::endl;
		}
		std::cout << std::endl;
	}

	void main_like()
	{
		printTree(_root, "", false);
		std::cout << std::endl;
	}

};

template< typename Key, typename Compare, typename Allocator >
bool operator==(const set< Key, Compare, Allocator > & lhs, const set< Key, Compare, Allocator > & rhs)
{
	return 
	!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())
	&& !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
};

template< typename Key, typename Compare, typename Allocator >
bool operator!=(const set< Key, Compare, Allocator > & lhs, const set< Key, Compare, Allocator > & rhs)
{
	return !(lhs == rhs);
};

template< typename Key, typename Compare, typename Allocator >
bool operator<(const set< Key, Compare, Allocator > & lhs, const set< Key, Compare, Allocator > & rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};

template< typename Key, typename Compare, typename Allocator >
bool operator>(const set< Key, Compare, Allocator > & lhs, const set< Key, Compare, Allocator > & rhs)
{
	return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
};

template< typename Key, typename Compare, typename Allocator >
bool operator<=(const set< Key, Compare, Allocator > & lhs, const set< Key, Compare, Allocator > & rhs)
{
	return !(lhs > rhs);
};

template< typename Key, typename Compare, typename Allocator >
bool operator>=(const set< Key, Compare, Allocator > & lhs, const set< Key, Compare, Allocator > & rhs)
{
	return !(lhs < rhs);
};

template< class Key, class Compare, class Alloc >
void swap( ft::set< Key, Compare, Alloc > & lhs, ft::set< Key, Compare, Alloc >& rhs )
{
	lhs.swap(rhs);
};
}
#endif