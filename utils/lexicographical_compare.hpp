/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:50:57 by ylee              #+#    #+#             */
/*   Updated: 2022/02/03 18:24:09 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace	ft
{

	template< class InputIter1, class InputIter2 >
	bool lexicographical_compare( InputIter1 first1, InputIter1 last1,
								InputIter2 first2, InputIter2 last2 )
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false ;
			if (*first1 < *first2)
				return true ;
			++first1;
			++first2;
		}
		return first2 != last2 ;
	}

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2, Compare comp )
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1) )
				return false ;
			if ( comp(*first1, *first2) )
				return true ;
			++first1;
			++first2;
		}
		return first2 != last2 ;
	}
}


#endif

