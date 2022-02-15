/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:44:11 by ylee              #+#    #+#             */
/*   Updated: 2022/02/15 23:31:43 by ylee             ###   ########.fr       */
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
		value_type*		end_capacity;
		size_type		size;
		size_type		capacity;

	public:
		//constructor
		explicit	vector( const allocator_type& alloc = allocator_type<T>() )
		: alloc(alloc), elements(nullptr), begin(nullptr), end(nullptr), end_capacity(nullptr), size(0), capacity(0)
		{}
		//val 에 있는 내용으로 초기화하여 생성
		explicit	vector( size_type n, const value_type& val = value_type(), const_allocator_type& alloc = allocator_type() )
		: alloc(alloc), size(n), capacity(0)
		{
			while (capacity < size)
			{
				size_type new_capacity = (capacity * 2 > 0) ? (capacity * 2) : 1;
				capacity = new_capacity ;
			}
			element = alloc.allocate(capacity);
			begin = elements;
			end_capacity = begin + capacity ;
			end = begin;
			for(int i = 0; i < n; i++, end++)
			{
				alloc.construct(end, val);
			}
		}
		//InputIter 의 first 부터 last 까지의 내용으로 초기화하여 생성
		template <typename InputIter>
		vector( InputIter first, InputIter last, const allocator_type& alloc = allocator_type() )
		:alloc(alloc)
		{
			difference_type	diff = iterator::distance(first, last);
			size = static_cast<size_type>(diff);
			capacity = 0 ;
			while (capacity < size)
			{
				size_type new_capacity = (capacity * 2 > 0) ? (capacity * 2) : 1;
				capacity = new_capacity ;
			}
			element = alloc.allocate(capacity);
			begin = elements;
			end_capacity = begin + capacity ;
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
			end_capacity = begin + capacity ;
			end = begin;
			for(size_type i = 0; i < size; i++, end++)
			{
				alloc.construct(end, value_type(copy.elements[i]));
			}
		}
		//destructor
		~vector()
		{
			clear();
			alloc.deallocate(elements, capacity);
		}

		//member functions

		//	iterators
		iterator	begin() // first element 의 iterator 를 반환
		{
			return iterator(begin) ;
		}
		const_iterator	begin() const
		{
			return const_iterator(begin) ;
		}
		iterator	end()
		{
			return iterator(end) ;
		}
		const_iterator	end() const
		{
			return const_iterator(end) ;
		}
		reverse_iterator	rbegin()
		{
			return reverse_iterator(end()) ;
		}
		const_reverse_iterator	rbegin() const
		{
			return const_reverse_iterator(end()) ;
		}
		reverse_iterator	rend()
		{
			return reverse_iterator(begin()) ;
		}
		const_reverse_iterator	rend() const
		{
			return const_reverse_iterator(begin()) ;
		}

		//	capacity
		size_type	size() const
		{
			return size ;
		} // 저장된 element 의 수
		size_type	max_size() const
		{
			return alloc.max_size();
		} // 추가 allocate까지 최대로 가능한 사이즈. 실제 allocate 되어있는 최대 size는 capacity 이다. 혼동하지말기.
		void	resize(size_type cnt, value_type value = value_type())
		{
			if (size > cnt) // 사이즈를 줄이는 경우
			{
				while (size != cnt)
					pop_back(); // 뒤에서부터 erase 처리
			}
			else if (size > cnt) // 사이즈를 키우는 경우
			{
				while (size != cnt)
					push_back(value); // 뒤에서부터 insert 처리. 공간 부족하면 reserve
			}
		}
		size_type capacity() const  // allocate 되어있는 수
		{
			return capacity ;
		}

		bool empty() const
		{
			if (size == 0)
				return true ;
			return false ;
		}
		void reserve( size_type new_cap )
		{
			if (new_cap <= capacity)
				return ;
			if (max_size() < new_cap)
				throw ( std::length_error("vector::reserve") ) ;
			value_type* tmp = alloc.allocate(new_cap);
			for(int i = 0; i < size ; i++)
			{
				tmp[i] = elements[i];
			}
			alloc.deallocate(elements, capacity);
			capacity = new_cap;
			elements = tmp;
			begin = elements;
			end = begin + size ;
			end_capacity = begin + capacity ;
		}
		//	element access
		reference operator[]( size_type pos )
		{
			return elements[pos] ;
		}
		const_reference operator[]( size_type pos ) const
		{}
		reference at( size_type pos )
		{
			if (pos < size)
				throw(std::out_of_range("vector::at"));
			return elements[pos] ;
		}
		const_reference at( size_type pos ) const
		{
			if (pos < size)
				throw(std::out_of_range("vector::at"));
			return elements[pos] ;
		}
		reference front() // first element 의 reference 를 반환
		{
			if !begin
				return value_type() ;
			return *begin ;
		}
		const_reference front() const
		{
			if !begin
				return value_type() ;
			return *begin ;
		}
		reference back()
		{
			if (begin == end)
				return value_type() ;
			return *(begin + size - 1) ;
		}
		const_reference back() const
		{
			if (begin == end)
				return value_type() ;
			return *(begin + size - 1) ;
		}
		value_type*	data() // first element 의 pointer 를 반환
		{
			return elements ;
		}
		const value_type*	data() const
		{
			return elements ;
		}
		//	modifier
		void assign( size_type count, const T& value )
		{
			clear();
			if (capacity < count)
			{
				alloc.deallocate(elements, capacity);
				size_type new_capacity ;
				while (capacity < count)
				{
					new_capacity = (capacity * 2 > 0) ? (capacity * 2) : 1;
					capacity = new_capacity ;
				}
				elements = alloc.allocate(capacity);
				begin = elements;
				end_capacity = begin + capacity ;
			}
			end = begin ;
			for (int i = 0; i < count; i++, end++)
			{
				alloc.construct(end, value_type(value));
			}
		}
		template< class InputIt >
		void assign( InputIt first, InputIt last )
		{
			clear ;
			difference_type count = iterator::distance(first, last);
			if (capacity < count)
			{
				alloc.deallocate(elements, capacity);
				size_type new_capacity ;
				while (capacity < count)
				{
					new_capacity = (capacity * 2 > 0) ? (capacity * 2) : 1;
					capacity = new_capacity ;
				}
				elements = alloc.allocate(capacity);
				begin = elements;
				end_capacity = begin + capacity ;
			}
			end = begin ;
			for ( ; first != last ; end++, first++)
			{
				alloc.construct(end, value_type(*first));
			}
		}
		void push_back( const T& value )
		{
			insert(end(), value);
		}
		void pop_back()
		{
			erase(end() - 1);
		}
		iterator insert( iterator pos, const T& value )
		{
			if (size + 1 < capacity)
			{
				size_type	new_cap = (capacity * 2 > 0) ? (capacity * 2) : 1;
				reserve(new_cap);
			}
			value_type* cur = end;
			if (cur < &(*pos))
				pos = end();
			while (cur > &(*pos))
			{
				alloc.construct(cur, *(cur - 1));
				cur--;
				alloc.destroy(cur);
			}
			alloc.construct(cur, value);
			size += 1;
			end++;
		}
		void insert( iterator pos, size_type count, const T& value )
		{
			while (size + count < capacity)
			{
				size_type	new_cap = (capacity * 2 > 0) ? (capacity * 2) : 1;
				reserve(new_cap);
			}
			value_type* cur = end;
			if (cur < &(*pos))
				pos = end();
			while (cur > &(*pos))
			{
				alloc.construct(cur + count - 1, *(cur - 1));
				cur--;
				alloc.detroy(cur);
			}
			for (size_type i = 0; i < count; i++)
			{
				alloc.construct(cur + i, value);
			}
			size = size + count ;
			end = end + count ;
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last )
		{
			difference_type diff = iterator::distance(first, last);
			size_type	count = static_cast<size_type>(diff);
			while (size + count < capacity)
			{
				size_type	new_cap = (capacity * 2 > 0) ? (capacity * 2) : 1;
				reserve(new_cap);
			}
			value_type* cur = end;
			if (cur < &(*pos))
				pos = end();
			while (cur > &(*pos))
			{
				alloc.construct(cur + count - 1, *(cur - 1));
				cur--;
				alloc.destroy(cur);
			}
			for (size_type i = 0; i < count; i++, first++)
			{
				alloc.construct(cur + i, *first);
			}
			size = size + count ;
			end = end + count ;
		}
		iterator erase( iterator pos )
		{
			if (end() < pos)
				return pos ;
			value_type* cur = &(*pos);
			alloc.destroy(cur);
			while (cur + 1 < end)
			{
				alloc.construct(cur, *(cur + 1));
				cur++;
				alloc.destroy(cur);
			}
			size--;
			end--;
			return pos ;
		}
		iterator erase( iterator first, iterator last )
		{
			if (end() < first)
				return last ;
			if (end() < last)
				last = end() ;
			difference_type diff = iterator::distance(first, last);
			size_type count = static_cast<size_type>(diff);
			value_type* pos = &(*first);
			for (; first != last; first++)
			{
				alloc.destroy(&(*first));
			}
			for (size_type i = 0; first != end(); first++, i++)
			{
				alloc.construct(pos + i, *first);
				alloc.destroy(&(*first));
			}
			size = size - count ;
			end = end - count ;
			return iterator(pos) ;
		}
		void swap( vector& other )
		{
			allocator_type	tmp_alloc = other.alloc;
			value_type*		tmp_elements = other.elements;
			value_type*		tmp_begin = other.begin;
			value_type*		tmp_end = other.end;
			value_type*		tmp_end_cap = other.end_capacity;
			size_type		tmp_size = other.size;
			size_type		tmp_cap = other.capacity;

			other.alloc = this->alloc;
			other.elements = this->elements;
			other.begin = this->begin;
			other.end = this->end;
			other.end_capacity = this->end_capacity;
			other.size = this->size;
			other.capacity = this->capacity;
			
			this->alloc = tmp_alloc;
			this->elements = tmp_elements;
			this->begin = tmp_begin;
			this->end = tmp_end;
			this->end_capacity = tmp_end_cap;
			this->size = tmp_size;
			this->capacity = tmp_cap;
		}
		void	clear()
		{
			for(size_type i = 0; i < size; i++)
			{
				end--;
				alloc.destroy(end) ;
			}
			size = 0 ;
		}
		//	allcator
		allocator_type get_allocator() const
		{
			return alloc ;
		}
	};

	//non-member functions
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		vector<T,Alloc>::iterator	first1 = lhs.begin();
		vector<T,Alloc>::iterator	last1 = lhs.end();
		vector<T,Alloc>::iterator	first2 = rhs.begin();
		vector<T,Alloc>::iterator	last2 = rhs.end();
		
		vector<T,Alloc>::difference_type	diff1 = vector<T,Alloc>::iterator::distance(first1, last1);
		vector<T,Alloc>::difference_type	diff2 = vector<T,Alloc>::iterator::distance(first2, last2);

		if (diff1 != diff2)
			return false ;
		for (; first1 != last1; first1++, first2++)
		{
			if (*first1 != *first2)
				return false ;
		}
		return true ;
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !( lhs == rhs ) ;
	}


	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		vector<T,Alloc>::iterator	first1 = lhs.begin();
		vector<T,Alloc>::iterator	last1 = lhs.end();
		vector<T,Alloc>::iterator	first2 = rhs.begin();
		vector<T,Alloc>::iterator	last2 = rhs.end();

		for (; first1 != last1; first1++, first2++)
		{
			if (first2 == last2)
				return false ;
			if (*first1 < *first2)
				return true ;
			if (*first1 > *first2)
				return false ;
		}
		return true ;
	}
	
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs < rhs)
			return true ;
		if (lhs == rhs)
			return true ;
		return false ;
	}
	
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs <= rhs) ;
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs) ;
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs)
	{
			allocator_type	tmp_alloc = rhs.alloc;
			value_type*		tmp_elements = rhs.elements;
			value_type*		tmp_begin = rhs.begin;
			value_type*		tmp_end = rhs.end;
			value_type*		tmp_end_cap = rhs.end_capacity;
			size_type		tmp_size = rhs.size;
			size_type		tmp_cap = rhs.capacity;

			rhs.alloc = lhs.alloc;
			rhs.elements = lhs.elements;
			rhs.begin = lhs.begin;
			rhs.end = lhs.end;
			rhs.end_capacity = lhs.end_capacity;
			rhs.size = lhs.size;
			rhs.capacity = lhs.capacity;
			
			lhs.alloc = tmp_alloc;
			lhs.elements = tmp_elements;
			lhs.begin = tmp_begin;
			lhs.end = tmp_end;
			lhs.end_capacity = tmp_end_cap;
			lhs.size = tmp_size;
			lhs.capacity = tmp_cap;
	}
}


#endif
