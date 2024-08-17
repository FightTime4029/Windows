#pragma once

#include <iostream>
template<class K, class V>
struct AVTreeNode
{
	AVTreeNode<K,V>* _left;
	AVTreeNode<K,V>* _right;
	AVTreeNode<K,V>* _parent;
	int bf = 0; //avl树的平衡因子  在根节点的左边创建新节点 bf-- 反之 bf++
	std::pair<K,V> _kv;

	struct AVTreeNode(const std::pair<K, V> kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};


template<class K, class V>
class AVLTree
{
	typedef AVTreeNode<K,V> Node;

public:
	bool Insert(const std::pair<K, V> kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false; //key值相同情况 直接返回
			}
		}
		//找到适合插入的地方了
		cur = new Node(kv);
		if (parent->_kv.first > kv.first)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		//更新平衡因子
		while (parent)
		{
			if (parent->_right == cur)
			{
				parent->bf++;
			}
			else
			{
				parent->bf--;
			}

			if (parent->bf == 0)
			{
				//说明子树高度不变 退出
				break;
			}
			else if (parent->bf == 1 || parent->bf == -1)
			{
				//创建了一个子节点 导致不平衡  需要向上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->bf == 2 || parent->bf == -2)
			{
				//左右树不平衡了 需要进行旋转
				if (parent->bf == 2)
				{
					if (cur->bf == 1)
					{
						//右子树高度+1 左单旋 
						RotateL(parent);
						break;

					}
					else if (cur->bf == -1)
					{
						//左子树高度+1 
						RotateRL(parent);
						break;

					}
				}
				else if (parent->bf = -2)
				{
					if (cur->bf == -1)
					{
						//左子树高度+1 右单旋
						RotateR(parent);
						break;

					}
					else if (cur->bf == 1)
					{
						//右子树高度+1 
						RotateLR(parent);
						break;

					}
				}
			}
		}

		return true;
	}

	//旋转路径是直线就是单旋
	//旋转路径是折线就是双旋


	//左单旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//如果subR的左边不为空 把subR的左边链接到parent的右边		
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		//subR的左边连接上parent
		subR->_left = parent;
		//找到parent的parent
		Node* ppNode = parent->_parent;
		//将parent的父节点变成subR
		parent->_parent = subR;
		//如果parent是根节点 更新根节点 并将subR的parent节点置空
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		//否则不是根节点 判断parent是parent->_parent的左孩子还是右孩子 更新成为subR
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}
		//旋转之后 变得平衡 平衡因子设置成0
		parent->bf = subR->bf = 0;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//subL的右边如果不为空 则将其连接到parent的左边 并修改subL右孩子的parent节点
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		//将parent拉下来变成subL的右孩子
		subL->_right = parent;
		//保存parent的parent
		Node* ppNode = parent->_parent;
		//更新parent的parent 成为subL
		parent->_parent = subL;
		//如果parent是根节点 更新根节点 并将subL的parent置空
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		//否则 找到parent是parent->_parent的左孩子 还是 右孩子 连接到相应位置
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;

			subL->_parent = ppNode;
		}
		//旋转完毕 将平衡因子归零
		parent->bf = subL->bf = 0;
	}
	//右左双旋
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		//进入单旋 会改变平衡因子 所以需要记录一下
		int bf1 = subRL->bf;

		RotateR(subR);
		RotateL(parent);

		if (bf1 == 1)
		{
			subRL->bf = subR->bf = 0;
			parent->bf = -1;
		}
		else if (bf1 == -1)
		{
			parent->bf = subRL->bf = 0;
			subR->bf = 1;
		}
		else if (bf1 == 0)
		{
			parent->bf = subR->bf = subRL->bf = 0;
		}
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf1 = subLR->bf;

		RotateL(subL);
		RotateR(parent);

		if (bf1 == 1)
		{
			subL->bf = -1;
			parent->bf = subLR->bf = 0;
		}
		else if (bf1 == -1)
		{
			parent->bf = 1;
			subL->bf = subLR->bf = 0;
		}
		else if (bf1 == 0)
		{
			parent->bf = subL->bf = subLR->bf = 0;
		}

	}

	int Hight(Node* root)
	{
		if (root)
			return 0;
		int leftheight = Hight(root->_left);
		int rightheight = Hight(root->_right);

		return leftheight > rightheight ? leftheight + 1 : rightheight + 1;
	}

	bool _IsBalance(Node* root)
	{
		if (root)
			return true;

		int leftheight = Hight(root->_left);
		int rightheight = Hight(root->_right);
		
		return abs(leftheight - rightheight) < 2 && _IsBalance(root->_left) && _IsBalance(root->_right);
	}

	bool IsBalance()
	{
		 return _IsBalance(_root);
	}


	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->_left);
		std::cout << root->_kv.first << " : " << root->_kv.second << std::endl;
		_Inorder(root->_right);
	}

	void Inorder()
	{
		_Inorder(_root);
	}

private:
	Node* _root = nullptr;
};