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
	printf("1.添加联系人        2.删除联系人\n");
	printf("3.查找联系人        4.修改联系人\n");
	printf("5.展示联系人        6.按照姓名排序\n");
	printf("0.保存并退出              \n");
}



int main()
{
	cont con;
	
	InitContant(&con);

	int input = 0;
	do
	{
		menu();
		printf("请输入你的操作:>");
		scanf("%d", &input);

		//检测input输入值
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
			printf("退出通讯录");
			break;
		default:
			printf("输入错误，重新输入\n");
			break;
		}
	} while(input);

	return 0;
}