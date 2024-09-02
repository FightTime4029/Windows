#pragma once
#include <vector>

template<class K>
struct SetOfKey
{
	const K& operator()(const K& key)
	{
		return key;
	}
};

namespace CLOSE_HASH
{
enum state
{
	EMPTY,
	EXITS,
	DELETE,
};

template<class T>
struct HashData
{
	T _data;
	state _state;
};

template<class K,class V,class KeyofK>
class HashTable
{
	typedef HashData<V> HashData;
public:

	bool Insert(const V& d)
	{
		//负载因子 = 表中数据/表中大小
		//越接近满，冲突越多，冲突越多，效率越低
		//所以哈希表不是满了才增容而是接近满  或者 在0.7左右增容
		if (_tables.size() == 0 || _num * 10 / _tables.size() >= 7)		//两个整数相除 无法得到小数 所以方程式两边都乘10
		{
			//增容
			HashTable<K,V,KeyofK> newht;
			size_t newsize = (_tables.size() == 0 ? 10 : _tables.size() * 2);
			newht._tables.resize(newsize);

			for (int i = 0; i < _tables.size(); i++)
			{
				if (_tables[i]._state == EXITS)
				{
					newht.Insert(_tables[i]._data);
				}
			}
			_tables.swap(newht._tables);
		}

		KeyofK keyofk;
		//计算d在表中的映射位置
		size_t index = keyofk(d) % _tables.size();
		while (_tables[index]._state == EXITS)
		{
			if (keyofk(_tables[index]._data) == keyofk(d))
			{
				return false;
			}

			++index;
			if (index == _tables.size())
			{
				index = 0;
			}
		}

		_tables[index]._data = d;
		_tables[index]._state = EXITS;
		_num++;
		return true;
	}

	 HashData* Find(const K& key)
	{
		KeyofK keyofk;
		size_t index =key % _tables.size();
		while (_tables[index].state != EMPTY)
		{
			if (keyofk(_tables[index]._data) == key)
			{
				if (_tables[index].state == DELETE)
				{
					return nullptr;
				}
				else if(_tables[index].state == EXITS)
				{
					return &_tables[index];
				}
			}
			++index;
			if (index == _tables.size())
			{
				index = 0;
			}

		}
		return nullptr;
	}

	bool Erase(const K& key)
	{
		HashData* hd = Find(key);
		if (HashData)
		{
			hd->_state = DELETE;
			--_num;
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	std::vector<HashData> _tables;
	size_t _num = 0; //存了几个有效数据
};



void test_hash()
{
	HashTable<int, int, SetOfKey<int>> ht;
	ht.Insert(4);
	ht.Insert(14);
	ht.Insert(24);
	ht.Insert(33);
	ht.Insert(1);

}

}


namespace OPEN_HASH
{

	template<class V>
	struct HashNode
	{
		V _data;
		HashNode* next; 
		
		HashNode(const V& data):_data(data)
		{}
	};

	template<class K,class V,class KeyOfV>
	class HashTable
	{
		typedef HashNode<V> Node;
	public:
		bool insert(const V& key)
		{
			KeyOfV keyofv;
			if (_tables.size() == _num)
			{
				std::vector<Node*> newtables;
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				newtables.resize(newsize);
				for (int i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->next;
						size_t index = keyofv(cur->_data) % newtables.size();
						cur->next = newtables[index];
						newtables[index] = cur;
						cur = next;
					}
				}
				_tables.swap(newtables);
			}

			size_t index = keyofv(key) % _tables.size();
			Node* cur = _tables[index];
			//先找是否存在
			while (cur)
			{
				if (keyofv(cur->_data) == keyofv(key))
				{
					return false;
				}
				else
				{
					cur = cur->next;
				}
			}

			//不存在
			Node* newnode = new Node(key);
			newnode->next = _tables[index];
			_tables[index] = newnode;
			++_num;
			return true;
		}
		Node* find(const K& key)
		{
			KeyOfV keyofv;
			size_t index = key % _tables.size();
			Node* cur = _tables[index];
			while (cur)
			{
				if (keyofv(cur->_data) == key)
				{
					return cur;
				}
				else
				{
					cur = cur->next;
				}
			}
			return nullptr;
		}

		bool erase(const K& key)
		{
			KeyOfV keyofv;
			size_t index = key % _tables.size();
			Node* cur = _tables[index];
			Node* prev = nullptr;
			while (cur)
			{
				if(keyofv(cur->_data) == key)
				{
					if (prev == nullptr)
					{
						_tables[index] = cur->next;
						delete cur;
						return true;
					}
					else
					{
						prev->next = cur->next;
						delete cur;
						return true;
					}
				}
				else
				{
					prev = cur;
					cur = cur->next;
				}
			}
			return false;
		}

	private:
		std::vector<Node*> _tables;
		size_t _num = 0; //有效数据
	};

	void test_hash()
	{
		HashTable<int, int, SetOfKey<int>> ht;
		ht.insert(4);
		ht.insert(14);
		ht.insert(34);
		ht.insert(44);
		ht.insert(54);
		ht.insert(64);
		ht.insert(74);
		ht.insert(84);
		ht.insert(24);
		ht.insert(33);
		ht.insert(1);
		ht.erase(4);
		ht.erase(44);
	}



}