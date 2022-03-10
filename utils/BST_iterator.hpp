/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:48:04 by ylee              #+#    #+#             */
/*   Updated: 2022/03/10 22:09:19 by ylee             ###   ########.fr       */
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
		typedef	T	value_type;

		value_type	value;
		BST_Node*	parent;
		BST_Node*	left;
		BST_Node*	right;
		
		BST_Node()
		: value(value_type()), parent(nullptr), left(nullptr), right(nullptr)
		{}
		BST_Node(BST_Node* parent = nullptr, BST_Node* left = nullptr, BST_Node* right = nullptr)
		: value(value_type()), parent(parent), left(left), right(right)
		{}
		BST_Node(const value_type& value, BST_Node* parent = nullptr, BST_Node* left = nullptr, BST_Node* right = nullptr)
		: value(value_type(value)), parent(parent), left(left), right(right)
		{}
		BST_Node(const BST_Node& copy)
		{
			*this = copy;
		}
		BST_Node&	operator=(const BST_Node& copy)
		{
			value = copy.value;
			parent = copy.parent;
			left = copy.left;
			right = copy.right;
			return *this ;
		}
		virtual ~BST_Node(){}

		value_type	operator*()
		{
			return value ;
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

	template <typename T>
	std::ostream&	operator<<(std::ostream& out, const BST_Node<T>& node)
	{
		out << node.value;
		return out ;
	}
	


	template<typename Node, typename Compare = ft::less<Node> >
	class	BST_iterator : ft::iterator<ft::bidirectional_iterator_tag, Node>
	{
	public:
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::value_type			value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Node>::difference_type	difference_type;
		typedef Node*			pointer;
		typedef Node&			reference;
	protected:
		pointer	curN ;
		pointer	endN ;
		Compare	comp ;
	public:
		BST_iterator()
		: curN(nullptr), endN(nullptr), comp(Compare())
		{}
		explicit	BST_iterator(pointer curN, pointer endN = nullptr, Compare comp = Compare())
		: curN(curN), endN(endN), comp(comp)
		{}
		BST_iterator( const BST_iterator& other )
		{ *this = other ; }
		~BST_iterator() {}
		BST_iterator&	operator=( const BST_iterator& other)
		{
			curN = other.curN ;
			endN = other.endN ;
			comp = other.comp ;
			return *this ;
		}
		pointer	base() const
		{
			return curN ;
		}
		reference			operator*() const
		{
			return *curN ;
		}
		pointer				operator->() const
		{
			return &(operator*()) ;
		}
		
		BST_iterator&	operator++()
		{
			pointer	tmp = curN;
			//std::cout << "this Node : " << tmp << "//";
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
				while (tmp != endN && comp(*tmp, *curN))
					tmp = tmp->parent ;
				curN = tmp ;
			}
			else
				curN = curN->right ;
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
			pointer	tmp = curN;
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
				while (tmp != endN && comp(*curN, *tmp))
					tmp = tmp->parent ;
				curN = tmp ;
			}
			else
				curN = curN->left ;
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
	template<typename Node>
	bool					operator==(const BST_iterator<Node>& lhs,
										const BST_iterator<Node>& rhs)
	{
		return *lhs.base() == *rhs.base() ;
	}
	template<typename Node>
	bool					operator!=(const BST_iterator<Node>& lhs,
										const BST_iterator<Node>& rhs)
	{
		return *lhs.base() != *rhs.base() ;
	}
	template<typename Node>
	bool					operator<(const BST_iterator<Node>& lhs,
										const BST_iterator<Node>& rhs)
	{
		return  *lhs.base() < *rhs.base() ;
	}
	template<typename Node>
	bool					operator<=(const BST_iterator<Node>& lhs,
										const BST_iterator<Node>& rhs)
	{
		return !(*rhs.base() < *lhs.base()) ;
	}
	template<typename Node>
	bool					operator>(const BST_iterator<Node>& lhs,
										const BST_iterator<Node>& rhs)
	{
		return *rhs.base() < *lhs.base() ;
	}
	template<typename Node>
	bool					operator>=(const BST_iterator<Node>& lhs,
										const BST_iterator<Node>& rhs)
	{
		return !(*lhs.base() < *rhs.base()) ;
	}
	
}


#endif

