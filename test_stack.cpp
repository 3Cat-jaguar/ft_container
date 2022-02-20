#include <iostream>
#include <string>
#include <stack>
#include "stack.hpp"

void    test_stack(void)
{
    std::string elemList[] = 
    {
        "test",
        "string",
        "is here",
        "now end"
    };

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

    std::cout << ">>test push<<\n";
    for(int i = 0; i < 4; i++)
    {
        origin.push(elemList[i]);
        mystack.push(elemList[i]);
    }
    std::cout << "origin size : " << origin.size() << " //\n";
    std::cout << "origin stack is ";
    if (!origin.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "last elem is : |" << origin.top() << "| //\n";

    std::cout << "mystack size : " << mystack.size() << " //\n";
	std::cout << "my stack is ";
    if (!mystack.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "last elem is : |" << mystack.top() << "| //\n";
    std::cout << "-------\n";

    std::cout << ">>copy mystack to mystack2<<\n";
    ft::stack<std::string>  mystack2(mystack);
    std::cout << "mystack size : " << mystack.size() << " //\n";
    std::cout << "mystack stack is ";
    if (!mystack.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "last elem is : |" << mystack.top() << "| //\n";

    std::cout << "mystack2 size : " << mystack2.size() << " //\n";
	std::cout << "my stack2 is ";
    if (!mystack2.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "last elem is : |" << mystack2.top() << "| //\n";
    std::cout << "-------\n";

    std::cout << ">>test relational operators<<\n";
    std::cout << "\"mystack\"";
    if (mystack == mystack2)
        std::cout << " == ";
    if (mystack != mystack2)
        std::cout << " != ";
    if (mystack < mystack2)
        std::cout << " < ";
    if (mystack <= mystack2)
        std::cout << " <= ";
    if (mystack > mystack2)
        std::cout << " > ";
    if (mystack >= mystack2)
        std::cout << " >= ";
    std::cout << "\"mystack2\"\n";
    std::cout << "-------\n";

    std::cout << ">>pop mystack<<\n";
    mystack.pop();
    std::cout << "mystack size : " << mystack.size() << " //\n";
    std::cout << "mystack stack is ";
    if (!mystack.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "last elem is : |" << mystack.top() << "| //\n";

    std::cout << "mystack2 size : " << mystack2.size() << " //\n";
	std::cout << "my stack2 is ";
    if (!mystack2.empty())
        std::cout << "not ";
    std::cout << "empty\n";
    std::cout << "last elem is : |" << mystack2.top() << "| //\n";
    
    std::cout << "\"mystack\"";
    if (mystack == mystack2)
        std::cout << " == ";
    if (mystack != mystack2)
        std::cout << " != ";
    if (mystack < mystack2)
        std::cout << " < ";
    if (mystack <= mystack2)
        std::cout << " <= ";
    if (mystack > mystack2)
        std::cout << " > ";
    if (mystack >= mystack2)
        std::cout << " >= ";
    std::cout << "\"mystack2\"\n";
    std::cout << "-------\n";

    return ;
}