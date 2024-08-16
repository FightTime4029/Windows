#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef int HTypeData;
typedef struct Heap
{
	HTypeData* _a;
	int _size;
	int _capacity;
}Heap;


void HeapInit(Heap* php, int* a, int n);
void AdjustDown(HTypeData* a, int n, int root);
void Swap(HTypeData* p1, HTypeData* p2);
void HeapDestory(Heap* php);
void HeapPush(Heap* php, HTypeData x);
void HeapPop(Heap* php,int n );
void HeapTop(Heap* php);