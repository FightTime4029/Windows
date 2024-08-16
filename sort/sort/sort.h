#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//插入排序   O(N^2)
void InsertSort(int* a, int n);

//希尔排序 O(N^1.3 ~ N^2)
void ShellSort(int* a, int n);

//选择排序  O(N^2)
void SelectSort(int* a, int n);

//堆排序 O(N*logN)
void ADjustDown(int* a, int n, int root);
void HeapSort(int* a, int n);

//冒泡排序 O(N^2)
void BubbleSort(int* a, int n);

//快速排序  //时间复杂度 O（N*logN）
		   //空间复杂度 O（logN）
void QuickSort(int* a, int left, int right);

//快速排序非递归实现（需要使用到栈）
void QuickSortNonR(int* a,int left,int right);

//模拟栈 没有实现
//typedef int StDataType;
//typedef struct Stack
//{
//	StDataType* a;
//	int size;
//	int capacity;
//}Stack;
//void StackInit(Stack* pst);
//void StackPush(Stack* pst, StDataType x);
//void StackPop(Stack* pst);
//StDataType StackTop(Stack* pst);
//int StackEmpty(Stack* pst);



//归并排序 //时间复杂度 O（N*logN）
		   //空间复杂度 O（N）
void MergeSort(int* a, int n);

//归并排序非递归实现
void MergeSortNonR(int* a, int n);


//计数排序  时间复杂度  O（N+range）
		  //空间复杂度 O（range）
void CountSort(int* a,int n);