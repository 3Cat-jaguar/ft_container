/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:50:02 by ylee              #+#    #+#             */
/*   Updated: 2022/02/03 16:44:55 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
# define EQUAL_HPP

namespace	ft
{
	template<typename InputIter1, typename InputIter2>
	bool	equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (*first1 != *first2) // if (! (*first1 == *first2) ) 와 어떻게 다를까?
				return false ;
		}
		return true ;
	}
}

#endif

