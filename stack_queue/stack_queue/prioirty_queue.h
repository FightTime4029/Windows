#pragma once

#include <iostream>
#include <vector>
namespace sxj
{
	template<class T>
	struct less
	{
	public:
		bool operator()(const T& x1, const T& x2)
		{
			return x1 < x2;
		}
	};

	template<class T>
	struct greater
	{
	public:
		bool operator()(const T& x1, const T& x2)
		{
			return x1 > x2;
		}
	};

	template<class T,class Contioner = std::vector<T>,class Compare = less<T>>
	class priority_queue
	{
	public:
		void AdJustUp(int child)
		{
			int parent = (child - 1) / 2;

			while (child > 0)
			{
				//if (pq[child] > pq[parent])
				Compare com;
				if (com(pq[parent],pq[child]))
				{
					::swap(pq[child], pq[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}

			}
		}

		void AdJustDown(int root)
		{
			int parent = root;
			int child = parent * 2 + 1;
			Compare com;
			while (child <  pq.size())
			{
				//if (child+1 < pq.size() && pq[child] < pq[child+1])
				if (child + 1 < pq.size() && com(pq[child],pq[child + 1]))
				{
					child += 1;
				}

				//if (pq[child] > pq[parent])
				if (com(pq[parent],pq[child]))
				{
					::swap(pq[child], pq[parent]);

					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}

		}

		void push(const T& x)
		{
			pq.push_back(x);

			AdJustUp(pq.size() - 1);
		}

		void pop()
		{
			::swap(pq[0], pq[pq.size() - 1]);

			pq.pop_back();

			AdJustDown(0);
		}

		size_t size()
		{
			return pq.size();
		}

		bool empty()
		{
			return pq.empty();
		}

		T& top()
		{
			return pq.front();
		}


	private:
		Contioner pq;

	};

}