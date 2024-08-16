#define _CRT_SECURE_NO_WARNINGS
#include "Heap.h"

//������
//С��  ��������
//���  ��������
void HeapSort(int* a,int n)
{
	//������
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a,n, i);
	}
	//ѡ����С��  Ԫ�ؼ�һ
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		--end;
	}
}

int main()
{
	Heap hp;
	int array[] = { 27,15,19,18,28,34,65,49,25,37 };
	int sz = sizeof(array) / sizeof(array[0]);
	HeapInit(&hp, array, sz);
	HeapPush(&hp, 13);
	for (int i = 0;i < sz; i++)
	{
		printf("%d ", hp._a[i]);
	}
	return 0;
}