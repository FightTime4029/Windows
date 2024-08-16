#define _CRT_SECURE_NO_WARNINGS

#include "sort.h"

void printarray(int* a,int n)
{
	assert(a);

	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void TestInsertSort()
{
	int a[] = { 4,8,9,3,5,8,2,6,1,0 };
	printarray(a, sizeof(a) / sizeof(a[0]));

	InsertSort(a, sizeof(a) / sizeof(a[0]));

	printarray(a, sizeof(a) / sizeof(a[0]));
}

void TestShellSort()
{
	int a[] = { 4,8,9,3,5,8,2,6,1,0 };
	printarray(a, sizeof(a) / sizeof(a[0]));

	ShellSort(a, sizeof(a) / sizeof(a[0]));

	printarray(a, sizeof(a) / sizeof(a[0]));
}

void TestSelectSort()
{
	int a[] = { 4,8,9,3,5,8,2,6,1,0 };
	printarray(a, sizeof(a) / sizeof(a[0]));

	SelectSort(a, sizeof(a) / sizeof(a[0]));

	printarray(a, sizeof(a) / sizeof(a[0]));
}

void TestHeapSort()
{
	int a[] = { 4,8,9,3,5,8,2,6,1,0 };
	printarray(a, sizeof(a) / sizeof(a[0]));

	HeapSort(a, sizeof(a) / sizeof(a[0]));

	printarray(a, sizeof(a) / sizeof(a[0]));
}

void TestBubbleSort()
{
	int a[] = { 4,8,9,3,5,8,2,6,1,0 };
	printarray(a, sizeof(a) / sizeof(a[0]));

	BubbleSort(a, sizeof(a) / sizeof(a[0]));

	printarray(a, sizeof(a) / sizeof(a[0]));
}

void TestQuickSort()
{
	int a[] = { 4,8,9,3,5,8,2,6,1,0 };
	printarray(a, sizeof(a) / sizeof(a[0]));

	QuickSort(a,0, sizeof(a) / sizeof(a[0])-1);

	printarray(a, sizeof(a) / sizeof(a[0]));
}

void TestMergeSort()
{
	int a[] = { 4,8,9,3,5,8,2,6,1,0 };
	printarray(a, sizeof(a) / sizeof(a[0]));

	MergeSort(a,sizeof(a) / sizeof(int));

	printarray(a, sizeof(a) / sizeof(a[0]));
}

void TestMergeSortNonR()
{
	int a[] = { 4,8,9,3,5,8,2,6,1,0 };
	printarray(a, sizeof(a) / sizeof(a[0]));

	MergeSortNonR(a, sizeof(a) / sizeof(int));

	printarray(a, sizeof(a) / sizeof(a[0]));
}

void TestCountSort()
{
	int a[] = { 4,8,9,3,5,8,2,6,1,0 };
	printarray(a, sizeof(a) / sizeof(a[0]));

	CountSort(a, sizeof(a) / sizeof(int));

	printarray(a, sizeof(a) / sizeof(a[0]));
}

int main()
{
	TestCountSort();
	return 0;
}