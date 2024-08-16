#include "game.h"
#include <stdlib.h>
#include <time.h>
void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = '  ';
		}
	}
}

void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		int j = 0;
		//��ӡ����
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if(j<col-1)
			printf("|");
		}
		printf("\n");
		//�ָ����
		if(i<row-1)
		{
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
					printf("|");
			}
			printf("\n");
		}
	}
}


void PlayerMove(char board[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;
	printf("�������:>\n");
	printf("���������꣺  ");
	scanf("%d%d", &x, &y);
	//�ж�x,y�Ƿ�Ϸ�
	if (x > 0 && x <= row && y >= 1 && y <= col)
	{
		if (board[x - 1][y - 1] == ' ')
		{
			board[x - 1][y - 1] = '*';
		}
		else
		{
			printf("���걻ռ��, ��������\n");
		}
	}
	else
	{
		printf("��������, ��������\n");
	}
}


ComputerMove(char board[ROW][COL], int row, int col)
{
	printf("��������:>\n");
	int x = 0;
	int y = 0;
	while (1)
	{
		x = rand() % row;
		y = rand() % col;
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}

	}
}
//�ж������Ƿ��� ���˷���1
//δ������0
int IsFull(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				return 0;
		}
	}
	return 1;
}

char IsWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	//�ж���

	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
		{
			return board[i][1];
		}
	} 
	//�ж���

	int j = 0;
	for (j = 0; j < col; j++)
	{
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ')
		{
			return board[1][j];
		}
	}
	//�ж϶Խ�
	
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
		{
			return board[1][1];
		}
		if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
		{
			return board[1][1];
		}

		//���̷��� ��ûʤ��

		if (IsFull(board, row, col))
		{
			printf("ƽ��");
			return 'q';
		}

		return 'c';
}