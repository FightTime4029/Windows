#pragma once

#include <iostream>
template<class K, class V>
struct AVTreeNode
{
	AVTreeNode<K,V>* _left;
	AVTreeNode<K,V>* _right;
	AVTreeNode<K,V>* _parent;
	int bf = 0; //avl����ƽ������  �ڸ��ڵ����ߴ����½ڵ� bf-- ��֮ bf++
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
				if (parent->bf == 2)
				{
					if (cur->bf == 1)
					{
						//�������߶�+1 ���� 
						RotateL(parent);
						break;

					}
					else if (cur->bf == -1)
					{
						//�������߶�+1 
						RotateRL(parent);
						break;

					}
				}
				else if (parent->bf = -2)
				{
					if (cur->bf == -1)
					{
						//�������߶�+1 �ҵ���
						RotateR(parent);
						break;

					}
					else if (cur->bf == 1)
					{
						//�������߶�+1 
						RotateLR(parent);
						break;

					}
				}
			}
		}

		return true;
	}

	//��ת·����ֱ�߾��ǵ���
	//��ת·�������߾���˫��


	//����
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//���subR����߲�Ϊ�� ��subR��������ӵ�parent���ұ�		
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		//subR�����������parent
		subR->_left = parent;
		//�ҵ�parent��parent
		Node* ppNode = parent->_parent;
		//��parent�ĸ��ڵ���subR
		parent->_parent = subR;
		//���parent�Ǹ��ڵ� ���¸��ڵ� ����subR��parent�ڵ��ÿ�
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		//�����Ǹ��ڵ� �ж�parent��parent->_parent�����ӻ����Һ��� ���³�ΪsubR
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}
		//��ת֮�� ���ƽ�� ƽ���������ó�0
		parent->bf = subR->bf = 0;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//subL���ұ������Ϊ�� �������ӵ�parent����� ���޸�subL�Һ��ӵ�parent�ڵ�
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		//��parent���������subL���Һ���
		subL->_right = parent;
		//����parent��parent
		Node* ppNode = parent->_parent;
		//����parent��parent ��ΪsubL
		parent->_parent = subL;
		//���parent�Ǹ��ڵ� ���¸��ڵ� ����subL��parent�ÿ�
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		//���� �ҵ�parent��parent->_parent������ ���� �Һ��� ���ӵ���Ӧλ��
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;

			subL->_parent = ppNode;
		}
		//��ת��� ��ƽ�����ӹ���
		parent->bf = subL->bf = 0;
	}
	//����˫��
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		//���뵥�� ��ı�ƽ������ ������Ҫ��¼һ��
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