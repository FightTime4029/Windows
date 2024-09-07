#pragma once
#include <vector>
#include <queue>
typedef unsigned char uch;

using std::vector;
template<class W>
struct HuffmanTreeNode
{
	HuffmanTreeNode<W>* _left;
	HuffmanTreeNode<W>* _right;
	HuffmanTreeNode<W>* _parent;

	W _weight;

	HuffmanTreeNode(const W& weight)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_weight(weight)
	{}
};

template<class W>
class HuffmanTree
{
	typedef HuffmanTreeNode<W> Node;
private:
	struct Compare
	{
		bool operator()(const Node* x,const Node* y)
		{
			return x->_weight > y->_weight;
		}
	};
public:
	HuffmanTree() :_root(nullptr)
	{}

	HuffmanTree(const vector<W>& vw, const W& valid)
	{
		std::priority_queue<Node*,vector<Node*>,Compare> pq;
		for (const auto& e : vw)
		{
			if(e != valid)
			pq.push(new Node(e));
		}

		while (pq.size() > 1)
		{
			Node* left = pq.top();
			pq.pop();
			Node* right = pq.top();
			pq.pop();

			Node* parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			left->_parent = parent;
			parent->_right = right;
			right->_parent = parent;

			pq.push(parent);
		}

		_root = pq.top();
		pq.pop();
	}

	Node* GetRoot()
	{
		return _root;
	}

	~HuffmanTree()
	{
		Destroy(_root);
	}
private:
	void  Destroy(Node* root)
	{
		if (!root)
			return;

		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
		root = nullptr;
	}
private:
	Node* _root;
};

