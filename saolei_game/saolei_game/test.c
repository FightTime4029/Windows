#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void menu()
{
	printf("********1.play*******\n");
	printf("********0.exit*******\n");
}

void game()
{
	int mine[ROWS][COLS] = { 0 };//����Ϣ
	int show[ROWS][COLS] = { 0 };//չʾ��Ϣ
	Initboard(mine,ROWS,COLS,'0');
	Initboard(show, ROWS, COLS, '*');
	//������
	SetMine(mine, ROW, COL);
	//��ӡ��ʼ��
	DisplayBoard(show, ROW, COL);
	//DisplayBoard(mine, ROW, COL);
	Fined_Mine(mine, show, ROW, COL);//��ѯ��
}

int main() 
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("��ѡ��:> ");
		scanf("%d", &input);

		switch(input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("�������������\n");
		}
	} while (input);
	return 0;
}
