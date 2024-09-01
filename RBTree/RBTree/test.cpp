#define _CRT_SECURE_NO_WARNINGS
#include "mymap.hpp"
#include "myset.hpp"
#include "RBTree.h"
using namespace std;






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


	//testset();
	//testmap();

	RBTree<int,int,sxj::map<int,int>::MapOfK> r;

	r.Insert(1, 1);
}