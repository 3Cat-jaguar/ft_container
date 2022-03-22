/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:33:42 by ylee              #+#    #+#             */
/*   Updated: 2022/03/22 17:24:56 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include <string>
#include <iostream>
#define TYPE_NAMESPACE std

#if TYPE_NAMESPACE == std
	#include <map>
#else
	#include "map.hpp"
	#include "./utils/binary_search_tree.hpp"
#endif


void	test_map()
{
    TYPE_NAMESPACE::map<int, std::string>  origin;	
	TYPE_NAMESPACE::pair<int, std::string> test1(5, "test1");
	TYPE_NAMESPACE::pair<int, std::string> test2(3, "test2");
	TYPE_NAMESPACE::pair<int, std::string> test3(4, "test3");
	TYPE_NAMESPACE::pair<int, std::string> test4(8, "test4");
	TYPE_NAMESPACE::pair<int, std::string> test5(6, "test5");
	TYPE_NAMESPACE::pair<int, std::string> test6(7, "test6");
	
	origin.insert(test1) ;
	origin.insert(test2) ;
	origin.insert(test3) ;
	origin.insert(test4) ;
	origin.insert(test5) ;
	origin.insert(test6) ;
	
	
	TYPE_NAMESPACE::map<int, std::string>::iterator	i1 = origin.begin();
	TYPE_NAMESPACE::map<int, std::string>::iterator	f1 = origin.end();
	
	std::cout << "origin : " ;
	while (i1 != f1)
	{
		std::cout << (*i1).first ;
		std::cout << " , " ;
		i1++;
	}
	std::cout << " // end\n" ;
	
}