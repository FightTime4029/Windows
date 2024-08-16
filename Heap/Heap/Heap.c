#define _CRT_SECURE_NO_WARNINGS
#include "Heap.h"

void Swap(HTypeData* p1, HTypeData* p2)
{
	HTypeData tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
void AdjustDown(HTypeData* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;

	while (child < n)
	{
		if (child+1<n && a[child] > a[child+1])
		{
			++child;
		}
		if (a[parent] > a[child])
		{
			Swap(&a[parent],&a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void AdjustUp(HTypeData* a, int n, int child)
{
	int parent = (child - 1) / 2;

	while (child > 0)
	{
		if (a[parent] > a[child])
		{
			Swap(&a[parent], &a[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}

}

void HeapInit(Heap* php, int a[], int n)
{
	//初始化
	php->_a = (HTypeData*)malloc(sizeof(HTypeData) * n);

	memcpy(php->_a, a, sizeof(HTypeData) * n);

	php->_capacity = n;
	php->_size = n;

	//开始构建堆
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(php->_a, php->_size,i);
	}
}


void HeapDestory(Heap* php)
{
	assert(php);
	free(php->_a);
	php->_capacity = php->_size = 0;
}
void HeapPush(Heap* php, HTypeData x)
{
	assert(php);
	if (php->_capacity == php->_size)
	{
		php->_capacity *= 2;
		HTypeData* newheap = (HTypeData*)realloc(php->_a, sizeof(HTypeData) * php->_capacity);
		php->_a = newheap;
	}

	php->_a[php->_size++] = x;

	AdjustUp(php->_a, php->_size, php->_size-1);
}
void HeapPop(Heap* php,int n)
{
	assert(php);
	assert(php->_size);

	Swap(&php->_a, &php->_a[php->_size - 1]);
	php->_size--;
	AdjustDown(php, n, 0);

}
void HeapTop(Heap* php)
{
	assert(php);
	assert(php->_size);
	return php->_a[0];
}