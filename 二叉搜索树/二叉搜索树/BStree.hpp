#pragma once
#include <iostream>
#include <cassert>
template<class k>
struct BTNode // 树节点结构体
{

	BTNode(const k& key)
		:left(nullptr),right(nullptr),_key(key)
	{}

	BTNode<k>* left;
	BTNode<k>* right;
	k _key;
	
};



template<class k>
class BSTree //binary serch tree 二叉搜索树
{
	typedef BTNode<k> Node;
public:
	BSTree()
		:_root(nullptr)
	{}

	bool insert(const k& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);

			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			parent = cur;
			if (cur->_key < key)
				cur = cur->right;
			else if (cur->_key > key)
				cur = cur->left;
			else
				return false;
		}

		cur = new Node(key);
		if (parent->_key < key)
		{
			parent->right = cur;
		}
		else
		{
			parent->left = cur;
		}

	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->left);
		std::cout << root->_key << " ";
		_InOrder(root->right);
	}
	void InOrder()
	{
		_InOrder(_root);
		std::cout << std::endl;
	}


	bool find(const k& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->right;
			}
			else if (cur->_key > key)
			{
				cur = cur->left;
			}
			else
			{
				return true;
			}
		}

		return false;
	}


	bool earse(const k& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->left;
			}
			else
			{
				//左边为空让父节点指向右边
				if (cur->left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->right;
					}
					else
					{
						if (parent->left == cur)
						{
							parent->left = cur->right;
						}
						else
						{
							parent->right = cur->right;
						}
					}
					delete cur;
				}
				//右边为空让父节点指向左边
				else if (cur->right == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->left;
					}
					else
					{
						if (parent->left == cur)
						{
							parent->left = cur->left;
						}
						else
						{
							parent->right = cur->left;
						}
					}
					delete cur;

				}
				else
				{
					//如果左右子树都不为空
					//找左子树的最大值
					//Node* leftMaxParent = cur;
					//Node* leftMax = cur->left;
					//while (leftMax->right)
					//{
					//	leftMaxParent = leftMax;
					//	leftMax = leftMax->right;
					//}

					//cur->_key = leftMax->_key;

					//if (leftMax == leftMaxParent->left)
					//{
					//	leftMaxParent->left = leftMax->left;
					//}
					//else
					//{
					//	leftMaxParent->right = leftMax->left;
					//}

					//delete leftMax;


					//找右子树的最小值
					Node* rightMinParent = cur;
					Node* rightMin = cur->right;

					while (rightMin->left)
					{
						rightMinParent = rightMin;
						rightMin = rightMin->left;
					}

					cur->_key = rightMin->_key;

					if (rightMin == rightMinParent->left)
					{
						rightMinParent->left = rightMin->right;
					}
					else
					{
						rightMinParent->right = rightMin->right;
					}

					delete rightMin;
				}
				return true;
			}
		}
		return false;
	}

private:
	Node* _root;
};