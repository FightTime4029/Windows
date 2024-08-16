#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

//
template<class T1, class T2>
class A
{
//private:
//	T1 a [N];
};

//模板特化 全特化
template<>
class A<int , char>
{
};


template<class T1,class T2>
class A<T1*, T2*>
{
};


//偏特化
template<class T2>
class A<int, T2>
{
};


void test_set()
{
	set<int> s;
	s.insert(1);
	s.insert(5);
	s.insert(6);
	s.insert(7);
	s.insert(4);
	s.insert(3);
	
	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;

	s.erase(3);

	for (auto e : s)
	{
		cout << e << ' ';
	}
	cout << endl;
}



void test_map()
{
	map<string, int> m;
	m.insert(pair<string, int>("樱桃", 1));
	m.insert(make_pair("西瓜", 1));

	for (auto& e : m)
	{
		cout << e.first << ' ' << e.second << endl;
	}
}
int main()
{
	//A<int, 1000> ar;
	//A<int, char> ar;
	//A<int, double> ar1;

	/*int i = 10;
	int j = 1;
	int const* p2 = &i;
	p2 = &j;*/

	//test_set();

	test_map();

	return 0;
}