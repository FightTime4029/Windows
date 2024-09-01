#pragma once
#include <iostream>
#include "RBTree.h"

namespace sxj
{
	template<class K, class V>
class map
{
public:
	struct MapOfK
	{
		const K& operator()(const std::pair<K, V>& kv)
		{
			return kv.first;
		}
	};
	//typedef typename RBTree<K, pair<K,V>, MapOfK>::iterator iterator;
	bool Insert(const pair<K,V>& kv)
	{
		return _t->Insert(kv);
	}

	/*iterator begin()
	{
		return _t->begin();
	}

	iterator end()
	{
		return _t->end();
	}*/

private:
	RBTree<K, pair<K, V>, MapOfK>* _t;
};

}


void testmap()
{
	sxj::map<int, int> m;
	m.Insert(make_pair(1, 1));
	m.Insert(make_pair(2, 2));
	m.Insert(make_pair(3, 3));


}