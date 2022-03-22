#include <iostream>
#include <chrono>
#include "test_funcs.hpp"
#define TYPE_NAMESPACE
#ifdef TYPE_NAMESPACE == std
	#include <map>
	#include <stack>
	#include <vector>
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
#endif

int main(void)
{
    std::chrono::system_clock::time_point	start = std::chrono::system_clock::now();
    if (TYPE_NAMESPACE == 1)
        std::cout << ">>this test is STL<<\n\n";
    else
        std::cout << ">>this test is my containers<<\n\n";
    std::cout << "===== test vector =====\n";
    test_vector();
    std::cout << "\n===== test stack =====\n";
    test_stack();
    std::cout << "\n===== test map =====\n";
    test_map();
    std::cout << "\n!!! test end\n";
    std::chrono::system_clock::time_point	end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start ;
	std::cout << "duration time : " << diff.count() << std::endl;
    return (0);
}