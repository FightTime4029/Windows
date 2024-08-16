#pragma once
#include <iostream>
#include <deque>

namespace sxj
{
	template<class T , class Container = deque<T>>
	class stack
	{
	public:
		void push(const T& x)
		{
			st.push_back(x);
		}

		void pop()
		{
			st.pop_back();
		}
		
		bool empty()
		{
			return st.empty();
		}

		int size()
		{
			return st.size();
		}

		T top()
		{
			return st.back();
		}

	private:
		Container st;
	};





}