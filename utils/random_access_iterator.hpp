/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:48:04 by ylee              #+#    #+#             */
/*   Updated: 2022/02/07 12:24:12 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "./iterator_traits.hpp"

namespace	ft
{
	template<typename Iter>
	class	random_access_iterator
	{
		typedef	Iter											iterator_type;
		typedef ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef ft::iterator_traits<Iter>::value_type			value_type;
		typedef ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef ft::iterator_traits<Iter>::pointer				pointer;
		typedef ft::iterator_traits<Iter>::reference			reference;
	protected:
		iterator_type	current ;
	public:
		random_access_iterator() {}
		explicit	random_access_iterator( iterator_type x ) { current = x ; }
		template <typename U >
		random_access_iterator( const random_access_iterator<U>& other ) { current = other.current ; }
		~random_access_iterator() {}
		template <typename U>
		random_access_iterator&	operator=( const random_access_iterator<U>& other)
		{
			current = other.current ;
			return *this ;
		}
		iterator_type	base()
		{
			return random_access_iterator<Iter>(current).current ;
		}
		reference			operator*() const
		{
			iterator_type	tmp = current ;
			return *--tmp ;
		}
		pointer				operator->() const { return &(operator*()) ; }
		reference			operator[]( difference_type	n ) const { return base()[-n-1] ; }
		random_access_iterator&	operator++()
		{
			++(*this) ;
			return this ;
		}
		random_access_iterator	operator++(int)
		{
			random_access_iterator	tmp = *this ;
			++(*this);
			return tmp ;
		}
		random_access_iterator&	operator--()
		{
			--(*this) ;
			return this ;
		}
		random_access_iterator	operator--(int)
		{
			random_access_iterator	tmp = *this ;
			--(*this);
			return tmp ;
		}
		random_access_iterator	operator+(difference_type n) const
		{
			return random_access_iterator( base() + n ) ;
		}
		random_access_iterator	operator-(difference_type n) const
		{
			return random_access_iterator( base() - n ) ;
		}
		random_access_iterator&	operator+=(difference_type n)
		{
			current += n ;
			return *this ;
		}
		random_access_iterator&	operator-=(difference_type n)
		{
			current -= n ;
			return *this ;
		}
		//additional functions
		difference_type	distance(Iter fist, Iter last)
		{
			difference_type	result = 0;
			while (first != last)
			{
				result++;
				first++;
			}
			return result ;
		}
	};
	//non-member function operators
	template<typename Iter>
	bool					operator==(const random_access_iterator<Iter>& lhs,
										const random_access_iterator<Iter>& rhs)
	{
		return lhs.base() == rhs.base() ;
	}
	template<typename Iter>
	bool					operator!=(const random_access_iterator<Iter>& lhs,
										const random_access_iterator<Iter>& rhs)
	{
		return lhs.base() != rhs.base() ;
	}
	template<typename Iter>
	bool					operator<(const random_access_iterator<Iter>& lhs,
										const random_access_iterator<Iter>& rhs)
	{
		return lhs.base() < rhs.base() ;
	}
	template<typename Iter>
	bool					operator<=(const random_access_iterator<Iter>& lhs,
										const random_access_iterator<Iter>& rhs)
	{
		return lhs.base() <= rhs.base() ;
	}
	template<typename Iter>
	bool					operator>(const random_access_iterator<Iter>& lhs,
										const random_access_iterator<Iter>& rhs)
	{
		return lhs.base() > rhs.base() ;
	}
	template<typename Iter>
	bool					operator>=(const random_access_iterator<Iter>& lhs,
										const random_access_iterator<Iter>& rhs)
	{
		return lhs.base() >= rhs.base() ;
	}
	template<typename Iter>
	random_access_iterator<Iter>	operator+(
				typename random_access_iterator<Iter>::difference_type n,
				const random_access_iterator<Iter>& rev_it)
	{
		random_access_iterator<Iter>	tmp(rev_it);
		tmp += n ;
		return tmp ;
	}
	template<typename Iter>
	random_access_iterator<Iter>	operator-(
				typename random_access_iterator<Iter>::difference_type n,
				const random_access_iterator<Iter>& rev_it)
	{
		random_access_iterator<Iter>	tmp(rev_it);
		tmp -= n ;
		return tmp ;
	}
}


#endif

