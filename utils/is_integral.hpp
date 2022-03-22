/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:49:27 by ylee              #+#    #+#             */
/*   Updated: 2022/03/22 16:20:26 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace	ft
{
	template <bool B, typename T>
	struct	is_integral_value
	{
		typedef T type;
		static const bool value = B;
	};

	//integral 이 아닌 타입이 들어오는 경우 false 로 value 를 지정한다.
	template <typename>
	struct	is_integral_type : public is_integral_value<false, bool> {};

	//integral 인 타입이 들어오는 경우 특수화를 이용하여 value 를 true 로 지정한다.
	template <>
	struct	is_integral_type<bool> : public is_integral_value<true, bool> {};

	template <>
	struct	is_integral_type<char> : public is_integral_value<true, char> {};

	template <>
	struct	is_integral_type<wchar_t> : public is_integral_value<true, wchar_t> {};

	template <>
	struct	is_integral_type<short int> : public is_integral_value<true, short int> {};

	template <>
	struct	is_integral_type<int> : public is_integral_value<true, int> {};

	template <>
	struct	is_integral_type<long int> : public is_integral_value<true, long int> {};

	template <>
	struct	is_integral_type<long long int> : public is_integral_value<true, long long int> {};

	template <>
	struct	is_integral_type<unsigned char> : public is_integral_value<true, unsigned char> {};

	template <>
	struct	is_integral_type<unsigned short int> : public is_integral_value<true, unsigned short int> {};

	template <>
	struct	is_integral_type<unsigned int> : public is_integral_value<true, unsigned int> {};

	template <>
	struct	is_integral_type<unsigned long int> : public is_integral_value<true, unsigned long int> {};

	template <>
	struct	is_integral_type<unsigned long long int> : public is_integral_value<true, unsigned long long int> {};

	// is_integral 에 들어온 타입을 is_integral_type 에 보내서 value 를 체크한다.
	template <typename T>
	struct	is_integral : public is_integral_type<T> {}; 
}


#endif
