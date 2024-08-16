#define _CRT_SECURE_NO_WARNINGS
#include "bInarytreenode.h"

int main()
{
	TreeNode* A = (TreeNode*)malloc(sizeof(TreeNode));
	A->data = 'A';
	A->left = NULL ;
	A->right = NULL;
	TreeNode* B = (TreeNode*)malloc(sizeof(TreeNode));
	B->data = 'B';
	B->left = NULL;
	B->right = NULL;
	TreeNode* C = (TreeNode*)malloc(sizeof(TreeNode));
	C->data = 'C';
	C->left = NULL;
	C->right = NULL;
	TreeNode* D = (TreeNode*)malloc(sizeof(TreeNode));
	D->data = 'D';
	D->left = NULL;
	D->right = NULL;
	TreeNode* E = (TreeNode*)malloc(sizeof(TreeNode));
	E->data = 'E';
	E->left = NULL;
	E->right = NULL;
	TreeNode* F = (TreeNode*)malloc(sizeof(TreeNode));
	F->data = 'F';
	F->left = NULL;
	F->right = NULL;
	A->left = B;
	A->right = C;
	B->left = D;
	B->right = F;
	PrevTreeNode(A);
	printf("\n÷––Ú\n");
	InTreeNode(A);
	printf("\n”“–Ú\n");
	PostTreeNode(A);

	int hight = TreeHight(&B);
	printf("%d\n", hight);
}