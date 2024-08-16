#define _CRT_SECURE_NO_WARNINGS


#include "bInarytreenode.h"

void PrevTreeNode(TreeNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%c ", root->data);
	PrevTreeNode(root->left);
	PrevTreeNode(root->right);
}



void InTreeNode(TreeNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	PrevTreeNode(root->left);
	printf("%c ", root->data);
	PrevTreeNode(root->right);
}


void PostTreeNode(TreeNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	PrevTreeNode(root->left);
	PrevTreeNode(root->right);
	printf("%c ", root->data);
}

int TreeSize(TreeNode* root)
{
	return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
}

int TreeLeafSize(TreeNode* root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;

	return TreeLeafSize(root->left) + TreeLeafSize(root->right);
}

//按理来说没有问题不知道什么情况?
int TreeHight(TreeNode* root)
{
	if (root == NULL)
		return 0;

	int leftdepth = TreeHight(root->left);
	int rightdepth = TreeHight(root->right);

		return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
}