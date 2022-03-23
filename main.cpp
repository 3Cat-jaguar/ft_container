#include <iostream>
#include <chrono>
#include "test_funcs.hpp"
#ifndef TYPE
#define TYPE    2
#endif
#if TYPE == 2
#define TYPE_NAMESPACE ft
#elif TYPE == 1
#define TYPE_NAMESPACE std
#endif

int main(void)
{
    std::chrono::system_clock::time_point	start = std::chrono::system_clock::now();
    #if TYPE == 1
        std::cout << ">>this test is STL<<\n\n";
    #elif TYPE == 2
        std::cout << ">>this test is my containers<<\n\n";
    #endif
    std::cout << "===== test vector =====\n\n";
    test_vector();
    std::cout << "\n\n===== test stack =====\n\n";
    test_stack();
    std::cout << "\n\n===== test map =====\n\n";
    test_map();
    std::cout << "\n!!! test end\n";
    std::chrono::system_clock::time_point	end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end - start ;
	std::cout << "duration time : " << diff.count() << std::endl;
    return (0);
}