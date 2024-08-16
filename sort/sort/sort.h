#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//��������   O(N^2)
void InsertSort(int* a, int n);

//ϣ������ O(N^1.3 ~ N^2)
void ShellSort(int* a, int n);

//ѡ������  O(N^2)
void SelectSort(int* a, int n);

//������ O(N*logN)
void ADjustDown(int* a, int n, int root);
void HeapSort(int* a, int n);

//ð������ O(N^2)
void BubbleSort(int* a, int n);

//��������  //ʱ�临�Ӷ� O��N*logN��
		   //�ռ临�Ӷ� O��logN��
void QuickSort(int* a, int left, int right);

//��������ǵݹ�ʵ�֣���Ҫʹ�õ�ջ��
void QuickSortNonR(int* a,int left,int right);

//ģ��ջ û��ʵ��
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



//�鲢���� //ʱ�临�Ӷ� O��N*logN��
		   //�ռ临�Ӷ� O��N��
void MergeSort(int* a, int n);

//�鲢����ǵݹ�ʵ��
void MergeSortNonR(int* a, int n);


//��������  ʱ�临�Ӷ�  O��N+range��
		  //�ռ临�Ӷ� O��range��
void CountSort(int* a,int n);