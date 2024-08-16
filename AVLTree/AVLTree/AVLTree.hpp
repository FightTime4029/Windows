#pragma once

#include <iostream>
template<class K, class V>
struct AVTreeNode
{
	AVTreeNode<k, v> _left;
	AVTreeNode<k, v> _right;
	AVTreeNode<k, v> _parent;
	int bf; //avl����ƽ������  �ڸ��ڵ����ߴ����½ڵ� bf-- ��֮ bf++
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
				return false; //keyֵ��ͬ��� ֱ�ӷ���
			}
		}
		//�ҵ��ʺϲ���ĵط���
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

		//����ƽ������
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
				//˵�������߶Ȳ��� �˳�
				break;
			}
			else if (parent->bf == 1 || parent->bf == -1)
			{
				//������һ���ӽڵ� ���²�ƽ��  ��Ҫ���ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->bf == 2 || parent->bf == -2)
			{
				//��������ƽ���� ��Ҫ������ת
			}
		}

		return true;
	}


private:
	Node* _root = nullptr;
};