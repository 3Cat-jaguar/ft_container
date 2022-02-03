/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:48:38 by ylee              #+#    #+#             */
/*   Updated: 2022/02/03 16:34:11 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

// enable_if 를 이용하면
// true 인 값이 들어오는 경우에만
// T 를 type 으로 쓸 수 있도록 제한할 수 있다.
// 그 외의 경우에는 컴파일 에러가 발생하지도, 동작하지도 않는다.

namespace	ft
{
	template < bool B, typename T = void >
	struct	enable_if {};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
}

#endif
