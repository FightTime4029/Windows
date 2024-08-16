#pragma once


namespace sxj
{
	template<class T, class Contioner = deque<T>>
	class queue
	{
	public:
		void push(const T& x)
		{
			q.push_back(x);
		}

		void pop()
		{
			q.pop_front();
		}

		bool empty()
		{
			return q.empty();
		}

		int size()
		{
			return q.size();
		}

		T top()
		{
			return q.front();
		}
	private:
		Contioner q;

	};



}