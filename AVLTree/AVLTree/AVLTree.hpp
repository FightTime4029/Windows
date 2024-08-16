#pragma once

#include <iostream>
template<class K, class V>
struct AVTreeNode
{
	AVTreeNode<k, v> _left;
	AVTreeNode<k, v> _right;
	AVTreeNode<k, v> _parent;
	int bf; //avl树的平衡因子  在根节点的左边创建新节点 bf-- 反之 bf++
	std::pair<k, v> _kv;

	struct AVTreeNode(const std::pair<k, v> kv)
		:_kv(kv)
		, _left(nullptr)
		, right(nullptr)
		, _parent(nullptr)
		, bf(0);
};


template<class k, class v>
class AVLTree
{
	typedef AVTreeNode<k, v> Node;

	bool Insert(const std::pair<k, v> kv)
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
			}
		}

		return true;
	}


private:
	Node* _root = nullptr;
};