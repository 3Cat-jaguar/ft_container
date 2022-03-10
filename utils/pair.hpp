/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:51:45 by ylee              #+#    #+#             */
/*   Updated: 2022/03/11 00:04:49 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STD_PAIR_HPP
# define STD_PAIR_HPP

# include <iostream>

namespace	ft
{
	template<typename T1, typename T2>
	struct	pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;
		
		first_type	first;
		second_type	second;

		pair( const first_type& x = first_type(), const second_type& y = second_type())
		: first(x), second(y)
		{}
		
		// template <typename U1, typename U2>
		// pair( const pair<U1, U2>& p)
		// {
		// 	first = static_cast<first_type>(p.first);
		// 	second = static_cast<second_type>(p.second);
		// }
		pair( const pair& p)
		{
			first = p.first;
			second = p.second;
		}
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
	
	template <typename T1, typename T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second ; }

	//비교해야할 값이 두개이므로 위에 정의된 operator== 를 활용한다. 
	template <typename T1, typename T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs) ; }

	template <typename T1, typename T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second) ; }

	//비교해야할 값이 두개이므로 위에 정의된 operator< 를 활용한다
	template <typename T1, typename T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs) ; }

	template <typename T1, typename T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs ; }

	template <typename T1, typename T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs) ; }

	template <typename T1, typename T2>
	std::ostream&	operator<<(std::ostream& out, const pair<T1, T2>& p)
	{
		out << "this pair Key : " << p.first << " , Mapping : " << p.second;
		return out ;
	}
}

#endif
