/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:44:11 by ylee              #+#    #+#             */
/*   Updated: 2022/03/11 00:44:36 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "./utils/binary_search_tree.hpp"
# include "./utils/pair.hpp"
# include "./utils/less.hpp"
# include "./utils/BST_iterator.hpp"
# include "./utils/reverse_iterator.hpp"

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
		typedef typename ft::binary_search_tree<value_type>::iterator		iterator;
		typedef typename ft::binary_search_tree<value_type>::const_iterator	const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;
	
		//ft::pair 구조체 두개를 받아 둘의 key 를 비교하는 클래스. key 를 인자로 받아 비교하는 것은 ft::less<key> 에서 처리하고 구조체를 받아 비교할 때에는 이 클래스에서 처리한다.
		class value_compare
		: ft::binary_function<value_type, value_type, bool>
		{
		protected:
			Compare		comp; // ft::less<Key> 을 저장한다.
			value_compare(Compare c = key_compare()) : comp(c) {}
			~value_compare(){}
		public:
			bool    operator()(const value_type& lhs, const value_type& rhs)
			{
				//pair 구조체를 받은 뒤 ft::less<Key> 에서 lhs, rhs 의 key 값을 비교한다.
				//pair 는 struct 이므로 first 는 public 이다.
				return comp(lhs.first, rhs.first); 
			}
		};
		
	private:
		ft::binary_search_tree<value_type, value_compare >    tree;

	public:
		map(Key& key = Key(), T& mapped = T()):tree(value_type(key,mapped)) {}
		// explicit map( const Compare& comp, const Allocator& alloc = Allocator() )
		// {}
		// template< class InputIt >
		// map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
		// {}
		// map( const map& copy )
		// {}
		// ~map(){}
		// map&    operator=(const map& copy)
		// {}
		allocator_type get_allocator() const;
		T& at( const Key& key );
		const T& at( const Key& key ) const;
		T& operator[]( const Key& key );
		iterator begin(){return (this->tree).begin() ; }
		const_iterator begin() const;
		iterator end(){ return	(this->tree).end() ; }
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void clear(); 
		ft::pair<iterator, bool> insert( const value_type& value )
		{return	tree.insert(value) ; }
		template< class InputIt >
		void insert( InputIt first, InputIt last );
		
		void erase( iterator pos ); 
		void erase( iterator first, iterator last );
		size_type erase( const Key& key );
		void swap( map& other );
		size_type count( const Key& key ) const;
		iterator find( const Key& key )
		{
			return	tree.find(value_type(key)) ;
		}
		const_iterator find( const Key& key ) const;
		ft::pair<iterator,iterator> equal_range( const Key& key );
		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
		iterator lower_bound( const Key& key );
		const_iterator lower_bound( const Key& key ) const;
		iterator upper_bound( const Key& key );
		const_iterator upper_bound( const Key& key ) const;
		key_compare key_comp() const;
		typename ft::map<Key, T>::value_compare value_comp() const
		{
			return value_compare() ;
		}
		template< class K, class U, class Comp, class Al >
		friend bool operator==( const ft::map<K,U,Comp,Al>& lhs, const ft::map<K,U,Comp,Al>& rhs ); 
	};
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ); 
	
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs );

}

#endif
