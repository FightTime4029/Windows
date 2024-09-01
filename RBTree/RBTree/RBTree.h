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
		//�����ڵ���ɫ�����
		cur->_col = RED;
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//���1 ����ڵ�Ҳ�Ǻ�ɫ ��ô��parent��uncle�ڵ��ɺ�ɫ grandfather��ɺ�ɫ  
				//����grandfather �Ǹ��ڵ� ���������ĳɺ�ɫ
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				//���2 or ���3
				else
				{
					//���3 ��Ҫ˫��
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
			//parent��grandfather���ұ�
			else
			{
				Node* uncle = grandfather->_left;
				//���1 �����Ǻ�ɫ ���ڵ�Ҳ�Ǻ�ɫ ������͸��ڵ��ɺ�ɫ �游��ɺ�ɫ ���Ǹ��ڵ����Ǻ�ɫ
				if (uncle && (uncle->_col = RED))
				{
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				//���2 or ���3
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
		//parent->bf = subR->bf = 0;
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


