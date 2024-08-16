#pragma once
#include <iostream>
#include <assert.h>
namespace sxj 
{

	template<class T>
	struct __list_node
	{
	public:
		__list_node(const T&x=T()):prev(nullptr),next(nullptr),data(x)
		{}

	

		__list_node<T>* prev;
		__list_node<T>* next;
		T data;

	};
	template<class T,class Ref,class Ptr>
	 struct __list_iterator
	{
		typedef __list_node<T> Node;
		typedef __list_iterator<T,Ref,Ptr> Self;

		Node* _node;

		__list_iterator(Node* node):_node(node)
		{ }

		Ref operator*()
		{
			return _node->data;
		}

		
		Ptr operator->()
		{
			return &_node->data;
		}

		Ref operator*() const
		{
			return _node->data;
		}


		Ptr operator->() const
		{
			return &_node->data;
		}


		Self& operator++()
		{
			_node = _node->next;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp = (*this);
			//_node = _node->next;
			++(*this);
			return tmp;
		}

		Self& operator--()
		{
			_node = _node->prev;
			return *this;
		}
		Self operator--(int)
		{
			__list_iterator<T> tmp = (*this);
			//_node = _node->prev;
			--(*this);
			return tmp;
		}

		bool operator!=(const Self& x)
		{
			return _node != x._node;
		}

		bool operator==(const Self& x)
		{
			return _node == x._node;
		}
	};



	template<class T>
	class list
	{
		typedef __list_node<T> Node;
	public:
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T,const T&,const T*> const_iterator;

		list()
		{
			_head = new Node;
			_head->prev = _head;
			_head->next = _head;
		}

		~list()
		{
			clear();

			delete _head;
			_head = nullptr;
		}

		list(const list<T>& lt)
		{
			_head = new Node;
			_head->next = nullptr;
			_head->prev = nullptr;

			//list<T>::const_iterator it = lt.begin();
			//while (it != lt.end())
			//{
			//	push_back(*it);
			//	++it;
			//}
			for (auto e : lt)
			{
				push_back(e);
			}
		}

		//list<T>& operator=(const list<int>& lt)
		//{
		//	if (this != &lt)
		//	{
		//		clear();
		//		for (auto e : lt)
		//			push_back(e);
		//	}
		//	return *this;
		//}

		list<T>& operator=(list<int> lt)
		{
			::swap(_head, lt._head);
			return *this;
		}


		void clear()
		{
			list<T>::iterator it = begin();

			while (it != end())
			{
				earse(it++);
			}
		}
		iterator begin() const
		{
			return iterator(_head->next);
		}
		iterator end() const
		{
			return iterator(_head);
		}


		void push_back(const T& x)
		{
			//Node* tail = _head->prev;
			//Node* newnode = new Node(x);

			//tail->next = newnode;
			//newnode->prev = tail;
			//_head->prev = newnode;
			//newnode->next = _head;
			insert(end(), x);

		}
		void pop_back()
		{
		/*	Node* tail = _head->prev;
			assert(tail != _head);
			Node* prev = tail->prev;
			prev->next = _head;
			_head->prev = prev;
			delete tail;
			tail = nullptr;*/

			earse(--end());
		}
		void push_front(const T& x)
		{
			/*Node* newnode = new Node(x);
			Node* next = _head->next;

			_head->next = newnode;
			newnode->prev = _head;
			newnode->next = next;
			next->prev = newnode;*/

			insert(begin(), x);
		}
		void pop_front()
		{
		/*	Node* del = _head->next;
			assert(del != _head);
			Node* next = del->next;
			_head->next = next;
			next->prev = _head;*/
	/*		delete del;
			del = nullptr;*/

			earse(begin());
		}

		void earse(iterator pos)
		{
			//assert(_head = _head->next);
			assert(pos != end());
			Node* del = pos._node;

			Node* prev = del->prev;
			Node* next = del->next;

			prev->next = next;
			next->prev = prev;

			delete del;
			del = nullptr;
		}
		void insert(iterator pos, const T& x)
		{
			Node* Pos = pos._node;

			Node* prev = Pos->prev;

			Node* newnode = new Node(x);
				
			newnode->prev = prev;
			prev->next = newnode;
			newnode->next = Pos;
			Pos->prev = newnode;

		}
	private:
		Node* _head;
	};



}