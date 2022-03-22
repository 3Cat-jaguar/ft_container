#include <iostream>
#if TYPE == 2
#ifndef TYPE_NAMESPACE
#define TYPE_NAMESPACE ft
#endif
#include "vector.hpp"
#elif TYPE == 1
#ifndef TYPE_NAMESPACE
#define TYPE_NAMESPACE std
#endif
#include <vector>
#endif

template <typename T>
void	printVector(TYPE_NAMESPACE::vector<T>& vec, bool isConst = true, bool isRev = false)
{
	std::cout << "size : " << vec.size() << std::endl;
	std::cout << "capacity : " << vec.capacity() << std::endl;
	std::cout << "max_size : " << vec.max_size() << std::endl;

	if (isConst == false && isRev == false)
	{
		typename TYPE_NAMESPACE::vector<T>::iterator it = vec.begin();
		typename TYPE_NAMESPACE::vector<T>::iterator ite = vec.end();
		std::cout << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << *it << " , ";
		std::cout << " //end\n";
		std::cout << "###############################################\n" << std::endl;
	}
	else if (isConst == true && isRev == false)
	{
		typename TYPE_NAMESPACE::vector<T>::const_iterator it = vec.begin();
		typename TYPE_NAMESPACE::vector<T>::const_iterator ite = vec.end();
		std::cout << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << *it << " , ";
		std::cout << " //end\n";
		std::cout << "###############################################\n" << std::endl;
	}
	else if (isConst == false && isRev == true)
	{
		typename TYPE_NAMESPACE::vector<T>::reverse_iterator it = vec.rbegin();
		typename TYPE_NAMESPACE::vector<T>::reverse_iterator ite = vec.rend();
		std::cout << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << *it << " , ";
		std::cout << " //end\n";
		std::cout << "###############################################\n" << std::endl;
	}
	else
	{
		typename TYPE_NAMESPACE::vector<T>::const_reverse_iterator it = vec.rbegin();
		typename TYPE_NAMESPACE::vector<T>::const_reverse_iterator ite = vec.rend();
		std::cout << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << *it << " , ";
		std::cout << " //end\n";
		std::cout << "###############################################\n" << std::endl;
	}
}

void test_vector()
{

	// vector test command
	TYPE_NAMESPACE::vector<int> origin;
	printVector(origin);

	if (origin.empty())
		std::cout << "   > origin is empty\n";
	else
		std::cout << "   > origin is not empty\n";
	std::cout << "-------\n";

	for (int i = 0; i < 10; i++)
	{
		origin.push_back(i);
		std::cout << "origin push_back " << i << std::endl;
		std::cout << "origin size : " << origin.size() << ", cap : " << origin.capacity() << " //\n";

		std::cout << "-------\n";
	}
	printVector(origin);

	std::cout << ">>check empty vector<<\n";
	if (origin.empty())
		std::cout << "   > origin is empty\n";
	else
		std::cout << "   > origin is not empty\n";
	std::cout << "-------\n";

	std::cout << ">>use origin reverse iterator<<\n";
	printVector(origin, true, true);

	std::cout << ">>change 3rd element and check in vectors<<\n";
	std::cout << "origin's 2nd, 3rd, 4th element : "
	<< origin[1] << " , " << origin.at(2) << " , " << origin[3] << " // \n";
	std::cout << "  > origin's 4th element change to 24\n";
	origin[3] = 24 ;
	std::cout << "check changed 4th element\n";
	printVector(origin);

	std::cout << ">>copy origin to copyVec<<\n";

	TYPE_NAMESPACE::vector<int> copyVec(origin);
	std::cout << "[[copyVec]]\n";
	printVector(copyVec);
	
	std::cout << ">>test pop_back<<\n";

	for (int i = 0; i < 2; i++)
	{
		origin.pop_back();
		std::cout << i + 1 << ") origin pop_back \n";
		std::cout << "origin size : " << origin.size() << ", cap : " << origin.capacity() << " //\n";
	}
	std::cout << "[[poped origin]]\n";
	printVector(origin);
	std::cout << "[[unpoped copyVec]]\n";
	printVector(copyVec);

	std::cout << ">>test swap : origin(poped) <-> copyVec(unpoped) <<\n";
	origin.swap(copyVec);
	std::cout << "\tafter swap\n";
	std::cout << "[[origin]]\n";
	printVector(origin);
	std::cout << "[[copyVec]]\n";
	printVector(copyVec);
	

	std::cout << ">>test resize & reserve<<\n";
	std::cout << "\t> origin size : " << origin.size() << " -> 6 use resize //\n";
	origin.resize(6);
	std::cout << "[[after resize]]\n";
	printVector(origin);
	std::cout << "\t> copyVec size : " << copyVec.size() << " -> 15 use resize //\n";
	copyVec.resize(15, 42);
	std::cout << "[[after resize]]\n";
	printVector(copyVec);
	std::cout << "\n";
	std::cout << "\t> copyVec size : " << copyVec.size() << " -> 2 use reserve //\n";
	copyVec.reserve(2);
	std::cout << "[[after reserve]]\n";
	printVector(copyVec);
	std::cout << "\t> copyVec size : " << copyVec.size() << " -> 36 use reserve //\n";
	copyVec.reserve(36);
	std::cout << "[[after reserve]]\n";
	printVector(copyVec);

	std::cout << ">>copyVec erase 2nd ~ 5th elements<<\n";
	
	copyVec.erase(copyVec.begin()+1,copyVec.begin()+5);
	std::cout << "[[after erase]]\n";
	printVector(copyVec);

	std::cout << ">>insert 3 elements after 3rd element at once <<\n";
	copyVec.insert(copyVec.begin()+3, static_cast<TYPE_NAMESPACE::vector<int>::size_type>(3), 10);
	std::cout << "[[after insert]]\n";
	printVector(copyVec);

	std::cout << ">>insert copyVec's 3 elements use reverse_iterator in origin<<\n";
	std::cout << "[[before insert]] - origin\n";
	printVector(origin);
	std::cout << "[[before insert]] - copyVec\n";
	printVector(copyVec);
	std::cout << "\tinsert copyVec's 6th ~ 9th element to origin 2nd position by reverse order\n";
	TYPE_NAMESPACE::vector<int>::const_reverse_iterator	first = copyVec.rbegin() + 5;
	TYPE_NAMESPACE::vector<int>::const_reverse_iterator	last = copyVec.rbegin() + 9;
	
	origin.insert(origin.begin() + 2, first, last);
	std::cout << "[[after insert]] - origin\n";
	printVector(origin);

	std::cout << ">>assign origin 3 elements, value = 42<<\n";
	origin.assign(static_cast<size_t>(3), 42);
	std::cout << "[[after assign]]\n";
	printVector(origin);

	std::cout << ">>assign origin copyVec's first 5 elements<<\n";
	std::cout << "[[before assign]] - copyVec\n";
	printVector(copyVec);
	origin.assign(copyVec.begin(), copyVec.begin()+5);
	std::cout << "[[after assign]] - origin\n";
	printVector(origin);
	
	std::cout << ">>test front, back element<<\n";
	std::cout << "origin.front() : " << origin.front() << " , origin.back() : " << origin.back() << " // \n";
	std::cout << "-------\n";

	std::cout << ">>test call element storage use data()<<\n";
	std::cout << "copyVec elements : ";
	int	*data = copyVec.data();
	for(int i = 0; i < static_cast<int>(copyVec.size()); i++)
		std::cout << data[i] << " , ";
	std::cout << "end\n";
	std::cout << "-------\n";

	std::cout << ">>test non-member function swap<<\n";
	TYPE_NAMESPACE::swap(origin, copyVec);
	std::cout << "[[after swap]] - origin\n";
	printVector(origin);
	std::cout << "[[after swap]] - copyVec\n";
	printVector(copyVec);

	std::cout << ">>test non-member operators<<\n";
	std::cout << "\"origin\"";
	if (origin == copyVec)
		std::cout << " == ";
	if (origin != copyVec)
		std::cout << " != ";
	if (origin < copyVec)
		std::cout << " < ";
	if (origin <= copyVec)
		std::cout << " <= ";	
	if (origin > copyVec)
		std::cout << " > ";
	if (origin > copyVec)
		std::cout << " >= ";
	std::cout << "\"copyVec\"\n";
	std::cout << "-------\n";


	std::cout << ">>clear vectors<<\n";
	origin.clear();
	copyVec.clear();

	std::cout << ">>check empty vector<<\n";
	if (origin.empty())
		std::cout << "   > origin is empty\n";
	else
		std::cout << "   > origin is not empty\n";
	if (copyVec.empty())
		std::cout << "   > copyVec is empty\n";
	else
		std::cout << "   > copyVec is not empty\n";
	std::cout << "-------\n";
	
	return ;
}
