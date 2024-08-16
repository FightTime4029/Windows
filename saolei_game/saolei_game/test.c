#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void menu()
{
	printf("********1.play*******\n");
	printf("********0.exit*******\n");
}

void game()
{
	int mine[ROWS][COLS] = { 0 };//雷信息
	int show[ROWS][COLS] = { 0 };//展示信息
	Initboard(mine,ROWS,COLS,'0');
	Initboard(show, ROWS, COLS, '*');
	//放入雷
	SetMine(mine, ROW, COL);
	//打印初始表
	DisplayBoard(show, ROW, COL);
	//DisplayBoard(mine, ROW, COL);
	Fined_Mine(mine, show, ROW, COL);//查询雷
}

int main() 
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("请选择:> ");
		scanf("%d", &input);

		switch(input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误，请重试\n");
		}
	} while (input);
	return 0;
}
