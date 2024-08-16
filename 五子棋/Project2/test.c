#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game.h"


void menu()
{
	printf("***********************************\n");
	printf("************  1.play    ***********\n");
	printf("************  0.exit    ***********\n");
	printf("***********************************\n");

}

void game()
{
	char ret = 0;
	char board[ROW][COL] = { 0 };
	//初始化棋盘
	InitBoard(board, ROW, COL);
	DisplayBoard(board, ROW, COL);
	//下棋
	while (1)
	{
		PlayerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		ret = IsWin(board,ROW,COL);
		if (ret != 'c')
		{
			break;
		}
		
		ComputerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'c')
		{
			break;
		}
		if (ret == '*')
		{
			printf("玩家赢\n");
			break;
		}
		else if (ret == '#')
		{
			printf("电脑赢\n");
			break;

		}
		else if (ret == 'p')
		{
			printf("平局\n");
			break;

		}
	}
}
int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		scanf("%d", &input);
		printf("\n");
		switch (input)
		{
		case 1 :
			game();
			break;
		case 0:
			printf("退出游戏");
				break;
		default:
			printf("错误字符，请重新输入");
			break;
		}
	} while (input);
	return 0;
}