#define _CRT_SECURE_NO_WARNINGS
#include "AVLTree.hpp"
using namespace std;

int main()
{
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7,16,14};
	AVLTree<int, int> t;
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}

	t.Inorder();
	cout<<t.IsBalance()<<endl;
	return 0;
}