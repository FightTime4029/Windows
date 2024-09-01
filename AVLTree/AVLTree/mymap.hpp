#pragma once

#include "RBTree.hpp"

using namespace std;
namespace sxj
{
	template<class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<const K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<K, std::pair<const K, V>, MapKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		bool insert(const std::pair<const K, V>& kv)
		{
			return _t.Insert(kv);
		}
	private:
		RBTree<K, std::pair<const K, V>, MapKeyOfT> _t;
	};
	void test_map()
	{
		int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		map<int, int> m;
		for (auto e : a)
		{
			m.insert(make_pair(e, e));
		}


	}
}

