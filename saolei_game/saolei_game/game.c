#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

void Initboard(char board[ROWS][COLS], int rows, int cols, char set)//��ʼ������
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		} 
	}
}


void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i= 0;
	int j = 0;
	printf("----ɨ����Ϸ----\n");
	for (j = 0;j <= col; j++)
	{
		printf("%d ", j);
	}
	printf("\n");
	for (i = 1; i <=row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ",board[i][j]);
		}
		printf("\n");
	}
	printf("----ɨ����Ϸ----\n");

}



void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = eazy_count;
	int x = 0;
	int y = 0;
	while (count)
	{
		x = rand() % row + 1;
		y = rand() % col + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
		}
		count--;
	}
}

int get_mine_count(char mine[ROWS][COLS], int x, int y)
{
	return (mine[x - 1][y] +
		mine[x - 1][y - 1]+
	mine[x][y - 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x][y + 1] +
		mine[x - 1][y + 1] - 8 * '0');
}

int Fined_Mine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0;
	while (win<row*col-eazy_count)
	{
		printf("������Ҫ�Ų������:>");
		scanf("%d%d", &x, &y);
		win++;
		if (x > 0 && x <= row && y > 0 && y <= col)
		{
			if (mine[x][y] == '1')
			{
				DisplayBoard(mine, ROW, COL);
				printf("BOOM! �㱻ը����\n");
				break;
			}
			else
			{
				show[x][y] = get_mine_count(mine, x, y)+'0';
				DisplayBoard(show, ROW, COL);
			}
		}
		else
		{
			printf("����������������������\n");
		}

	}


	if (win == row * col - eazy_count)
	{
		printf("��ϲ�㣡���׳ɹ�\n");
		DisplayBoard(show, ROW, COL);
	}
}




