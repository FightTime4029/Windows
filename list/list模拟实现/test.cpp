#define _CRT_SECURE_NO_WARNINGS
#include "list.h"

int main()
{
	sxj::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);
	lt.push_back(7);
	//lt.pop_back();
	//lt.pop_front();
	//lt.push_front(0);
	//lt.pop_front();



	sxj::list<int>::iterator it = lt.begin();
	while (it != lt.end())
	{
		std::cout << *it << ' ';
		++it;
	}
	std::cout << std::endl;


	for (auto e : lt)
	{
		std::cout << e << ' ';
	}
	std::cout << std::endl;
	return 0;
}