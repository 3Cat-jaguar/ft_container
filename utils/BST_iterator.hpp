/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:48:04 by ylee              #+#    #+#             */
/*   Updated: 2022/03/22 16:19:47 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP

# include <iostream>
# include "./less.hpp"
# include "./iterator_traits.hpp"

namespace	ft
{
	template<typename T>
	struct BST_Node
	{
		typedef	T		value_type;
		typedef	int		size_type;

		value_type	value;
		BST_Node*	parent;
		BST_Node*	left;
		BST_Node*	right;
		size_type	height;
		
		BST_Node()
		: value(value_type()), parent(nullptr), left(nullptr), right(nullptr), height(0)
		{}
		BST_Node(BST_Node* parent = nullptr, BST_Node* left = nullptr, BST_Node* right = nullptr)
		: value(value_type()), parent(parent), left(left), right(right), height(0)
		{}
		BST_Node(const value_type& value, BST_Node* parent = nullptr, BST_Node* left = nullptr, BST_Node* right = nullptr)
		: value(value_type(value)), parent(parent), left(left), right(right), height(0)
		{}
		BST_Node(const BST_Node& copy)
		:value(copy.value), parent(copy.parent), left(copy.left), right(copy.right), height(copy.height)
		{}
		BST_Node&	operator=(const BST_Node& copy)
		{
			value = copy.value;
			parent = copy.parent;
			left = copy.left;
			right = copy.right;
			height = copy.height ;
			return *this ;
		}
		virtual ~BST_Node(){}

		value_type	operator*()
		{
			return value ;
		}
		
		BST_Node&	copyExceptValue(const BST_Node& copy)
		{
			parent = copy.parent;
			left = copy.left;
			right = copy.right;
			height = copy.height;
			return *this ;
		}
		
		bool	operator==(const BST_Node& other)
		{
			return	value == other.value ;
		}
		
		bool	operator!=(const BST_Node& other)
		{
			return	value != other.value ;
		}

		bool	operator<(const BST_Node& other)
		{
			return value < other.value ;
		}

		bool	operator<=(const BST_Node& other)
		{
			return	value <= other.value ;
		}

		bool	operator>(const BST_Node& other)
		{
			return	value > other.value ;
		}

		bool	operator>=(const BST_Node& other)
		{
			return	value >= other.value ;
		}
	};
	


	template<typename T>
	bool	operator==(const BST_Node<T>& lhs, const BST_Node<T>& rhs)
	{
		return	lhs.value == rhs.value ;
	}

	template<typename T>
	bool	operator!=(const BST_Node<T>& lhs, const BST_Node<T>& rhs)
	{
		return	lhs.value != rhs.value ;
	}

	template<typename T>
	bool	operator> (const BST_Node<T>& lhs, const BST_Node<T>& rhs)
	{
		return	lhs.value >  rhs.value ;
	}

	template<typename T>
	bool	operator>=(const BST_Node<T>& lhs, const BST_Node<T>& rhs)
	{
		return	lhs.value >= rhs.value ;
	}

	template<typename T>
	bool	operator< (const BST_Node<T>& lhs, const BST_Node<T>& rhs)
	{
		return	lhs.value <  rhs.value ;
	}

	template<typename T>
	bool	operator<=(const BST_Node<T>& lhs, const BST_Node<T>& rhs)
	{
		return	lhs.value <= rhs.value ;
	}
	
	template<typename Node, typename Compare>
	class	BST_const_iterator;

	template<typename Node, typename Compare = ft::less<Node> >
	class	BST_iterator : ft::iterator<ft::bidirectional_iterator_tag, Node>
	{
	public:
		typedef	typename Node::value_type	value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer			pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
	// protected:
		Node*	curN ;
		Node*	endN ;
		Compare	comp ;
	// public:
		BST_iterator()
		: curN(nullptr), endN(nullptr), comp(Compare())
		{}
		explicit	BST_iterator(Node* curN, Node* endN = nullptr, Compare comp = Compare())
		: curN(curN), endN(endN), comp(comp)
		{}
		BST_iterator( const BST_iterator& other )
		{ *this = other ; }
		virtual ~BST_iterator() {}
		BST_iterator&	operator=( const BST_iterator& other)
		{
			curN = other.curN ;
			endN = other.endN ;
			comp = other.comp ;
			return *this ;
		}
		Node*	base() const
		{
			return curN ;
		}
		reference			operator*() const
		{
			return curN->value ;
		}
		pointer				operator->() const
		{
			return &(curN->value) ;
		}
		
		BST_iterator&	operator++()
		{
			Node*	tmp = curN;
			if (curN->right != endN)
			{
				tmp = curN->right ;
				while (tmp->left != endN)
					tmp = tmp->left ;
				curN = tmp ;
			}
			else if (curN != endN)
			{
				tmp = curN->parent ;
				while (tmp != endN && comp(tmp->value.first, curN->value.first))
					tmp = tmp->parent ;
				curN = tmp ;
			}
			return *this ;
		}
		BST_iterator	operator++(int)
		{
			BST_iterator	tmp = *this ;
			operator++() ;
			return tmp ;
		}
		BST_iterator&	operator--()
		{
			Node*	tmp = curN;
			if (curN->left != endN)
			{
				tmp = curN->left ;
				while (tmp->right != endN)
					tmp = tmp->right ;
				curN = tmp ;
			}
			else if (curN != endN)
			{
				tmp = curN->parent ;
				while (tmp != endN && comp(curN->value.first, tmp->value.first))
					tmp = tmp->parent ;
				curN = tmp ;
			}
			else // curN == endN 일 때 제일 큰 node 로 이동.
				curN = curN->parent ;
			return *this ;
		}
		BST_iterator	operator--(int)
		{
			BST_iterator	tmp = *this ;
			operator--() ;
			return tmp ;
		}

	};
	//non-member function operators
	template<typename Node, typename Compare>
	bool					operator==(const BST_iterator<Node, Compare>& lhs, const BST_iterator<Node, Compare>& rhs)
	{
		return lhs.base() == rhs.base() ;
	}
	template<typename Node, typename Compare>
	bool					operator!=(const BST_iterator<Node, Compare>& lhs, const BST_iterator<Node, Compare>& rhs)
	{
		return !(lhs == rhs) ;
	}

	//compare iterator and const iterator
	template<typename Node, typename Compare>
	bool					operator==(const BST_iterator<Node, Compare>& lhs, const BST_const_iterator<Node, Compare>& rhs)
	{
		return lhs.base() == rhs.base() ;
	}
	template<typename Node, typename Compare>
	bool					operator!=(const BST_iterator<Node, Compare>& lhs, const BST_const_iterator<Node, Compare>& rhs)
	{
		return !(lhs == rhs) ;
	}


	template<typename Node, typename Compare = ft::less<Node> >
	class	BST_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, Node>
	{
	public:
		typedef	typename Node::value_type	value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, const value_type>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, const value_type>::difference_type	difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, const value_type>::pointer			pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, const value_type>::reference			reference;
	// protected:
		Node*	curN ;
		Node*	endN ;
		Compare	comp ;
	// public:
		BST_const_iterator()
		: curN(nullptr), endN(nullptr), comp(Compare())
		{}
		explicit	BST_const_iterator(Node* curN, Node* endN = nullptr, Compare comp = Compare())
		: curN(curN), endN(endN), comp(comp)
		{}
		BST_const_iterator( const BST_const_iterator& other )
		{ *this = other ; }
		BST_const_iterator( const BST_iterator<Node, Compare>& other )
		{
			curN = other.curN ;
			endN = other.endN ;
			comp = other.comp ;
		}
		
		virtual ~BST_const_iterator() {}
		BST_const_iterator&	operator=( const BST_const_iterator& other)
		{
			curN = other.curN ;
			endN = other.endN ;
			comp = other.comp ;
			return *this ;
		}
		Node*	base() const
		{
			return curN ;
		}
		reference			operator*() const
		{
			return curN->value ;
		}
		pointer				operator->() const
		{
			return &(curN->value) ;
		}
		
		BST_const_iterator&	operator++()
		{
			Node*	tmp = curN;
			if (curN->right != endN)
			{
				tmp = curN->right ;
				while (tmp->left != endN)
					tmp = tmp->left ;
				curN = tmp ;
			}
			else if (curN != endN)
			{
				tmp = curN->parent ;
				while (tmp != endN && comp(tmp->value.first, curN->value.first))
					tmp = tmp->parent ;
				curN = tmp ;
			}
			return *this ;
		}
		BST_const_iterator	operator++(int)
		{
			BST_const_iterator	tmp = *this ;
			operator++() ;
			return tmp ;
		}
		BST_const_iterator&	operator--()
		{
			Node*	tmp = curN;
			if (curN->left != endN)
			{
				tmp = curN->left ;
				while (tmp->right != endN)
					tmp = tmp->right ;
				curN = tmp ;
			}
			else if (curN != endN)
			{
				tmp = curN->parent ;
				while (tmp != endN && comp(curN->value.first, tmp->value.first))
					tmp = tmp->parent ;
				curN = tmp ;
			}
			else
				curN = curN->parent ;
			return *this ;
		}
		BST_const_iterator	operator--(int)
		{
			BST_const_iterator	tmp = *this ;
			operator--() ;
			return tmp ;
		}
	};
	//non-member function operators
	template<typename Node, typename Compare>
	bool					operator==(const BST_const_iterator<Node, Compare>& lhs, const BST_const_iterator<Node, Compare>& rhs)
	{
		return lhs.base() == rhs.base() ;
	}
	template<typename Node, typename Compare>
	bool					operator!=(const BST_const_iterator<Node, Compare>& lhs, const BST_const_iterator<Node, Compare>& rhs)
	{
		return !(lhs == rhs) ;
	}
	
	//compare const iterator and iterator
	template<typename Node, typename Compare>
	bool					operator==(const BST_const_iterator<Node, Compare>& lhs, const BST_iterator<Node, Compare>& rhs)
	{
		return lhs.base() == rhs.base() ;
	}
	template<typename Node, typename Compare>
	bool					operator!=(const BST_const_iterator<Node, Compare>& lhs, const BST_iterator<Node, Compare>& rhs)
	{
		return !(lhs == rhs) ;
	}
}


#endif

