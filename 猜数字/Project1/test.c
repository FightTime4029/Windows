#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include<time.h>

void menu()
{
	printf("*********************\n");
	printf("*****1.play game*****\n");
	printf("*****0.exit game*****\n");
	printf("*********************\n");
}
void game()
{
	int guess = 0;
	int ret = rand()%100+1;//���������
	printf("��һ��\n");
	while (1)
	{
		scanf("%d", &guess);
		if (guess < ret)
			printf("��С��\n");
		else if (guess > ret)
			printf("�´���\n");
		else {
			printf("��ϲ�㣬�¶���\n");
			break;
		}
	}
}
int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));//����һ��ʱ���������ǿ��ת����int����
	do
	{
		menu();
		scanf("%d", &input);
		switch(input) 
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ");
			break;
		default:
			printf("��⵽�������\n");
			break;
		}
	} while (input);
	return 0;
}