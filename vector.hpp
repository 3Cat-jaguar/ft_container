/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:44:11 by ylee              #+#    #+#             */
/*   Updated: 2022/03/23 05:57:32 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // for allocator
# include "./utils/random_access_iterator.hpp"
# include "./utils/reverse_iterator.hpp"
# include "./utils/enable_if.hpp"
# include "./utils/is_integral.hpp"


namespace	ft
{
	template< typename T, typename Allocator = std::allocator<T> >
	class	vector
	{
	public :
		typedef	T										value_type;
		typedef	Allocator								allocator_type;
		typedef	size_t									size_type;
		typedef	ptrdiff_t								difference_type;
		typedef	T&										reference;
		typedef	const T&								const_reference;
		typedef	typename Allocator::pointer				pointer;
		typedef	typename Allocator::const_pointer		const_pointer;
		typedef	ft::random_access_iterator<T>			iterator;
		typedef	ft::random_access_iterator<const T>		const_iterator;
		typedef	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		allocator_type	alloc;
		value_type*		elements;
		value_type*		start;
		value_type*		fin;
		value_type*		fin_cap;
		size_type		len;
		size_type		cap;

	public:
		//constructor
		explicit	vector( const allocator_type& _alloc = allocator_type() )
		: alloc(_alloc), len(0), cap(0)
		{
			elements = alloc.allocate(0);
			start = elements;
			fin = elements;
			fin_cap = elements;
		}
		//val 에 있는 내용으로 초기화하여 생성
		explicit	vector( size_type n, const value_type& val = value_type(), const allocator_type& _alloc = allocator_type() )
		: alloc(_alloc), len(n), cap(0)
		{
			while (cap < len)
			{
				size_type new_capacity = (cap * 2 > 0) ? (cap * 2) : 1;
				cap = new_capacity ;
			}
			elements = alloc.allocate(cap);
			start = elements;
			fin_cap = start + cap ;
			fin = start;
			for(size_type i = 0; i < n; i++, fin++)
			{
				alloc.construct(fin, val);
			}
		}
		//InputIter 의 first 부터 last 까지의 내용으로 초기화하여 생성
		template <typename InputIter>
		vector( InputIter first, InputIter last, const allocator_type& _alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type* = nullptr )
		:alloc(_alloc)
		{
			difference_type	diff = ft::distance<InputIter>(first, last);
			len = static_cast<size_type>(diff);
			cap = 0 ;
			while (cap < len)
			{
				size_type new_capacity = (cap * 2 > 0) ? (cap * 2) : 1;
				cap = new_capacity ;
			}
			elements = alloc.allocate(cap);
			start = elements;
			fin_cap = start + cap ;
			fin = start;
			for ( ; first != last ; fin++, first++)
			{
				alloc.construct(fin, *first);
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
			len = copy.len;
			cap = copy.cap;
			elements = alloc.allocate(cap);
			start = elements;
			fin_cap = start + cap ;
			fin = start;
			for(size_type i = 0; i < len; i++, fin++)
			{
				alloc.construct(fin, value_type(copy.elements[i]));
			}
			return *this ;
		}
		//destructor
		~vector()
		{
			clear();
			alloc.deallocate(elements, cap);
		}

		//member functions

		//	iterators
		iterator	begin() // first element 의 iterator 를 반환
		{
				return iterator(start) ;
		}
		const_iterator	begin() const
		{
			return const_iterator(start) ;
		}
		iterator	end()
		{
			return iterator(fin) ;
		}
		const_iterator	end() const
		{
			return const_iterator(fin) ;
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
			return len ;
		} // 저장된 element 의 수
		size_type	max_size() const
		{
			return alloc.max_size();
		} // 추가 allocate까지 최대로 가능한 사이즈. 실제 allocate 되어있는 최대 size는 capacity 이다. 혼동하지말기.
		void	resize(size_type cnt, value_type value = value_type())
		{
			if (size() > cnt) // 사이즈를 줄이는 경우
			{
				while (size() != cnt)
					pop_back(); // 뒤에서부터 erase 처리
			}
			else if (size() < cnt) // 사이즈를 키우는 경우
			{
				while (size() != cnt)
					push_back(value); // 뒤에서부터 insert 처리. 공간 부족하면 reserve
			}
		}
		size_type capacity() const  // allocate 되어있는 수
		{
			return cap ;
		}

		bool empty() const
		{
			if (len == 0)
				return true ;
			return false ;
		}
		void reserve( size_type new_cap )
		{
			if (new_cap <= cap)
				return ;
			if (max_size() < new_cap)
				throw ( std::length_error("vector::reserve") ) ;
			value_type* tmp = alloc.allocate(new_cap);
			for(size_type i = 0; i < len ; i++)
			{
				alloc.construct(tmp + i, elements[i]);
			}
			if (elements != nullptr)
				alloc.deallocate(elements, cap);
			cap = new_cap;
			elements = tmp;
			start = elements;
			fin = start + len ;
			fin_cap = start + cap ;
		}
		//	element access
		reference operator[]( size_type pos )
		{
			return elements[pos] ;
		}
		const_reference operator[]( size_type pos ) const
		{
			return elements[pos] ;
		}
		reference at( size_type pos )
		{
			if (!(pos < size()))
				throw(std::out_of_range("vector::at"));
			return elements[pos] ;
		}
		const_reference at( size_type pos ) const
		{
			if (!(pos < size()))
				throw(std::out_of_range("vector::at"));
			return elements[pos] ;
		}
		reference front() // first element 의 reference 를 반환
		{
			return *start ;
		}
		const_reference front() const
		{
			return *start ;
		}
		reference back()
		{
			return *(start + len - 1) ;
		}
		const_reference back() const
		{
			return *(start + len - 1) ;
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
			if (cap < count)
			{
				alloc.deallocate(elements, cap);
				size_type new_capacity ;
				while (cap < count)
				{
					new_capacity = (cap * 2 > 0) ? (cap * 2) : 1;
					cap = new_capacity ;
				}
				elements = alloc.allocate(cap);
				start = elements;
				fin_cap = start + cap ;
			}
			fin = start ;
			for (size_type i = 0; i < count; i++, fin++)
			{
				alloc.construct(fin, value_type(value));
			}
			len = count ;
		}
		template< class InputIt >
		void assign( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr )
		{
			clear() ;
			difference_type diff = ft::distance<InputIt>(first, last);
			size_type	count = static_cast<size_type>(diff);
			if (cap < count)
			{
				alloc.deallocate(elements, cap);
				size_type new_capacity ;
				while (cap < count)
				{
					new_capacity = (cap * 2 > 0) ? (cap * 2) : 1;
					cap = new_capacity ;
				}
				elements = alloc.allocate(cap);
				start = elements;
				fin_cap = start + cap ;
			}
			fin = start ;
			for ( ; first != last ; fin++, first++)
			{
				alloc.construct(fin, value_type(*first));
			}
			len = count ;
		}
		void push_back( const T& value )
		{
			insert(end(), value);
		}
		void pop_back()
		{
			if (len == 0)
				return ;
			this->erase(end() - 1);
		}
		iterator insert( iterator pos, const T& value )
		{
			difference_type	diff = pos.base() - start;
			if (size() + 1 > cap)
			{
				size_type	new_cap = (cap * 2 > 0) ? (cap * 2) : 1;
				this->reserve(new_cap);
			}
			pos = iterator(start + diff) ;
			value_type* cur = fin;
			if (cur < &(*pos))
				pos = end();
			while (pos != end() && cur > &(*pos))
			{
				alloc.construct(cur, *(cur - 1));
				alloc.destroy(cur - 1);
				cur--;
			}
			alloc.construct(cur, value);
			len += 1;
			fin++;
			return pos ;
		}
		void insert( iterator pos, size_type count, const T& value )
		{
			difference_type	diff = pos.base() - start;
			while (size() + count > cap)
			{
				size_type	new_cap = (cap * 2 > 0) ? (cap * 2) : 1;
				reserve(new_cap);
			}
			pos = iterator(start + diff) ;
			value_type* cur = fin;
			if (cur < &(*pos))
				pos = end();
			while (pos != end() && cur > &(*pos))
			{
				alloc.construct(cur + count - 1, *(cur - 1));
				alloc.destroy(cur - 1);
				cur--;
			}
			for (size_type i = 0; i < count; i++)
			{
				alloc.construct(cur + i, value);
			}
			len = len + count ;
			fin = fin + count ;
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr )
		{
			difference_type diff = ft::distance<InputIt>(first, last);
			size_type	count = static_cast<size_type>(diff);
			diff = pos.base() - start ;
			while (size() + count > cap)
			{
				size_type	new_cap = (cap * 2 > 0) ? (cap * 2) : 1;
				reserve(new_cap);
			}
			pos = iterator(start + diff) ;
			value_type* cur = fin;
			if (cur < &(*pos))
				pos = end();
			while (pos != end() && cur > &(*pos))
			{
				alloc.construct(cur + count - 1, *(cur - 1));
				cur--;
				alloc.destroy(cur);
			}
			for (size_type i = 0; i < count; i++, first++)
			{
				alloc.construct(cur + i, *first);
			}
			len = len + count ;
			fin = fin + count ;
		}
		iterator erase( iterator pos )
		{
			if (end() < pos)
				return pos ;
			value_type* cur = &(*pos);
			alloc.destroy(cur);
			while (cur + 1 < fin)
			{
				alloc.construct(cur, *(cur + 1));
				cur++;
				alloc.destroy(cur);
			}
			len--;
			fin--;
			return pos ;
		}
		iterator erase( iterator first, iterator last )
		{
			if (end() < first)
				return last ;
			if (end() < last)
				last = end() ;
			difference_type diff = ft::distance<iterator>(first, last);
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
			len = len - count ;
			fin = fin - count ;
			return iterator(pos) ;
		}
		void swap( vector& other )
		{
			allocator_type	tmp_alloc = other.alloc;
			value_type*		tmp_elements = other.elements;
			value_type*		tmp_start = other.start;
			value_type*		tmp_fin = other.fin;
			value_type*		tmp_fin_cap = other.fin_cap;
			size_type		tmp_len = other.len;
			size_type		tmp_cap = other.cap;

			other.alloc = this->alloc;
			other.elements = this->elements;
			other.start = this->start;
			other.fin = this->fin;
			other.fin_cap = this->fin_cap;
			other.len = this->len;
			other.cap = this->cap;
			
			this->alloc = tmp_alloc;
			this->elements = tmp_elements;
			this->start = tmp_start;
			this->fin = tmp_fin;
			this->fin_cap = tmp_fin_cap;
			this->len = tmp_len;
			this->cap = tmp_cap;
		}
		void	clear()
		{
			for(size_type i = 0; i < len; i++)
			{
				fin--;
				alloc.destroy(fin) ;
			}
			len = 0 ;
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
		typename vector<const T,Alloc>::iterator	first1 = lhs.begin();
		typename vector<const T,Alloc>::iterator	last1 = lhs.end();
		typename vector<const T,Alloc>::iterator	first2 = rhs.begin();
		typename vector<const T,Alloc>::iterator	last2 = rhs.end();
		
		typename vector<const T,Alloc>::difference_type	diff1 = ft::distance<typename vector<const T,Alloc>::iterator>(first1, last1);
		typename vector<const T,Alloc>::difference_type	diff2 = ft::distance<typename vector<const T,Alloc>::iterator>(first2, last2);

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
	bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return !( lhs == rhs ) ;
	}


	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename vector<const T,Alloc>::iterator	first1 = lhs.begin();
		typename vector<const T,Alloc>::iterator	last1 = lhs.end();
		typename vector<const T,Alloc>::iterator	first2 = rhs.begin();
		typename vector<const T,Alloc>::iterator	last2 = rhs.end();

		for (; first1 != last1; first1++, first2++)
		{
			if (first2 == last2)
				return false ;
			if (*first1 < *first2)
				return true ;
			if (*first1 > *first2)
				return false ;
		}
		if (first2 == last2)
			return false ;
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
		vector<T, Alloc> tmp(rhs);
		tmp.swap(lhs);
		tmp.swap(rhs);
	}
}


#endif
