#define _CRT_SECURE_NO_WARNINGS
#include "sort.h"

void Swap(int* a,int *b)
{
	assert(a && b);

	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//�������� O(N^2)
void InsertSort(int* a, int n)
{
	assert(a);
	//���ƶ��ٴ�
	for (int i = 0; i < n - 1; ++i)
	{
		//��������
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			//���end+1С��end end���-- 
			if (tmp < a[end])
			{
				//����end + 1������ ��end������ǰŲ�� ֱ���ҵ�end + 1����end��λ��
				a[end + 1] = a[end];
				--end;
			}
			else
			{
				break;
			}
			//��tmp�ŵ�end + 1��λ��
			a[end + 1] = tmp;
		}
	}

}


//ϣ������ O(N^1.3 ~ N^2)
void ShellSort(int* a, int n)
{
	int gap=n;
	while (gap>1)
	{
		gap = gap / 3 + 1;//��֤���һ��Ϊ1
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

//ѡ������ O(N^2)
//����ѡ������������������ ����Ӧ��ѡ��һ����
void SelectSort(int* a, int n)
{
	assert(a);

	int begin = 0, end = n - 1;

	
	while (begin < end)
	{
		int maxi = 0;
		int mini = 0;
		maxi = mini = begin;
		//�ҳ����ֵ���ұ� �ҳ���Сֵ�����
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
			//���max��begin�ص� ��Ҫ��begin��������
		maxi = mini;


		Swap(&a[end] ,&a[maxi]);

		++begin;
		--end;
	}
}


//������ O(N*logN)
void ADjustDown(int* a, int n, int root)
{
	//���
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
	//������
	for (int i = (n-1-1)/2; i >=0; --i)
	{
		ADjustDown(a, n, i);
	}
	

	//������ ��Ҫ���򽨴�� ����С��
	int end = n - 1;
	while (end>0)
	{
		Swap(&a[0], &a[end]);
		ADjustDown(a, end, 0);
		end--;
	}

}

//ð������ O(N^2)
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

//��������  O(N*logN) �� O(N^2)
//��Ҫ��֤������
//�������� ѡ����������Ҳ������С��  ������ȡ�з��Ļ� �Ͳ�������������
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

//����ָ�뷨
int PartSort1(int* a,int begin,int end)
{
	assert(a);
	//keyѡ�������������Ҫ��end���ұߣ�����  keyѡ�����ұ� begin����ߣ���Ҫ����	
	int midindex = GetMidIndex(a, begin, end);
	Swap(&a[midindex], &a[end]);
	int keyindex = end;
	while (begin < end)
	{
		//�������һ����key�����
		while (begin < end && a[begin] <= a[keyindex])
		{
			++begin;
		}
		//���ұ���һ����keyС����
		while (begin < end && a[end]>= a[keyindex])
		{
			--end;
		}
		//���� ��С����������ߣ�����������ұ�
		Swap(&a[begin], &a[end]);
	}
	//begin��end�ཻ��λ�� �����ǵ�key  ����˵key��õ����������λ�����߿�����λ��
	Swap(&a[begin], &a[keyindex]);
	return begin;
}

//�ڿӷ�  �Ƚ��Ƽ�ʹ��
//�ȽϺ���� ѡ�ұߵ��� ��Ҫ�������  ��Ϊ�п���Ҫȥ����Ҹ��ȿӴ��ֵȥ���
//����� ����������µĿ� ȥ�ұ��ұȿ�С��ֵȥ���µĿ� �Դ�ѭ��
int PartSort2(int* a,int begin,int end)
{
	assert(a);
	int midindex = GetMidIndex(a, begin, end);
	Swap(&a[end], &a[midindex]);
	//�ڿ� 
	int key = a[end];

	while (begin < end)
	{
		if (begin < end && a[begin] <= key)
		{
			++begin;
		}
		//����ҵ���key����� �ŵ��ӵ�λ����ӣ� begin��λ�þͱ���µĿ�
		a[end] = a[begin];

		if (begin < end && a[end] >= key)
		{
			--end;
		}
		//�ұ��ҵ�һ����keyС���� �ŵ�begin���ڵĿӣ� end��λ�þͱ���µÿ�
		a[begin] = a[end];
	}

	a[begin] = key;
	return begin;
}

//ǰ��ָ�뷨
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

//ʱ�临�Ӷ� O��N*logN��
//�ռ临�Ӷ� O��logN��
void QuickSort(int* a, int left,int right)
{
	assert(a);

	if (left >= right)
		return;

	//�ݹ�������Ԫ�ش���10�����ÿ���
	if ((right - left + 1) > 10)
	{
		int div = PartSort3(a, left, right);
		QuickSort(a, left, div - 1);
		QuickSort(a, div + 1, right);
	}
	else //����Ԫ��С��10 û��Ҫȥ�ݹ��˷��ڴ� ʹ�ò���������ý��
	{
		InsertSort(a + left, right - left + 1);
	}
		
}


//��������ǵݹ�ʵ�֣���Ҫʹ�õ�ջ��
//�ݹ�ķǵݹ����ַ�����ֱ�Ӹ�ѭ����쳲��������У� ջģ��洢���ݷǵݹ�
//�ǵݹ飺1.���Ч�ʣ��ݹ齨��ջ֡���������ĵģ������ִ���������Ժ��Բ��ƣ�����Ż�΢����΢��
//        2.�ݹ�����ȱ���ǣ����ջ֡�����̫����׵���ջ�������Ϊϵͳջ�ռ�һ�㲻����M����
//		  ���ݽṹջģ��ǵݹ飬�����Ǵ洢�ڶ��ϣ�����G����Ŀռ�
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

//ʱ�临�Ӷ� O��N*logN��
//�ռ临�Ӷ� O��N��
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
	//�ѹ鲢�õ������ٿ�����ԭ����
	for (int i = left; i <= right; ++i)
	{
		a[i] = tmp[i];
	}
}
void _MergeSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
		return;
	//�ݹ�
	int midindex = (left + right) / 2;
	_MergeSort(a, left, midindex, tmp);
	_MergeSort(a, midindex + 1, right, tmp);

	//�鲢
	MergeArr(a, left, midindex, midindex + 1, right, tmp);
}

void MergeSort(int* a, int n)
{
	assert(a);
	int* tmp = malloc(sizeof(int) * n);

	_MergeSort(a, 0, n - 1, tmp);

	free(tmp);

}

//�鲢����ǵݹ�ʵ��
void MergeSortNonR(int* a, int n)
{
	assert(a);
	int* tmp = malloc(sizeof(int) * n);
	//ÿ�����е����ݸ���
	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			//�ϲ�ֻ��һ�� ����ϲ�ֱ��break
			if (begin2 >= n)
				break;
			//����ڶ��������С��gap �Եڶ��������������������
			if (end2 > n)
				end2 = n - 1;
			//[i,i+gap-1]  [i+gap,i+2*gap-1] ��������й鲢
			MergeArr(a,begin1,end1,begin2,end2, tmp);
		}
		//��һ�� һ������һ�����ݹ鲢���� �ڶ��� ���������������ݹ鲢����
		gap = gap * 2;
	}

	free(tmp);
}

void _MergeFile(const char* file1, const char* file2, const char* mfile)
{
	FILE* fout1 = fopen(file1, "r");
	if (fout1 == NULL)
	{
		perror("�ļ���ʧ��");
	}
	FILE* fout2 = fopen(file2, "r");
	if (fout2 == NULL)
	{
		perror("�ļ���ʧ��");
	}
	FILE* fin = fopen(mfile, "w");
	if (fin == NULL)
	{
		perror("�ļ���ʧ��");
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
		perror("�ļ���ʧ��");
	}
	//�ָ��С�ļ�
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
				perror("fin��ʧ��");
			}
			for (int i = 0; i < n; i++)
			{
				fprintf(fin,"%d\n", a[i]);
			}

			fclose(fin);
			i = 0;
		}
	}



	//�ڴ�����ʹ�ù鲢�㷨��������Ҳ���������Ѿ����������С�ļ� ѡ��С�ķŵ��µ��ļ�
	char file1[100] = "1";
	char file2[100] = "";
	char mfile[100] = "12";

	//һ���������ļ�
	for (int i = 2; i <= n; i++)
	{
		sprintf(file2, "%d", i);

		_MergeFile(file1, file2, mfile);

		strcpy(file1, mfile);

		sprintf(mfile, "%s%d", mfile, i + 1);
	}

	fclose(fout);
}


//�������� ʱ�临�Ӷ�  O��N+range��
		  //�ռ临�Ӷ� O��range��
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
	//��ԭ�����ֵ-ԭ�������Сֵ ӳ�䵽���ٵ������� ����һ��++һ��
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
