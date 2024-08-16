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


void PrevTreeNode(TreeNode* root); //二叉树前序遍历
void InTreeNode(TreeNode* root);   //二叉树中序遍历
void PostTreeNode(TreeNode* root); //二叉树后续遍历

int TreeSize(TreeNode* root);      //二叉树的个数
int TreeLeafSize(TreeNode* root);	//二叉树的叶子个数

int TreeHight(TreeNode* root);		//二叉树的最深深度