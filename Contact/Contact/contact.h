#pragma once

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#define MAX 100
#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_PHONE 12
#define MAX_ADDR 30
#define default_count 3
#define ADD_NEW_PEO 2

//定义通讯录中人的属性
typedef struct PeoCont
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char phone[MAX_PHONE];
	char addr[MAX_ADDR];
}PeoCont;

//定义通讯录
//typedef struct Contant
//{
//	PeoCont data[MAX];
//	int count;
//}cont;
//动态版本通讯录
typedef struct Contant
{
	PeoCont* data;
	int count;
	int max_count;
}cont;

//初始化通讯录
int InitContant(cont* con);

//添加通讯录成员
void Addcontant(cont* con);

//删除通讯录成员
void Delcontant(cont* con);

//查找指定联系人
void Searchtant(cont*con);

//修改通讯录成员信息
void Modifycontant(cont* con);

//展示通讯录
void showcontant(const cont* con);

//对通讯录进行排序
void sortcontant(const cont* con);

//销毁通讯录
void Destorycont(cont* con);

//保存通讯录
void Saveconst(const cont* con);

//加载通讯录
void load_contant(cont* con);
