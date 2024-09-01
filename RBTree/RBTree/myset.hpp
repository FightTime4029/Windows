#pragma once
#include <iostream>
#include "RBTree.h"

namespace sxj
{
	template<class K>
	class set
	{
	public:
		struct SetOfK
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

		//typedef typename RBTree<K, K, SetOfK>::iterator iterator;
		/*iterator& begin()
		{
			return _t->begin();
		}

		iterator end()
		{
			return _t->end();
		}*/

		bool Insert(const K& k)
		{
			return _t->Insert(k);
		}
	private:
		RBTree<K, K,SetOfK>* _t;
	};
}

void testset()
{
	sxj::set<int> s;
	s.Insert(1);
	s.Insert(2);
	s.Insert(3);

}