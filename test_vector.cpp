#include <iostream>
#include <vector>
#include "vector.hpp"


void vector_test()
{

	// vector test command
	ft::vector<int> myvec2;
	std::vector<int> origin;
	std::cout << "myvec2 can alloc max_size : " << myvec2.max_size() << " ,\n"
	<< "origin can alloc max_size : " << origin.max_size() << " //\n";
	std::cout << "-------\n";

	std::cout << ">>check empty vector<<\n";
	if (myvec2.empty())
		std::cout << "   > myvec2 is empty\n";
	else
		std::cout << "   > myvec2 is not empty\n";
	if (origin.empty())
		std::cout << "   > origin is empty\n";
	else
		std::cout << "   > origin is not empty\n";
	std::cout << "-------\n";

	for (int i = 0; i < 10; i++)
	{
		myvec2.push_back(i);
		std::cout << "myvec2 push_back " << i << std::endl;
		std::cout << "myvec2 size : " << myvec2.size() << ", cap : " << myvec2.capacity() << " //\n";
		origin.push_back(i);
		std::cout << "origin push_back " << i << std::endl;
		std::cout << "origin size : " << origin.size() << ", cap : " << origin.capacity() << " //\n";

		std::cout << "-------\n";
	}
	ft::vector<int>::iterator first3 = myvec2.begin();
	ft::vector<int>::iterator last3 = myvec2.end();
	std::vector<int>::iterator first2 = origin.begin();
	std::vector<int>::iterator last2 = origin.end();


	std::cout << ">>use origin iterator<<\n";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";
	std::cout << ">>use my vector<<\n";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";



	std::cout << ">>check empty vector<<\n";
	if (myvec2.empty())
		std::cout << "   > myvec2 is empty\n";
	else
		std::cout << "   > myvec2 is not empty\n";
	if (origin.empty())
		std::cout << "   > origin is empty\n";
	else
		std::cout << "   > origin is not empty\n";
	std::cout << "-------\n";

	ft::vector<int>::reverse_iterator first = myvec2.rbegin();
	ft::vector<int>::reverse_iterator last = myvec2.rend();
	std::vector<int>::reverse_iterator first1 = origin.rbegin();
	std::vector<int>::reverse_iterator last1 = origin.rend();


	std::cout << ">>use myvec reverse iterator<<\n";
	while (first != last)
	{
		std::cout << *first << ", ";
		first++;
	}
	std::cout << "end\n";
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
	std::cout << "  > myvec's 3rd element change to 42\n";
	myvec2.at(2) = 42 ;
	std::cout << "my vec's 2nd, 3rd, 4th element : "
	<< myvec2.at(1) << " , " << myvec2[2] << " , " << myvec2.at(3) << " // \n";
	std::cout << "  > myvec's 4th element change to 24\n";
	myvec2[3] = 24 ;
	std::cout << "my vec's 2nd, 3rd, 4th element : "
	<< myvec2[1] << " , " << myvec2.at(2) << " , " << myvec2[3] << " // \n";
	std::cout << "-------\n";

	std::cout << ">>copy myvec2 to myvec<<\n";
	ft::vector<int> myvec(myvec2);
	std::cout << "-------\n";
	
	std::cout << ">>test pop_back<<\n";

	for (int i = 0; i < 2; i++)
	{
		myvec2.pop_back();
		std::cout << "myvec2 pop_back "<< std::endl;
		std::cout << "myvec2 size : " << myvec2.size() << ", cap : " << myvec2.capacity() << " //\n";
		origin.pop_back();
		std::cout << "origin pop_back " << std::endl;
		std::cout << "origin size : " << origin.size() << ", cap : " << origin.capacity() << " //\n";

		std::cout << "-------\n";
	}

	std::cout << ">>test swap : myvec(unpoped) <-> myvec2(poped) <<\n";
	myvec2.swap(myvec);
	std::cout << "-------\n";

	first2 = origin.begin();
	last2 = origin.end();
	first3 = myvec.begin();
	last3 = myvec.end();
	ft::vector<int>::iterator first4 = myvec2.begin();
	ft::vector<int>::iterator last4 = myvec2.end();

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
	std::cout << ">>use myvec2 in before pop elements<<\n";
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

	std::cout << ">>myvec2 erase 2nd ~ 5th elements<<\n";
	first3 = myvec2.begin();
	last3 = myvec2.end();
	std::cout << "before erase : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	myvec2.erase(myvec2.begin()+1,myvec2.begin()+5);
	first3 = myvec2.begin();
	last3 = myvec2.end();
	std::cout << "after erase : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";

	std::cout << ">>insert many elements at once<<\n";
	first3 = myvec2.begin();
	last3 = myvec2.end();
	std::cout << "before insert : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	myvec2.insert(myvec2.begin()+1, static_cast<ft::vector<int>::size_type>(3), 10);
	first3 = myvec2.begin();
	last3 = myvec2.end();
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
	first3 = myvec2.begin();
	last3 = myvec2.end();
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
	myvec2.insert(myvec2.begin() + 2, first1, last1);
	first3 = myvec2.begin();
	last3 = myvec2.end();
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


	std::cout << ">>assign myvec2 origin's first 5 elements<<\n";
	first2 = origin.begin();
	last2 = origin.end();
	std::cout << "origin vec : ";
	while (first2 != last2)
	{
		std::cout << *first2 << ", ";
		first2++;
	}
	std::cout << "end\n";
	first3 = myvec2.begin();
	last3 = myvec2.end();
	std::cout << "before assign : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "myvec2 size : " << myvec2.size() << " , cap : " << myvec2.capacity() << " //\n";
	myvec2.assign(origin.begin(), origin.begin()+5);
	first3 = myvec2.begin();
	last3 = myvec2.end();
	std::cout << "after assign : ";
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "myvec2 size : " << myvec2.size() << " , cap : " << myvec2.capacity() << " //\n";
	std::cout << "-------\n";

	std::cout << ">>test front, back element<<\n";
	std::cout << "myvec.front() : " << myvec.front() << " , myvec2.back() : " << myvec2.back() << " // \n";
	std::cout << "-------\n";

	std::cout << ">>test call element storage use data()<<\n";
	std::cout << "myvec2 elements : ";
	int	*data = myvec2.data();
	for(int i = 0; i < static_cast<int>(myvec2.size()); i++)
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

	std::cout << "myvec2 : ";
	first3 = myvec2.begin();
	last3 = myvec2.end();
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";

	ft::swap(myvec, myvec2);

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

	std::cout << "myvec2 : ";
	first3 = myvec2.begin();
	last3 = myvec2.end();
	while (first3 != last3)
	{
		std::cout << *first3 << ", ";
		first3++;
	}
	std::cout << "end\n";
	std::cout << "-------\n";

	std::cout << ">>test non-member operators<<\n";
	std::cout << "\"myvec\"";
	if (myvec == myvec2)
		std::cout << " == ";
	if (myvec != myvec2)
		std::cout << " != ";
	if (myvec < myvec2)
		std::cout << " < ";
	if (myvec <= myvec2)
		std::cout << " <= ";	
	if (myvec > myvec2)
		std::cout << " > ";
	if (myvec > myvec2)
		std::cout << " >= ";
	std::cout << "\"myvec2\"\n";
	std::cout << "-------\n";


	std::cout << ">>clear vectors<<\n";
	origin.clear();
	myvec.clear();
	myvec2.clear();

	std::cout << ">>check empty vector<<\n";
	if (myvec.empty())
		std::cout << "   > myvec is empty\n";
	else
		std::cout << "   > myvec is not empty\n";
	if (myvec2.empty())
		std::cout << "   > myvec2 is empty\n";
	else
		std::cout << "   > myvec2 is not empty\n";
	if (origin.empty())
		std::cout << "   > origin is empty\n";
	else
		std::cout << "   > origin is not empty\n";
	std::cout << "-------\n";
	
	return ;
}
