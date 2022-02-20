#include <iostream>
#include "test_funcs.hpp"

int main(void)
{
    std::cout << "===== test vector =====\n";
    test_vector();
    std::cout << "\n===== test stack =====\n";
    test_stack();
    std::cout << "\n===== test map =====\n";
    test_map();
    std::cout << "\n!!! test end\n";
    return (0);
}