/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_function.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:11:23 by ylee              #+#    #+#             */
/*   Updated: 2022/02/24 16:15:45 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_FUNCTION_HPP
# define BINARY_FUNCTION_HPP

namespace ft
{
    template <typename Arg1, typename Arg2, typename Result>
    struct binary_function
    {
        typedef Arg1    first_argument_type;
        typedef Arg2    second_argument_type;
        typedef Result  result_type;
    };
    
} // namespace ft


#endif