#include <iostream>

#define TYPE_NAMESPACE std

#if TYPE_NAMESPACE == std
	#include <vector>
#else
	#include "vector.hpp"
#endif

void test_vector()
{

	// vector test command
	TYPE_NAMESPACE::vector<int> origin;
	"origin can alloc max_size : " << origin.max_size() << " //\n";
	std::cout << "-------\n";

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
	TYPE_NAMESPACE::vector<int>::iterator first2 = origin.begin();
	TYPE_NAMESPACE::vector<int>::iterator last2 = origin.end();

	std::cout << ">>use origin iterator<<\n";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";



	std::cout << ">>check empty vector<<\n";
	if (origin.empty())
		std::cout << "   > origin is empty\n";
	else
		std::cout << "   > origin is not empty\n";
	std::cout << "-------\n";

	TYPE_NAMESPACE::vector<int>::reverse_iterator first1 = origin.rbegin();
	TYPE_NAMESPACE::vector<int>::reverse_iterator last1 = origin.rend();

	std::cout << ">>use origin reverse iterator<<\n";
	while (first1 != last1)
	{
		std::cout << *first1 << ", ";
		first1++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";

	std::cout << ">>change 3rd element and check in vectors<<\n";
	std::cout << "origin's 2nd, 3rd, 4th element : "
	<< origin[1] << " , " << origin.at(2) << " , " << origin[3] << " // \n";
	std::cout << "  > origin's 4th element change to 24\n";
	origin[3] = 24 ;
	std::cout << "check changed 4th element\n";
	std::cout << origin.at(3) << " // \n";
	std::cout << "-------\n";

	std::cout << ">>copy origin to copyVec<<\n";
	TYPE_NAMESPACE::vector<int> copyVec(origin);
	std::cout << "-------\n";
	
	std::cout << ">>test pop_back<<\n";

	for (int i = 0; i < 2; i++)
	{
		copyVec.pop_back();
		std::cout << "copyVec pop_back "<< std::endl;
		std::cout << "copyVec size : " << copyVec.size() << ", cap : " << copyVec.capacity() << " //\n";
		origin.pop_back();
		std::cout << "origin pop_back " << std::endl;
		std::cout << "origin size : " << origin.size() << ", cap : " << origin.capacity() << " //\n";

		std::cout << "-------\n";
	}

	std::cout << ">>test swap : myvec(unpoped) <-> copyVec(poped) <<\n";
	std::cout << "\tbefore swap\n";
	first2 = origin.begin();
	last2 = origin.end();

	std::cout << ">>use origin iterator<<\n";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";

	first2 = copyVec.begin();
	last2 = copyVec.end();
	std::cout << ">>use copyVec iterator<<\n";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";

	origin.swap(copyVec);

	std::cout << "\tafter swap\n";
	first2 = origin.begin();
	last2 = origin.end();

	std::cout << ">>use origin iterator<<\n";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";

	first2 = copyVec.begin();
	last2 = copyVec.end();
	std::cout << ">>use copyVec iterator<<\n";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";

	std::cout << "-------\n";

	first2 = origin.begin();
	last2 = origin.end();

	std::cout << ">>use origin iterator<<\n";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";
	std::cout << ">>use myvec in after pop elements<<\n";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << ">>use copyVec in before pop elements<<\n";
	while (first4 != last4)
	{
		std::cout << *first4 << ", ";
		first4++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";

	std::cout << ">>test resize & reserve<<\n";
	std::cout << "  > myvec size : " << myvec.size() << " -> 4 use resize //\n";
	myvec.resize(4);
	std::cout << "myvec size : " << myvec.size() << " , cap : " << myvec.capacity() << " //\n";
	first3 = myvec.begin();
	last3 = myvec.end();
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "  > myvec size : " << myvec.size() << " -> 20 use resize //\n";
	myvec.resize(20, 42);
	std::cout << "myvec size : " << myvec.size() << " , cap : " << myvec.capacity() << " //\n";
	first3 = myvec.begin();
	last3 = myvec.end();
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "\n";
	std::cout << "  > myvec size : " << myvec.size() << " -> 2 use reserve //\n";
	myvec.reserve(2);
	std::cout << "myvec size : " << myvec.size() << " , cap : " << myvec.capacity() << " //\n";
	first3 = myvec.begin();
	last3 = myvec.end();
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "  > myvec size : " << myvec.size() << " -> 36 use reserve //\n";
	myvec.reserve(36);
	std::cout << "myvec size : " << myvec.size() << " , cap : " << myvec.capacity() << " //\n";
	first3 = myvec.begin();
	last3 = myvec.end();
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";

	std::cout << ">>copyVec erase 2nd ~ 5th elements<<\n";
	first3 = copyVec.begin();
	last3 = copyVec.end();
	std::cout << "before erase : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	copyVec.erase(copyVec.begin()+1,copyVec.begin()+5);
	first3 = copyVec.begin();
	last3 = copyVec.end();
	std::cout << "after erase : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";

	std::cout << ">>insert many elements at once<<\n";
	first3 = copyVec.begin();
	last3 = copyVec.end();
	std::cout << "before insert : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	copyVec.insert(copyVec.begin()+1, static_cast<ft::vector<int>::size_type>(3), 10);
	first3 = copyVec.begin();
	last3 = copyVec.end();
	std::cout << "after insert : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";

	std::cout << ">>insert origin's 3 elements use reverse_iterator<<\n";
	first2 = origin.begin();
	last2 = origin.end();
	std::cout << "origin vec : ";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";
	first3 = copyVec.begin();
	last3 = copyVec.end();
	std::cout << "before insert : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	//insert elements
	first1 = origin.rbegin() + 1; // 6
	last1 = origin.rbegin() + 4; // 3
	//insert 6, 5, 4
	copyVec.insert(copyVec.begin() + 2, first1, last1);
	first3 = copyVec.begin();
	last3 = copyVec.end();
	std::cout << "after insert : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";


	std::cout << ">>assign myvec 3 elements, value = 10<<\n";
	first3 = myvec.begin();
	last3 = myvec.end();
	std::cout << "before assign : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "myvec size : " << myvec.size() << " , cap : " << myvec.capacity() << " //\n";
	myvec.assign(static_cast<size_t>(3), 10);
	first3 = myvec.begin();
	last3 = myvec.end();
	std::cout << "after assign : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "myvec size : " << myvec.size() << " , cap : " << myvec.capacity() << " //\n";
	std::cout << "-------\n";


	std::cout << ">>assign copyVec origin's first 5 elements<<\n";
	first2 = origin.begin();
	last2 = origin.end();
	std::cout << "origin vec : ";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";
	first3 = copyVec.begin();
	last3 = copyVec.end();
	std::cout << "before assign : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "copyVec size : " << copyVec.size() << " , cap : " << copyVec.capacity() << " //\n";
	copyVec.assign(origin.begin(), origin.begin()+5);
	first3 = copyVec.begin();
	last3 = copyVec.end();
	std::cout << "after assign : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "copyVec size : " << copyVec.size() << " , cap : " << copyVec.capacity() << " //\n";
	std::cout << "-------\n";

	std::cout << ">>test front, back element<<\n";
	std::cout << "myvec.front() : " << myvec.front() << " , copyVec.back() : " << copyVec.back() << " // \n";
	std::cout << "-------\n";

	std::cout << ">>test call element storage use data()<<\n";
	std::cout << "copyVec elements : ";
	int	*data = copyVec.data();
	for(int i = 0; i < static_cast<int>(copyVec.size()); i++)
		std::cout << data[i] << " , ";
	std::cout << "end\n";
	std::cout << "-------\n";

	std::cout << ">>test non-member function swap<<\n";
	std::cout << "   > before swap\n";
	std::cout << "myvec : ";
	first3 = myvec.begin();
	last3 = myvec.end();
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";

	std::cout << "copyVec : ";
	first3 = copyVec.begin();
	last3 = copyVec.end();
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";

	ft::swap(myvec, copyVec);

	std::cout << "   > after swap\n";
	std::cout << "myvec : ";
	first3 = myvec.begin();
	last3 = myvec.end();
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";

	std::cout << "copyVec : ";
	first3 = copyVec.begin();
	last3 = copyVec.end();
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";

	std::cout << ">>test non-member operators<<\n";
	std::cout << "\"myvec\"";
	if (myvec == copyVec)
		std::cout << " == ";
	if (myvec != copyVec)
		std::cout << " != ";
	if (myvec < copyVec)
		std::cout << " < ";
	if (myvec <= copyVec)
		std::cout << " <= ";	
	if (myvec > copyVec)
		std::cout << " > ";
	if (myvec > copyVec)
		std::cout << " >= ";
	std::cout << "\"copyVec\"\n";
	std::cout << "-------\n";


	std::cout << ">>clear vectors<<\n";
	origin.clear();
	myvec.clear();
	copyVec.clear();

	std::cout << ">>check empty vector<<\n";
	if (myvec.empty())
		std::cout << "   > myvec is empty\n";
	else
		std::cout << "   > myvec is not empty\n";
	if (copyVec.empty())
		std::cout << "   > copyVec is empty\n";
	else
		std::cout << "   > copyVec is not empty\n";
	if (origin.empty())
		std::cout << "   > origin is empty\n";
	else
		std::cout << "   > origin is not empty\n";
	std::cout << "-------\n";
	
	return ;
}
