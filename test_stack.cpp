#include <iostream>
#include <string>
#if TYPE == 2
#ifndef TYPE_NAMESPACE
#define TYPE_NAMESPACE ft
#endif
#include "stack.hpp"
#elif TYPE == 1
#ifndef TYPE_NAMESPACE
#define TYPE_NAMESPACE std
#endif
#include <stack>
#endif

void    test_stack(void)
{
    std::string elemList[] = 
    {
        "test1",
        "test2",
        "test3",
        "test4"
    };

    TYPE_NAMESPACE::stack<std::string> origin;

    std::cout << ">>origin stack, my stack create<<\n";
    std::cout << "origin size : " << origin.size() << " //\n";
    std::cout << "origin stack is ";
    if (!origin.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "-------\n";

    std::cout << ">>test push<<\n";
    for(int i = 0; i < 4; i++)
    {
        std::cout << "push element : " << elemList[i] << std::endl;
        origin.push(elemList[i]);
    }
    std::cout << "origin size : " << origin.size() << " //\n";
    std::cout << "origin stack is ";
    if (!origin.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "last elem is : |" << origin.top() << "| //\n";
    std::cout << "-------\n";

    std::cout << ">>copy origin to copyStack<<\n";
    TYPE_NAMESPACE::stack<std::string>  copyStack(origin);
    std::cout << "copy stack size : " << copyStack.size() << " //\n";
    std::cout << "copy stack stack is ";
    if (!copyStack.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "last elem is : |" << copyStack.top() << "| //\n";
    std::cout << "-------\n";

    std::cout << ">>test relational operators<<\n";
    std::cout << "\"origin\"";
    if (origin == copyStack)
        std::cout << " == ";
    if (origin != copyStack)
        std::cout << " != ";
    if (origin <  copyStack)
        std::cout << " < ";
    if (origin <= copyStack)
        std::cout << " <= ";
    if (origin >  copyStack)
        std::cout << " > ";
    if (origin >= copyStack)
        std::cout << " >= ";
    std::cout << "\"copy Stack\"\n";
    std::cout << "-------\n";

    std::cout << ">>pop origin<<\n";
    origin.pop();
    std::cout << "origin size : " << origin.size() << " //\n";
    std::cout << "origin stack is ";
    if (!origin.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "last elem is : |" << origin.top() << "| //\n";

    std::cout << "copyStack size : " << copyStack.size() << " //\n";
	std::cout << "my stack2 is ";
    if (!copyStack.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "last elem is : |" << copyStack.top() << "| //\n";
    
    std::cout << "\"origin\"";
    if (origin == copyStack)
        std::cout << " == ";
    if (origin != copyStack)
        std::cout << " != ";
    if (origin < copyStack)
        std::cout << " < ";
    if (origin <= copyStack)
        std::cout << " <= ";
    if (origin > copyStack)
        std::cout << " > ";
    if (origin >= copyStack)
        std::cout << " >= ";
    std::cout << "\"copyStack\"\n";
    std::cout << "-------\n";

    return ;
}