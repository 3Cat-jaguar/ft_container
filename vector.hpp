/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:44:11 by ylee              #+#    #+#             */
/*   Updated: 2022/02/04 17:22:57 by ylee             ###   ########.fr       */
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
		value_type*	elements;
		size_type	size;
		size_type	capacity;

	public:
		//constructor
		explicit	vector( const allocator_type& alloc = allocator_type() );
		explicit	vector( size_type n, const value_type& val = value_type(),
							const_allocator_type& alloc = allocator_type() );
		template <typename InputIter>
		vector( InputIter first, InputIter last, 
				const allocator_type& alloc = allocator_type() );
		vector(const vector& copy);
		//assignation operator
		vector&	operator=(const vector& copy) ;
		//destructor
		~vector();

		//member functions

		//	iterators
		begin(); // first element 의 iterator 를 반환
		end();
		rbegin();
		rend();
		//	capacity
		size();
		max_size();
		resize();
		capacity();
		empty();
		reserve();
		//	element access
		operator[];
		at();
		front(); // first element 의 reference 를 반환
		back();
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
		assign();
		push_back();
		pop_back();
		insert();
		erase();
		swap();
		clear();
		//	allcator
		get_allocator();
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
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}


#endif
