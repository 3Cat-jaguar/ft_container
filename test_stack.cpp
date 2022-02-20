#include <iostream>
#include <string>
#include <stack>
#include "stack.hpp"

void    test_stack(void)
{
    std::stack<std::string> origin;
    ft::stack<std::string>  mystack;

    std::cout << ">>origin stack, my stack create<<\n";
    std::cout << "origin size : " << origin.size() << " //\n";
    std::cout << "origin stack is ";
    if (!origin.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "mystack size : " << mystack.size() << " //\n";
	std::cout << "my stack is ";
    if (!mystack.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "-------\n";

}