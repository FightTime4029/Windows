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
	int ret = rand()%100+1;//生成随机数
	printf("猜一猜\n");
	while (1)
	{
		scanf("%d", &guess);
		if (guess < ret)
			printf("猜小了\n");
		else if (guess > ret)
			printf("猜大了\n");
		else {
			printf("恭喜你，猜对了\n");
			break;
		}
	}
}
int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));//生成一个时间戳并将其强制转换成int类型
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
			printf("退出游戏");
			break;
		default:
			printf("检测到输入错误\n");
			break;
		}
	} while (input);
	return 0;
}