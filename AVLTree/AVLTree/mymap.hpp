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

	bool Insert(const pair<K,V>& kv)
	{
		return _t->Insert(kv);
	}


private:
	RBTree<K, pair<K, V>, MapOfK>* _t;
};
}