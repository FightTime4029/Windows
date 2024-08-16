#define _CRT_SECURE_NO_WARNINGS
#include "Heap.h"

//堆排序
//小堆  降序排列
//大堆  升序排列
void HeapSort(int* a,int n)
{
	//构建堆
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a,n, i);
	}
	//选出次小的  元素减一
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