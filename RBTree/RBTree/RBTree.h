#pragma once
#include <iostream>
using namespace std;

enum Color
{
	BLACK,
	RED
};

template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& data)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_data(data)
		,_col(RED)
	{}
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;

	T _data;

	Color _col;
};





template<class K,class V,class mapoft>
class RBTree
{
	typedef RBTreeNode<V> Node;

public:

	bool Insert(const V& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
		}
		Node* parent = nullptr;
		Node* cur = _root;

		mapoft moft;
		while (cur)
		{
			if (moft(cur->_data) < moft(kv))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (moft(cur->_data) > moft(kv))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		if (moft(parent->_data) < moft(kv))
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//新增节点颜色给红的
		cur->_col = RED;
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//情况1 叔叔节点也是红色 那么将parent和uncle节点变成黑色 grandfather变成红色  
				//若是grandfather 是根节点 放在最后将其改成黑色
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				//情况2 or 情况3
				else
				{
					//情况3 需要双旋
					if (parent->_right == cur) 
					{
						RotateL(parent);
						swap(parent, cur);
					}

					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
			//parent在grandfather的右边
			else
			{
				Node* uncle = grandfather->_left;
				//情况1 叔叔是红色 父节点也是红色 把叔叔和父节点变成黑色 祖父变成红色 若是根节点则还是黑色
				if (uncle && (uncle->_col = RED))
				{
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				//情况2 or 情况3
				else
				{
					if (cur = parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}

					RotateL(grandfather);
					grandfather->_col = BLACK;
					parent->_col = RED;
					break;
				}
			}
		}


		_root->_col = BLACK;
		return true;
	}


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
		//parent->bf = subR->bf = 0;
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
		//parent->bf = subL->bf = 0;
	}
	


	/*void _Inorder(Node* root)
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
	}*/


private:
	Node* _root = nullptr;
};


