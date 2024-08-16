#define _CRT_SECURE_NO_WARNINGS

#include "stack.h"
#include "queue.h"
#include <deque>
#include <vector>
#include "prioirty_queue.h"
using namespace std;

void test_queue()
{
	sxj::queue<int, deque<int>> q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	q.push(6);

	while (!q.empty())
	{
		cout << q.top()<< ' ';
		q.pop();
	}
	cout << endl;
}

void test_stack()
{
	sxj::stack<int, std::vector<int>> st;

	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	st.push(6);

	while (!st.empty())
	{
		std::cout << st.top() << ' ';
		st.pop();
	}
	cout << endl;
}


void test_priority_queue()
{
	//sxj::priority_queue<int> pq;
	sxj::priority_queue<int,vector<int>,greater<int>> pq;

	pq.push(1);
	pq.push(2);
	pq.push(3);
	pq.push(4);

	while (!pq.empty())
	{
		cout << pq.top() << ' ';
		pq.pop();
	}

	cout << endl;
}

int main()
{
	test_priority_queue();



	
	return 0;
}