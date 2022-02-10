#include <iostream>
#include <string>
#include <deque>
#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include "test_vector.hpp"
	#include "./utils/random_access_iterator.hpp"
	
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))


int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	// vector test command
	ft::test_vector<int> myvec;
	std::vector<int> origin;
	for (int i = 0; i < 10; i++)
	{
		myvec.push_back(i);
		origin.push_back(i);
	}
	ft::test_vector<int>::iterator first1 = myvec.begin();
	ft::test_vector<int>::iterator last1 = myvec.end();
	std::vector<int>::iterator first2 = origin.begin();
	std::vector<int>::iterator last2 = origin.end();

	std::cout << ">>use my iterator<<\n";
	while (first1 != last1)
	{
		std::cout << *first1 << ", ";
		first1++;
	}
	std::cout << "end\n";
	std::cout << ">>use origin iterator<<\n";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";
	return (0);
}
