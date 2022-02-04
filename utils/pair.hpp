/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:51:45 by ylee              #+#    #+#             */
/*   Updated: 2022/02/04 13:31:06 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STD_PAIR_HPP
# define STD_PAIR_HPP

namespace	ft
{
	template<typename T1, typename T2>
	struct	pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;
		
		first_type	first;
		second_type	second;

		pair() {}
		pair( const first_type& x, const second_type& y) { first = x; second = y; }
		template <typename U1, typename U2>
		pair( const pair<U1, U2>& p) { first = p.first; second = p.second; }
		pair( const pair& p) = default;
		~pair() {}
		pair&	operator=(const pair& p)
		{
			first = p.first;
			second = p.second;
			return *this ;
		}
	};
	//non-member functions
	template<typename T1, typename T2>
	pair<T1, T2>	make_pair(T1 t, T2 u) { return pair<T1, T2>(t, u) ; }

}




#endif
