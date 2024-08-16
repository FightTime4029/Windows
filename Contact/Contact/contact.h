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

//����ͨѶ¼���˵�����
typedef struct PeoCont
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char phone[MAX_PHONE];
	char addr[MAX_ADDR];
}PeoCont;

//����ͨѶ¼
//typedef struct Contant
//{
//	PeoCont data[MAX];
//	int count;
//}cont;
//��̬�汾ͨѶ¼
typedef struct Contant
{
	PeoCont* data;
	int count;
	int max_count;
}cont;

//��ʼ��ͨѶ¼
int InitContant(cont* con);

//���ͨѶ¼��Ա
void Addcontant(cont* con);

//ɾ��ͨѶ¼��Ա
void Delcontant(cont* con);

//����ָ����ϵ��
void Searchtant(cont*con);

//�޸�ͨѶ¼��Ա��Ϣ
void Modifycontant(cont* con);

//չʾͨѶ¼
void showcontant(const cont* con);

//��ͨѶ¼��������
void sortcontant(const cont* con);

//����ͨѶ¼
void Destorycont(cont* con);

//����ͨѶ¼
void Saveconst(const cont* con);

//����ͨѶ¼
void load_contant(cont* con);
