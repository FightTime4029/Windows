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
	//��ʼ������
	InitBoard(board, ROW, COL);
	DisplayBoard(board, ROW, COL);
	//����
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
			printf("���Ӯ\n");
			break;
		}
		else if (ret == '#')
		{
			printf("����Ӯ\n");
			break;

		}
		else if (ret == 'p')
		{
			printf("ƽ��\n");
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
			printf("�˳���Ϸ");
				break;
		default:
			printf("�����ַ�������������");
			break;
		}
	} while (input);
	return 0;
}