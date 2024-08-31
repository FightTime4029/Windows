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

		bool Insert(const K& k)
		{
			return _t->Insert(k);
		}
	private:
		RBTree<K, K,SetOfK>* _t;
	};
}