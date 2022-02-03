/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators_traits.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:47:27 by ylee              #+#    #+#             */
/*   Updated: 2022/02/03 18:07:51 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP

# include <cstddef>

namespace	ft
{
	//random_access_iterator_tag 는 iterator 헤더에 있는 empty class 이다.
	class	random_access_iterator_tag {};

	template <typename Iter>
	struct	iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <typename T>
	struct	iterator_traits<T*>
	{
		typedef	ptrdiff_t					difference_type;
		typedef	T							value_type;
		typedef	T*							pointer;
		typedef	T&							reference;
		typedef	random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct	iterator_traits<const T*>
	{
		typedef	ptrdiff_t					difference_type;
		typedef	T							value_type;
		typedef	const T*					pointer;
		typedef	const T&					reference;
		typedef	random_access_iterator_tag	iterator_category;
	};

}

#endif

