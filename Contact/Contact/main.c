#define _CRT_SECURE_NO_WARNINGS
#include "contact.h"

enum contant
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT,
};


void menu()
{
	printf("1.�����ϵ��        2.ɾ����ϵ��\n");
	printf("3.������ϵ��        4.�޸���ϵ��\n");
	printf("5.չʾ��ϵ��        6.������������\n");
	printf("0.���沢�˳�              \n");
}



int main()
{
	cont con;
	
	InitContant(&con);

	int input = 0;
	do
	{
		menu();
		printf("��������Ĳ���:>");
		scanf("%d", &input);

		//���input����ֵ
		switch (input)
		{
		case ADD:
			Addcontant(&con);
			break;
		case DEL:
			Delcontant(&con);
			break;
		case SEARCH:
			Searchtant(&con);
			break;
		case MODIFY:
			Modifycontant(&con);
			break;
		case SHOW:
			showcontant(&con);
			break;
		case SORT:
			sortcontant(&con);
			break;
		case EXIT:
			Saveconst(&con);
			Destorycont(&con);
			printf("�˳�ͨѶ¼");
			break;
		default:
			printf("���������������\n");
			break;
		}
	} while(input);

	return 0;
}