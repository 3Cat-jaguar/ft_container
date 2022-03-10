/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:16:16 by ylee              #+#    #+#             */
/*   Updated: 2022/02/24 16:19:08 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LESS_HPP
# define LESS_HPP

# include "./binary_function.hpp"

namespace ft
{
    template <typename T>
    struct less : ft::binary_function<T, T, bool>
    {
        bool    operator()(const T& lhs, const T& rhs) const
        {
            if (lhs < rhs)
                return true ;
            return false ;
        }
    };
} // namespace ft


#endif