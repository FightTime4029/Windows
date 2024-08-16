#define _CRT_SECURE_NO_WARNINGS
#include "contact.h"


void add_cont(cont* con)
{
	if (con->count == con->max_count)
	{
		PeoCont* str = (PeoCont*)realloc(con->data, (default_count + ADD_NEW_PEO) * sizeof(PeoCont));
		if (str != NULL)
		{
			con->data = str;
			con->max_count += ADD_NEW_PEO;
		}
		else
		{
			printf("Addcontant:%s", strerror(errno));
		}
	}
}

void load_contant(cont* con)
{
	FILE* create = fopen("contant.txt", "wb");
	fclose(create);
	create = NULL;
	FILE* pf_read = fopen("contant.txt", "rb");
	if (pf_read == NULL)
	{
		perror("load_contant");
	}

	PeoCont tmp = { 0 };

	while(fread(&tmp,sizeof(PeoCont),1,pf_read) == 1)
	{
		add_cont(con);

		con->data[con->count] = tmp;
		con->count++;
	}
	fclose(pf_read);
	pf_read = NULL;
}

int InitContant(cont* con)
{
	assert(con);
	con->count = 0;
	con->max_count = default_count;
	con->data =(PeoCont*)calloc(default_count, sizeof(PeoCont));

	if (con->data == NULL)
	{
		printf("InitContant:%s", strerror(errno));
		return 1;
	}

	load_contant(con);

	return 0;
}


static int find_by_name(const cont* con, const char name[])
{
	assert(con && name); 
	int i = 0;
	for (i=0;i<con->count;i++)
	{
		if (strcmp(con->data[i].name,name) == 0)
		{
			return i;
		}
	}
	return -1;
}


void Addcontant(cont* con)
{
	assert(con);
		add_cont(con);
	printf("��������Ҫ��ӵ�������>");
	scanf("%s", con->data[con->count].name);
	printf("��������Ҫ��ӵ����䣺>");
	scanf("%d", &(con->data[con->count].age));
	printf("��������Ҫ��ӵ��Ա�>");
	scanf("%s", con->data[con->count].sex);
	printf("��������Ҫ��ӵĵ绰��>");
	scanf("%s", con->data[con->count].phone);
	printf("��������Ҫ��ӵĵ�ַ��>");
	scanf("%s", con->data[con->count].addr);
	con->count++;
	printf("��ӳɹ�\n");
}


void Delcontant(cont* con)
{
	assert(con);

	char name[MAX_NAME] = { 0 };
	//����
	printf("��������Ҫɾ����ϵ�˵�������>");
	scanf("%s", name);
	if (con->count == 0)
	{
		printf("ͨѶ¼Ϊ�գ��޷�ɾ��\n");
	}
	//����
	int pos = find_by_name(con,name);
	if (pos == -1)
	{
		printf("�����������������\n");
		return;
	}
		
		
	//ɾ��
	int i = 0;
	for (i = pos; i < con->count - 1; i++)
	{
		/*memmove(con->data[pos], con->data[pos + 1], sizeof(con->data[0]));*/
		con->data[i] = con->data[i + 1];
	}

	con->count--;

	printf("ɾ���ɹ�\n");
}

void Searchtant(cont* con)
{
	assert(con);
	char name[MAX_NAME] = { 0 };
	printf("��������Ҫ���ҵ���ϵ��:>");
	scanf("%s",name);
	if (con->count == 0)
	{
		printf("ĿǰͨѶ¼Ϊ�գ��޷�����\n");
	}
	int pos = find_by_name(con,name);
	if (pos == -1)
	{
		printf("�޷��ҵ����������ϵ��\n");
		return;
	}
	printf("\t%-20s\t%-5s\t%-5s\t%-12s\t%-30s\n", "����", "����", "�Ա�", "�绰", "��ַ");
	printf("%-d\t%-20s\t%-5d\t%-5s\t%-12s\t%-30s\n", pos,
		con->data[pos].name,
		con->data[pos].age,
		con->data[pos].sex,
		con->data[pos].phone,
		con->data[pos].addr);
}


void Modifycontant(cont* con)
{
	assert(con);
	char name[MAX_NAME] = { 0 };
	char name1[MAX_NAME] = { 0 };
	int input = 0;
	printf("��������Ҫ�޸ĵ���ϵ������:>");
	scanf("%s", name);
	int pos = find_by_name(con, name);
	if (pos == -1)
	{
		printf("��Ҫ�޸ĵ���ϵ�˲�����\n");
		return;
	}

	printf("��������Ҫ��ӵ�������>");
	scanf("%s", con->data[pos].name);
	printf("��������Ҫ��ӵ����䣺>");
	scanf("%d", &(con->data[pos].age));
	printf("��������Ҫ��ӵ��Ա�>");
	scanf("%s", con->data[pos].sex);
	printf("��������Ҫ��ӵĵ绰��>");
	scanf("%s", con->data[pos].phone);
	printf("��������Ҫ��ӵĵ�ַ��>");
	scanf("%s", con->data[pos].addr);

	printf("�޸ĳɹ�\n");

}



void showcontant(const cont* con)
{
	int i = 0;
	printf("\t%-20s\t%-5s\t%-5s\t%-12s\t%-30s\n","����", "����", "�Ա�", "�绰", "��ַ");
	for (i = 0; i < con->count; i++)
	{
		
		printf("%-d\t%-20s\t%-5d\t%-5s\t%-12s\t%-30s\n", i,
												con->data[i].name,
												con->data[i].age,
												con->data[i].sex,
												con->data[i].phone,
												con->data[i].addr);
	}
}

int cmp_peo_by_name(const void* e1, const void* e2)
{
	return strcmp(((PeoCont*)e1)->name, ((PeoCont*)e2)->name);
}

void sortcontant(const cont* con)
{
	qsort(con->data, con->count, sizeof(PeoCont), cmp_peo_by_name);
	printf("����ɹ�\n");
}

void Saveconst(const cont* con)
{
	FILE* pf_write = fopen("contant.txt", "wb");
	if (pf_write == NULL)
	{
		perror("Saveconst��");
	}
	int i = 0;
	for (i = 0; i < con->count; i++)
	{
		fwrite(con->data + i, sizeof(PeoCont), 1, pf_write);
	}

	fclose(pf_write);
	pf_write = NULL;
}


void Destorycont(cont* con)
{
	assert(con);
	free(con->data);
	con->data = NULL;
}
