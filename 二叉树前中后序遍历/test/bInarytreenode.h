#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef char DataType;

typedef struct BinaryTreeNode
{
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
	DataType data;
}TreeNode;


void PrevTreeNode(TreeNode* root); //������ǰ�����
void InTreeNode(TreeNode* root);   //�������������
void PostTreeNode(TreeNode* root); //��������������

int TreeSize(TreeNode* root);      //�������ĸ���
int TreeLeafSize(TreeNode* root);	//��������Ҷ�Ӹ���

int TreeHight(TreeNode* root);		//���������������