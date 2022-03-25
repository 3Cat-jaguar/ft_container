/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:44:11 by ylee              #+#    #+#             */
/*   Updated: 2022/03/25 22:35:43 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <stdexcept>
# include "./utils/binary_search_tree.hpp"
# include "./utils/pair.hpp"
# include "./utils/less.hpp"
# include "./utils/BST_iterator.hpp"
# include "./utils/reverse_iterator.hpp"
# include "./utils/enable_if.hpp"
# include "./utils/is_integral.hpp"
# include "./utils/equal.hpp"
# include "./utils/lexicographical_compare.hpp"

namespace	ft
{
	template< typename Key, typename T, typename Compare = ft::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef typename ft::pair<const Key, T>								value_type;
		typedef size_t												size_type;
		typedef ptrdiff_t											difference_type;
		typedef Compare												key_compare;
		typedef Allocator											allocator_type;
		typedef value_type&											reference;
		typedef const value_type&									const_reference;
		typedef typename Allocator::pointer									pointer;
		typedef typename Allocator::const_pointer							const_pointer;
		typedef typename ft::binary_search_tree<value_type, Compare>::iterator		iterator;
		typedef typename ft::binary_search_tree<value_type, Compare>::const_iterator	const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;
	
		class value_compare
		: ft::binary_function<value_type, value_type, bool>
		{
		friend	class ft::map<Key, T, Compare, Allocator>;
		protected:
			Compare		comp; // ft::less<Key> 을 저장한다.
			value_compare(Compare c) : comp(c) {}
		public:
			bool    operator()(const value_type& lhs, const value_type& rhs)
			{
				return comp(lhs.first, rhs.first); 
			}
		};
		
	private:
		allocator_type			alloc;
		key_compare				comp;
	// public:
		ft::binary_search_tree<value_type, Compare>    tree;

	public:
		map()
		: alloc(Allocator()), comp(Compare())
		{}
		
		explicit map( const Compare& comp, const Allocator& alloc = Allocator() )
		: alloc(alloc), comp(comp)
		{
			tree = ft::binary_search_tree<value_type, Compare>(comp);
		}
		
		template< class InputIt >
		map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
		: alloc(alloc), comp(comp)
		{
			tree = ft::binary_search_tree<value_type, Compare>(comp);
			tree.insert(first, last) ;
		}
		
		map( const map& copy )
		: alloc(copy.alloc), comp(copy.comp)
		{
			tree = copy.tree;
		}
		
		~map()
		{
			clear();
		}
		
		map&    operator=(const map& copy)
		{
			alloc = copy.alloc;
			comp = copy.comp;
			tree = copy.tree;
			return *this ;
		}
		
		allocator_type get_allocator() const
		{
			return	alloc ;
		}
		
		T& at( const Key& key )
		{
			iterator	k = find(key);
			if (k == end())
				throw (std::out_of_range("not found key") ) ;
			return	k->second ;
		}
		
		const T& at( const Key& key ) const
		{
			iterator	k = find(key);
			if (k == end())
				throw (std::out_of_range("not found key") ) ;
			return	k->second ;
		}
		
		T& operator[]( const Key& key )
		{
			iterator	k = find(key);
			if (k == end())
			{
				k = insert(value_type(key)).first;
			}
			return	k->second ;
		}
		
		iterator begin()
		{
			return iterator(tree.beginNode(), tree.endNode()) ;
		}
		
		const_iterator begin() const
		{
			return	const_iterator(tree.beginNode(), tree.endNode()) ;
		}
		
		iterator end()
		{
			return	tree.end() ;
		}
		
		const_iterator end() const
		{
			return	const_iterator(tree.endN, tree.endN) ;
		}
		
		reverse_iterator rbegin()
		{
			return	reverse_iterator(end()) ;
		}
		
		const_reverse_iterator rbegin() const
		{
			return	const_reverse_iterator(end()) ;
		}
		
		reverse_iterator rend()
		{
			return	reverse_iterator(begin()) ;
		}
		
		const_reverse_iterator rend() const
		{
			return	reverse_iterator(begin()) ;
		}
		
		bool empty() const
		{
			if (begin() == end())
				return true ;
			return false ;
		}
		size_type size() const
		{
			return	tree.size() ;
		}
		size_type max_size() const
		{
			return	tree.max_size() ;
		}
		
		void clear()
		{
			tree.clear();
		}
		
		ft::pair<iterator, bool> insert( const value_type& value )
		{
			return	tree.insert(value) ;
		}

		iterator insert( iterator hint, const value_type& value )
		{
			return	tree.insert(hint, value) ;
		}
		
		template< class InputIt >
		void insert( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr )
		{
			tree.insert(first, last) ;
		}
		
		void erase( iterator pos )
		{
			tree.erase(pos) ;
		}
		
		void erase( iterator first, iterator last )
		{
			tree.erase(first, last) ;
		}
		
		size_type erase( const Key& key )
		{
			return	tree.erase(value_type(key)) ;
		}
		
		void swap( map& other )
		{
			tree.swap(other.tree);
		}
		
		size_type count( const Key& key ) const
		{
			return	tree.count(value_type(key)) ;
		}
		
		iterator find( const Key& key )
		{
			return	tree.find(value_type(key)) ;
		}
		
		const_iterator find( const Key& key ) const
		{
			iterator result = tree.find(value_type(key));	
			return	const_iterator(result) ;
		}
		
		ft::pair<iterator,iterator> equal_range( const Key& key )
		{
			return	tree.equal_range(value_type(key)) ;
		}
		
		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
		{
			return	tree.equal_range(value_type(key)) ;
		}
		
		iterator lower_bound( const Key& key )
		{
			return	tree.lower_bound(value_type(key)) ;
		}
		
		const_iterator lower_bound( const Key& key ) const
		{
			return	tree.lower_bound(value_type(key)) ;
		}
		
		iterator upper_bound( const Key& key )
		{
			return	tree.upper_bound(value_type(key)) ;
		}
		
		const_iterator upper_bound( const Key& key ) const
		{
			return	tree.upper_bound(value_type(key)) ;
		}
		
		key_compare key_comp() const
		{
			return comp ;
		}
		
		value_compare value_comp() const
		{
			return value_compare() ;
		}
		
	};
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return false ;
		return	ft::equal(lhs.begin(), lhs.end(), rhs.begin()) ;
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs) ;
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator< ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return	ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) ;
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return	!(rhs < lhs);
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator> ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return	(rhs < lhs) ;
	}
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return	!( lhs < rhs ) ;
	}
	
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}

}

#endif
