#define _CRT_SECURE_NO_WARNINGS
#include "mymap.hpp"
#include "myset.hpp"
using namespace std;


void testmap()
{
	sxj::map<int, int> m;
	m.Insert(make_pair(1, 1));
	m.Insert(make_pair(2, 2));
	m.Insert(make_pair(3, 3));
}


void testset()
{
	sxj::set<int> s;
	s.Insert(1);
	s.Insert(2);
	s.Insert(3);

}
int main()
{
	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7,16,14};
	//RBTree<int, int> t;
	//for (auto e : a)
	//{
	//	t.Insert(make_pair(e, e));
	//}

	//t.Inorder();
	//return 0;


	testset();
	testmap();
}