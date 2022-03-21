/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:48:04 by ylee              #+#    #+#             */
/*   Updated: 2022/03/21 00:15:48 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "./iterator_traits.hpp"

namespace	ft
{
	template<typename Iter>
	class	reverse_iterator
	{
	public:
		typedef	Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;
	protected:
		iterator_type	current ;
	public:
		reverse_iterator() {}
		explicit	reverse_iterator( iterator_type x ) { current = x ; }
		template <typename U >
		reverse_iterator( const reverse_iterator<U>& other ) { current = other.base() ; }
		~reverse_iterator() {}
		template <typename U>
		reverse_iterator&	operator=( const reverse_iterator<U>& other)
		{
			current = other.base() ;
			return *this ;
		}
		iterator_type	base() const
		{
			return current ;
		}
		reference			operator*() const
		{
			iterator_type	tmp = current ;
			return *(--tmp) ;
		}
		pointer				operator->() const { return &(operator*()) ; }
		reference			operator[]( difference_type	n ) const { return base()[-n-1] ; }
		reverse_iterator&	operator++()
		{
			current-- ;
			return *this ;
		}
		reverse_iterator	operator++(int)
		{
			reverse_iterator	tmp = *this ;
			++(*this);
			return tmp ;
		}
		reverse_iterator&	operator--()
		{
			current++ ;
			return *this ;
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator	tmp = *this ;
			--(*this);
			return tmp ;
		}
		reverse_iterator	operator+(difference_type n) const
		{
			return reverse_iterator( base() - n ) ;
		}
		reverse_iterator	operator-(difference_type n) const
		{
			return reverse_iterator( base() + n ) ;
		}
		reverse_iterator&	operator+=(difference_type n)
		{
			current -= n ;
			return *this ;
		}
		reverse_iterator&	operator-=(difference_type n)
		{
			current += n ;
			return *this ;
		}
	};
	//non-member function operators
	template<typename Iter>
	bool					operator==(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() == rhs.base() ;
	}
	template<typename Iter>
	bool					operator!=(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() != rhs.base() ;
	}
	template<typename Iter>
	bool					operator<(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() > rhs.base() ;
	}
	template<typename Iter>
	bool					operator<=(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() >= rhs.base() ;
	}
	template<typename Iter>
	bool					operator>(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() < rhs.base() ;
	}
	template<typename Iter>
	bool					operator>=(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<Iter>& rhs)
	{
		return lhs.base() <= rhs.base() ;
	}
	template<typename Iter>
	reverse_iterator<Iter>	operator+(
				typename reverse_iterator<Iter>::difference_type n,
				const reverse_iterator<Iter>& rev_it)
	{
		reverse_iterator<Iter>	tmp(rev_it);
		tmp += n ;
		return tmp ;
	}
	template<typename Iter>
	reverse_iterator<Iter>	operator-(
				typename reverse_iterator<Iter>::difference_type n,
				const reverse_iterator<Iter>& rev_it)
	{
		reverse_iterator<Iter>	tmp(rev_it);
		tmp -= n ;
		return tmp ;
	}
	
	//------- compare Iterator and const_Iterator
	
	template<typename Iter, typename cIter>
	bool					operator==(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<cIter>& rhs)
	{
		return lhs.base() == rhs.base() ;
	}
	template<typename Iter, typename cIter>
	bool					operator!=(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<cIter>& rhs)
	{
		return lhs.base() != rhs.base() ;
	}
	template<typename Iter, typename cIter>
	bool					operator<(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<cIter>& rhs)
	{
		return lhs.base() > rhs.base() ;
	}
	template<typename Iter, typename cIter>
	bool					operator<=(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<cIter>& rhs)
	{
		return lhs.base() >= rhs.base() ;
	}
	template<typename Iter, typename cIter>
	bool					operator>(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<cIter>& rhs)
	{
		return lhs.base() < rhs.base() ;
	}
	template<typename Iter, typename cIter>
	bool					operator>=(const reverse_iterator<Iter>& lhs,
										const reverse_iterator<cIter>& rhs)
	{
		return lhs.base() <= rhs.base() ;
	}

	template<typename T>
	typename reverse_iterator<T>::difference_type	operator-(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs)
	{
		return	rhs.base() - lhs.base() ;
	}

	template<typename T, typename cT>
	typename reverse_iterator<T>::difference_type	operator-(const reverse_iterator<T>& lhs, const reverse_iterator<cT>& rhs)
	{
		return	rhs.base() - lhs.base() ;
	}
	
}


#endif

