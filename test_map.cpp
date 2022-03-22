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

#include <map>
#include <utility>
#include <string>
#include <iostream>
#include "./utils/binary_search_tree.hpp"
#include "map.hpp"

void	test_map()
{
    std::map<int, std::string>  origin;
	ft::map<int, std::string> map_test ;
	
	std::pair<int, std::string> test1(5, "test1");
	std::pair<int, std::string> test2(3, "test2");
	std::pair<int, std::string> test3(4, "test3");
	std::pair<int, std::string> test4(8, "test4");
	std::pair<int, std::string> test5(6, "test5");
	std::pair<int, std::string> test6(7, "test6");


	ft::map<int, std::string>::value_type ft_test1(5, "test1");
	ft::map<int, std::string>::value_type ft_test2(3, "test2");
	ft::map<int, std::string>::value_type ft_test3(4, "test3");
	ft::map<int, std::string>::value_type ft_test4(8, "test4");
	ft::map<int, std::string>::value_type ft_test5(6, "test5");
	ft::map<int, std::string>::value_type ft_test6(7, "test6");
	
	origin.insert(test1) ;
	origin.insert(test2) ;
	origin.insert(test3) ;
	origin.insert(test4) ;
	origin.insert(test5) ;
	origin.insert(test6) ;
	
	map_test.insert(ft_test1) ;
	map_test.insert(ft_test2) ;
	map_test.insert(ft_test3) ;
	map_test.insert(ft_test4) ;
	map_test.insert(ft_test5) ;
	map_test.insert(ft_test6) ;
	
	std::map<int, std::string>::iterator	i1 = origin.begin();
	std::map<int, std::string>::iterator	f1 = origin.end();
	
	ft::map<int, std::string>::iterator i3 = map_test.begin();
	ft::map<int, std::string>::iterator f3 = map_test.end();
	
	
	std::cout << "origin : " ;
	while (i1 != f1)
	{
		std::cout << (*i1).first ;
		std::cout << " , " ;
		i1++;
	}
	std::cout << " // end\n" ;
	

	std::cout << "map test : \n" ;
	while (i3 != f3)
	{
		std::cout << "\t> " << *i3 ;
		std::cout << " ,\n" ;
		i3++;
	}
	std::cout << " // end\n" ;


	std::cout << "map_test find 7\n";
	std::cout << *(map_test.find(7)) << std::endl;
	
}