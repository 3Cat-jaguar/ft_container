/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylee <ylee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:33:42 by ylee              #+#    #+#             */
/*   Updated: 2022/03/23 16:27:53 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include <string>
#include <iostream>
#if TYPE == 2
#ifndef TYPE_NAMESPACE
#define TYPE_NAMESPACE ft
#endif
#include "map.hpp"
#elif TYPE == 1
#ifndef TYPE_NAMESPACE
#define TYPE_NAMESPACE std
#endif
#include <map>
#endif

template <typename T1, typename T2>
void	printMap(TYPE_NAMESPACE::map<T1, T2>& mp, bool isConst = true, bool isRev = false)
{
	std::cout << "size : " << mp.size() << std::endl;
	std::cout << "max_size : " << mp.max_size() << std::endl;

	if (isConst == false && isRev == false)
	{
		typename TYPE_NAMESPACE::map<T1, T2>::iterator it = mp.begin();
		typename TYPE_NAMESPACE::map<T1, T2>::iterator ite = mp.end();
		if (mp.empty())
			std::cout << "this map is empty\n";
		else
		{
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << it->first << " , " ;
			std::cout << " //end\n";
		}
		std::cout << "###############################################\n" << std::endl;
	}
	else if (isConst == true && isRev == false)
	{
		typename TYPE_NAMESPACE::map<T1, T2>::const_iterator it = mp.begin();
		typename TYPE_NAMESPACE::map<T1, T2>::const_iterator ite = mp.end();
		if (mp.empty())
			std::cout << "this map is empty\n";
		else
		{
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << it->first << " , " ;
			std::cout << " //end\n";
		}
		std::cout << "###############################################\n" << std::endl;
	}
	else if (isConst == false && isRev == true)
	{
		typename TYPE_NAMESPACE::map<T1, T2>::reverse_iterator it = mp.rbegin();
		typename TYPE_NAMESPACE::map<T1, T2>::reverse_iterator ite = mp.rend();
		if (mp.empty())
			std::cout << "this map is empty\n";
		else
		{
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << it->first << " , " ;
			std::cout << " //end\n";
		}
		std::cout << "###############################################\n" << std::endl;
	}
	else
	{
		typename TYPE_NAMESPACE::map<T1, T2>::const_reverse_iterator it = mp.rbegin();
		typename TYPE_NAMESPACE::map<T1, T2>::const_reverse_iterator ite = mp.rend();
		if (mp.empty())
			std::cout << "this map is empty\n";
		else
		{
			std::cout << "Content is:" << std::endl;
			for (; it != ite; ++it)
				std::cout << it->first << " , " ;
			std::cout << " //end\n";
		}
		std::cout << "###############################################\n" << std::endl;
	}
}

void	test_map()
{
	std::cout << "map default construct : map name is origin\n";
    TYPE_NAMESPACE::map<int, std::string>  origin;
	printMap(origin);
	
	TYPE_NAMESPACE::pair<int, std::string> test[10];

	for(int i = 0; i < 5; i++)
	{
		test[i] = TYPE_NAMESPACE::make_pair((i + 1) * 10, std::string(i + 1, 'a' + i));
	}
	
    std::cout << ">>origin map insert elements<<\n";
	for (int i = 4; i >= 0; i--)
	{
		std::cout << "insert [ " << test[i].first << " , " << test[i].second << " ]\n";
		origin.insert(test[i]) ;
		printMap(origin);
	}

	std::cout << std::endl;
	std::cout << "print iterator\n";
	printMap(origin, false, false);
	std::cout << "print const iterator\n";
	printMap(origin, true, false);
	std::cout << "print reverse iterator\n";
	printMap(origin, false, true);
	std::cout << "print const reverse iterator\n";
	printMap(origin, true, true);
	
	std::cout << "map construct with range : map name is mp_range\n";
    TYPE_NAMESPACE::map<int, std::string>  mp_range(origin.begin(), origin.end());
	printMap(mp_range);

	std::cout << "map copy construct : map name is mp_copy\n";
    TYPE_NAMESPACE::map<int, std::string>  mp_copy(mp_range);
	printMap(mp_copy);

    std::cout << ">>test at, operator[]<<\n";
	std::cout << "\tfind key=20 element use at\n";
	std::cout << "key = 20, mapped value = " << origin.at(20) << std::endl;
	std::cout << "\tfind key=20 element use operator[]\n";
	std::cout << "key = 20, mapped value = " << origin[20] << std::endl;
	std::cout << "--------\n\n";

	std::cout << ">>insert 1 element in mp_copy<<\n";
	std::cout << "\tinsert [25, test]\n";
	mp_copy.insert(TYPE_NAMESPACE::make_pair(25, "test"));
	std::cout << "[[check mp_copy after insert]]\n";
	printMap(mp_copy);
	std::cout << "[[mp_range for check deep copy]]\n";
	printMap(mp_range);

	std::cout << ">>clear mp_range and insert many elements<<\n";
	std::cout << "\tclear mp_range";
	mp_range.clear();
	printMap(mp_range);
	TYPE_NAMESPACE::map<int, std::string>::iterator first = mp_copy.begin();
	TYPE_NAMESPACE::map<int, std::string>::iterator last = mp_copy.end();
	first++;
	last--;
	last--;
	mp_range.insert(first, last);
	printMap(mp_range);
	
	std::cout << ">>check lower_bound, upper_bound, equal_range <<" << std::endl;
	std::cout << "lower_bound: " << mp_copy.lower_bound(20)->first << std::endl;
	std::cout << "upper_bound: " << mp_copy.upper_bound(20)->first << std::endl;
	std::cout << "equal_range: " << mp_copy.equal_range(20).first->first << ", " << mp_copy.equal_range(20).second->first << std::endl;

	
	std::cout << ">>test relational operators<<\n";
	std::cout << "\"origin\"";
	if (origin == mp_copy)
		std::cout << " == ";
	if (origin != mp_copy)
		std::cout << " != ";
	if (origin < mp_copy)
		std::cout << " < ";
	if (origin <= mp_copy)
		std::cout << " <= ";	
	if (origin > mp_copy)
		std::cout << " > ";
	if (origin > mp_copy)
		std::cout << " >= ";
	std::cout << "\"mp_copy\"\n";
	std::cout << "-------\n";	
	
}