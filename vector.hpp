/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:44:11 by ylee              #+#    #+#             */
/*   Updated: 2022/02/07 17:54:31 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // for allocator

namespace	ft
{
	template< typename T, typename Allocator = std::allocator<T> >
	class	vector
	{	
		typedef	T										value_type;
		typedef	Allocator								allocator_type;
		typedef	size_t									size_type;
		typedef	ptrdiff_t								difference_type;
		typedef	T&										reference;
		typedef	const T&								const_reference;
		typedef	Allocator::pointer						pointer;
		typedef	Allocator::const_pointer				const_pointer;
		typedef	ft::random_access_iterator<T>			iterator;
		typedef	ft::random_access_iterator<const T>		const_iterator;
		typedef	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		allcator_type	alloc;
		value_type*		elements;
		value_type*		begin;
		value_type*		end;
		size_type		size;
		size_type		capacity;

	public:
		//constructor
		explicit	vector( const allocator_type& alloc = allocator_type<T>() )
		: alloc(alloc), elements(nullptr), begin(nullptr), end(nullptr), size(0), capacity(0)
		{}
		//val 에 있는 내용으로 초기화하여 생성
		explicit	vector( size_type n, const value_type& val = value_type(),
							const_allocator_type& alloc = allocator_type() )
		: alloc(alloc), size(n), capacity(n)
		{
			element = alloc.allocate(n);
			begin = elements;
			end = begin;
			for(int i = 0; i < n; i++, end++)
			{
				alloc.construct(end, val);
			}
		}
		//InputIter 의 first 부터 last 까지의 내용으로 초기화하여 생성
		template <typename InputIter>
		vector( InputIter first, InputIter last, 
				const allocator_type& alloc = allocator_type() )
		:alloc(alloc)
		{
			difference_type	diff = iterator::distance(first, last);
			elements = alloc.allocate(diff);
			size = static_cast<size_type>(diff);
			capacity = size;
			begin = elements;
			end = begin;
			for ( ; first != last ; end++, first++)
			{
				alloc.construct(end, *first);
			}
		}
		vector(const vector& copy)
		{
			*this = copy;
		}
		//assignation operator
		vector&	operator=(const vector& copy)
		{
			alloc = copy.alloc;
			size = copy.size;
			capacity = copy.capacity;
			elements = alloc.allocate(capacity);
			begin = elements;
			end = begin;
			for(size_type i = 0; i < size; i++, end++)
			{
				alloc.construct(end, copy.elements[i]);
			}
		}
		//destructor
		~vector()
		{
			alloc.deallocate(elements, capacity);
		}

		//member functions

		//	iterators
		iterator	begin() // first element 의 iterator 를 반환
		{
			return iterator(*begin) ;
		}
		const_iterator	begin() const
		{
			return const_iterator(*begin) ;
		}
		iterator	end()
		{
			return iterator(*end) ;
		}
		const_iterator	end() const
		{
			return const_iterator(*end) ;
		}
		reverse_iterator	rbegin()
		{
			return reverse_iterator(*end) ;
		}
		const_reverse_iterator	rbegin() const
		{
			return const_reverse_iterator(*end) ;
		}
		reverse_iterator	rend()
		{
			return reverse_iterator(*begin) ;
		}
		const_reverse_iterator	rend() const
		{
			return const_reverse_iterator(*begin) ;
		}

		//	capacity
		size_type	size() const
		{ return size ; } // 저장된 element 의 수
		size_type	max_size() const
		{ return alloc.max_size() ; } // 추가 allocate까지 최대로 가능한 사이즈. 실제 allocate 되어있는 최대 size는 capacity 이다. 혼동하지말기.
		void	resize(size_type cnt, value_type value = value_type())
		{
			if (max_size() < cnt)
				throw(std::length_error("ft::vector::resize length error"));
			value_type*	tmp = alloc.allocate(cnt, elements);
			if (size < cnt)
			{
				for (size_type i = size; i < cnt; i++)
				{
					alloc.construct(&tmp[i], value);
				}
			}
			else
				size = cnt ;
			alloc.deallocate(elements, capacity);
			elements = tmp ;
			capacity = cnt ;
		}
		size_type capacity() const  // allocate 되어있는 수
		{}

		bool empty() const
		{}
		void reserve( size_type new_cap )
		{}
		//	element access
		reference operator[]( size_type pos )
		{}
		const_reference operator[]( size_type pos ) const
		{}
		reference at( size_type pos )
		{}
		const_reference at( size_type pos ) const
		{}
		reference front() // first element 의 reference 를 반환
		{}
		const_reference front() const
		{}
		reference back()
		{}
		const_reference back() const
		{}
		value_type*	data() // first element 의 pointer 를 반환
		{
			if (size() == 0)
				return NULL ;
			return elements ;
		}
		const value_type*	data() const
		{
			if (size() == 0)
				return NULL ;
			return elements ;
		}
		//	modifier
		void assign( size_type count, const T& value )
		{}
		template< class InputIt >
		void assign( InputIt first, InputIt last )
		{}
		void push_back( const T& value )
		{}
		void pop_back()
		{}
		iterator insert( iterator pos, const T& value )
		{}
		void insert( iterator pos, size_type count, const T& value )
		{}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last )
		{}
		iterator erase( iterator pos )
		{}
		iterator erase( iterator first, iterator last )
		{}
		void swap( vector& other )
		{}
		void	clear()
		{}
		//	allcator
		allocator_type get_allocator() const
		{}
	};

	//non-member functions
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);


	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs);
}


#endif
