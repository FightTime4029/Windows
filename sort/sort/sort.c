#define _CRT_SECURE_NO_WARNINGS
#include "sort.h"

void Swap(int* a,int *b)
{
	assert(a && b);

	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//插入排序 O(N^2)
void InsertSort(int* a, int n)
{
	assert(a);
	//控制多少次
	for (int i = 0; i < n - 1; ++i)
	{
		//单次排序
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			//如果end+1小于end end向后-- 
			if (tmp < a[end])
			{
				//保存end + 1的数据 将end依次往前挪动 直到找到end + 1大于end的位置
				a[end + 1] = a[end];
				--end;
			}
			else
			{
				break;
			}
			//将tmp放到end + 1的位置
			a[end + 1] = tmp;
		}
	}

}


//希尔排序 O(N^1.3 ~ N^2)
void ShellSort(int* a, int n)
{
	int gap=n;
	while (gap>1)
	{
		gap = gap / 3 + 1;//保证最后一个为1
		for (int i = 0; i < n - gap; ++i)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (tmp < a[end])
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}

//选择排序 O(N^2)
//这里选择了两个数进行排序 正常应该选择一个数
void SelectSort(int* a, int n)
{
	assert(a);

	int begin = 0, end = n - 1;

	
	while (begin < end)
	{
		int maxi = 0;
		int mini = 0;
		maxi = mini = begin;
		//找出最大值放右边 找出最小值放左边
		for (int i = begin+1; i <= end; i++)
		{
			if (a[i] < a[mini])
			{
				mini = i;
			}

			if (a[i] > a[maxi])
			{
				maxi = i;
			}
		}

		Swap(&a[begin] ,&a[mini]);
		if (begin == maxi)
			//如果max和begin重叠 需要对begin进行修正
		maxi = mini;


		Swap(&a[end] ,&a[maxi]);

		++begin;
		--end;
	}
}


//堆排序 O(N*logN)
void ADjustDown(int* a, int n, int root)
{
	//大堆
	assert(a);
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child+1 < n && a[child] < a[child + 1])
		{
			++child;
		}

		if (a[parent] < a[child])
		{
			Swap(&a[child] ,&a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int* a, int n)
{
	//构建堆
	for (int i = (n-1-1)/2; i >=0; --i)
	{
		ADjustDown(a, n, i);
	}
	

	//堆排序 想要升序建大堆 降序建小堆
	int end = n - 1;
	while (end>0)
	{
		Swap(&a[0], &a[end]);
		ADjustDown(a, end, 0);
		end--;
	}

}

//冒泡排序 O(N^2)
void BubbleSort(int* a, int n)
{
	assert(a);
	int end = n;
	while (end >0)
	{
		int exchange = 0;
		for (int i = 1; i < end; i++)
		{
			if (a[i - 1] > a[i])
			{
				Swap(&a[i - 1], &a[i]);
				exchange = 1;
			}
		}
		if (exchange == 0)
			break;
		--end;
	}
	
}

//快速排序  O(N*logN) 到 O(N^2)
//需要保证闭区间
//三个数中 选出不是最大的也不是最小的  有三数取中法的话 就不会有最坏的情况了
int GetMidIndex(int* a, int begin, int end)
{
	int mid = begin + end / 2;
	if (a[begin] < a[mid])
	{
		if (a[mid] < a[end])
		{
			return mid;
		}
		else if (a[mid] > a[end])
		{
			if (a[begin] < a[end])
			{
				return end;
			}
			else
			{
				return begin;
			}
		}
	}
	else
	{
		if (a[mid] > a[end])
		{
			return mid;
		}
		else if (a[mid] < a[end])
		{
			if (a[begin] < a[end])
			{
				return begin;
			}
			else
			{
				return end;
			}
		}
	}
}

//左右指针法
int PartSort1(int* a,int begin,int end)
{
	assert(a);
	//key选择最左边我们需要让end（右边）先走  key选择最右边 begin（左边）需要先走	
	int midindex = GetMidIndex(a, begin, end);
	Swap(&a[midindex], &a[end]);
	int keyindex = end;
	while (begin < end)
	{
		//在左边找一个比key大的数
		while (begin < end && a[begin] <= a[keyindex])
		{
			++begin;
		}
		//在右边找一个比key小的数
		while (begin < end && a[end]>= a[keyindex])
		{
			--end;
		}
		//交换 将小的数放在左边，大的数放在右边
		Swap(&a[begin], &a[end]);
	}
	//begin和end相交的位置 放我们的key  所以说key最好的情况就是中位数或者靠近中位数
	Swap(&a[begin], &a[keyindex]);
	return begin;
}

//挖坑法  比较推荐使用
//比较好理解 选右边当坑 需要左边先走  因为有坑需要去左边找个比坑大的值去填坑
//填完坑 左边又有了新的坑 去右边找比坑小的值去填新的坑 以此循环
int PartSort2(int* a,int begin,int end)
{
	assert(a);
	int midindex = GetMidIndex(a, begin, end);
	Swap(&a[end], &a[midindex]);
	//挖坑 
	int key = a[end];

	while (begin < end)
	{
		if (begin < end && a[begin] <= key)
		{
			++begin;
		}
		//左边找到比key大的数 放到坑的位置填坑， begin的位置就变成新的坑
		a[end] = a[begin];

		if (begin < end && a[end] >= key)
		{
			--end;
		}
		//右边找到一个比key小的数 放到begin所在的坑， end的位置就变成新得坑
		a[begin] = a[end];
	}

	a[begin] = key;
	return begin;
}

//前后指针法
int PartSort3(int* a,int begin,int end)
{
	assert(a);
	int midindex = GetMidIndex(a,begin,end);
	Swap(&a[midindex], &a[end]);
	int keyindex = end;
	int cur = begin;
	int prev = begin-1;

	while (cur<end)
	{
		if (a[cur] <= a[keyindex] && ++prev != cur)
		{
			Swap(&a[cur], &a[prev]);
		}
			++cur;
	}
	Swap(&a[++prev], &a[keyindex]);
	return prev;
}

//时间复杂度 O（N*logN）
//空间复杂度 O（logN）
void QuickSort(int* a, int left,int right)
{
	assert(a);

	if (left >= right)
		return;

	//递归进来如果元素大于10就是用快排
	if ((right - left + 1) > 10)
	{
		int div = PartSort3(a, left, right);
		QuickSort(a, left, div - 1);
		QuickSort(a, div + 1, right);
	}
	else //否则元素小于10 没必要去递归浪费内存 使用插入排序更好解决
	{
		InsertSort(a + left, right - left + 1);
	}
		
}


//快速排序非递归实现（需要使用到栈）
//递归改非递归两种方法：直接改循环（斐波那契数列） 栈模拟存储数据非递归
//非递归：1.提高效率（递归建立栈帧还是有消耗的，但是现代计算机可以忽略不计，这个优化微乎其微）
//        2.递归最大的缺陷是，如果栈帧的深度太深，容易导致栈溢出。因为系统栈空间一般不大，在M级别
//		  数据结构栈模拟非递归，数据是存储在堆上，堆是G级别的空间
//void QuickSortNonR(int* a, int left, int right)
//{
//	assert(a);
//
//	Stack st;
//	StackInit(&st);
//
//	StackPush(&st,right);
//	StackPush(&st, left);
//
//	while (!StackEmpty)
//	{
//		int begin = StackTop(&st);
//		StackPop(&st);
//		int end = StackTop(&st);
//		StackPop(&st);
//
//
//		int div = PartSort3(a, begin, end);
//
//		if (begin < div - 1)
//		{
//			StackPush(&st, div - 1);
//			StackPush(&st, begin);
//		}
//
//		if (div+1 < end)
//		{
//			StackPush(&st, end);
//			StackPush(&st, div + 1);
//		}
//	}
//}

//时间复杂度 O（N*logN）
//空间复杂度 O（N）
void MergeArr(int* a,int begin1,int end1,int begin2,int end2,int* tmp)
{
	int left = begin1, right = end2;
	int index = begin1;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
			tmp[index++] = a[begin2++];
	}

	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
	//把归并好的数据再拷贝回原数组
	for (int i = left; i <= right; ++i)
	{
		a[i] = tmp[i];
	}
}
void _MergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
		return;
	//递归
	int midindex = (left + right) / 2;
	_MergeSort(a, left, midindex, tmp);
	_MergeSort(a, midindex + 1, right, tmp);

	//归并
	MergeArr(a, left, midindex, midindex + 1, right, tmp);
}

void MergeSort(int* a, int n)
{
	assert(a);
	int* tmp = malloc(sizeof(int) * n);

	_MergeSort(a, 0, n - 1, tmp);

	free(tmp);

}

//归并排序非递归实现
void MergeSortNonR(int* a, int n)
{
	assert(a);
	int* tmp = malloc(sizeof(int) * n);
	//每个组中的数据个数
	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			//合并只有一组 无需合并直接break
			if (begin2 >= n)
				break;
			//如果第二组的数据小于gap 对第二组进行数据数量的修正
			if (end2 > n)
				end2 = n - 1;
			//[i,i+gap-1]  [i+gap,i+2*gap-1] 两个组进行归并
			MergeArr(a,begin1,end1,begin2,end2, tmp);
		}
		//第一次 一个数据一个数据归并排序 第二次 两个数据两个数据归并排序
		gap = gap * 2;
	}

	free(tmp);
}

void _MergeFile(const char* file1, const char* file2, const char* mfile)
{
	FILE* fout1 = fopen(file1, "r");
	if (fout1 == NULL)
	{
		perror("文件打开失败");
	}
	FILE* fout2 = fopen(file2, "r");
	if (fout2 == NULL)
	{
		perror("文件打开失败");
	}
	FILE* fin = fopen(mfile, "w");
	if (fin == NULL)
	{
		perror("文件打开失败");
	}
	int num1;
	int num2;
	int ret1 = fscanf(fout1, "%d\n",&num1);
	int ret2 = fscanf(fout2, "%d\n",&num2);
	while (ret1 != EOF && ret2 != EOF)
	{
		if (num1 < num2)
		{
			fprintf(fin, "%d\n", num1);
			ret1 = fscanf(fout1, "%d\n", &num1);

		}
		else
		{
			fprintf(fin, "%d\n", num2);
			ret2 = fscanf(fout2, "%d\n", &num2);
		}
	}

	while (ret1 != EOF)
	{
		fprintf(fin, "%d\n", num1);
		ret1 = fscanf(fout1, "%d\n", &num1);
	}

	while (ret2 != EOF)
	{
		fprintf(fin, "%d\n", num2);
		ret2 = fscanf(fout2, "%d\n", &num2);
	}

	fclose(fout1);
	fclose(fout2);
	fclose(fin);
}


void MergeSortFile(const char* file)
{
	assert(file);
	FILE* fout = fopen(file, "r");
	if (fout == NULL)
	{
		perror("文件打开失败");
	}
	//分割成小文件
	int num = 0;
	int n = 10;
	int a[10] = { 0 };
	int i = 0;
	int filei = 1;
	char subfile[20] = { 0 };

	while (fscanf(fout, "%d", &num) != EOF)
	{
		if (i < n-1)
		{
			a[i++] = num;
		}
		else
		{
			a[i] = num;
			QuickSort(a, 0, n - 1);
			sprintf(subfile, "%d", filei++);
			FILE* fin = fopen(subfile, "w");
			if (fin == NULL)
			{
				perror("fin打开失败");
			}
			for (int i = 0; i < n; i++)
			{
				fprintf(fin,"%d\n", a[i]);
			}

			fclose(fin);
			i = 0;
		}
	}



	//在磁盘中使用归并算法进行排序也即无数个已经被排序过的小文件 选出小的放到新的文件
	char file1[100] = "1";
	char file2[100] = "";
	char mfile[100] = "12";

	//一共有三个文件
	for (int i = 2; i <= n; i++)
	{
		sprintf(file2, "%d", i);

		_MergeFile(file1, file2, mfile);

		strcpy(file1, mfile);

		sprintf(mfile, "%s%d", mfile, i + 1);
	}

	fclose(fout);
}


//计数排序 时间复杂度  O（N+range）
		  //空间复杂度 O（range）
void CountSort(int* a, int n)
{
	assert(a);
	int i = 0;
	int min = a[0];
	int max = a[0];
	for ( i = 0; i < n; ++i)
	{
		if (a[i] < min)
			min = a[i];
		if (a[i] > max)
			max = a[i];
	}
	int range = max - min + 1;
	int* CountArr = (int*)malloc(sizeof(int) * range);
	memset(CountArr, 0, sizeof(int) * range);
	//将原数组的值-原数组的最小值 映射到开辟的数组中 出现一次++一次
	for ( i = 0; i < n; ++i)
	{
		CountArr[a[i] - min]++;
	}

	int index = 0;
	for (int j = 0; j<range; ++j)
	{
		while (CountArr[j]--)
		{
			a[index++] = j + min;
		}
	}
}
