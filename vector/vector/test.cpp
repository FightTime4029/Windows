#define _CRT_SECURE_NO_WARNINGS
#include "vector.h"
using namespace sxj;
int main()
{
	sxj::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);

	for (auto e : v)
	{
		std::cout << e << ' ';
	}
	std::cout << std::endl;


	vector<int>::iterator it = v.begin();
	v.earse(it + 6);
	it = v.begin();

	while (it != v.end())
	{
		std::cout << *it << ' ';
		it++;
	}
	std::cout << std::endl;
	//������ʧЧ����
	//it = v.begin();
	//while (it != v.end())
	//{
	//	if (*it % 2 == 0)
	//	{
	//		//������ﲻ�������� �п��ܻ�©ɾԪ��
	//		//ɾ����ǰԪ�ص�ʱ�� ��һ��Ԫ�ز�������©���ֱ�ӵ���һ��Ԫ��
	//		//v.earse(it);
	//		it = v.earse(it);
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}

	for (int i = .0; i < v.size(); ++i)
	{
		std::cout << v[i] << ' ';
	}
	std::cout << std::endl;

	//v.resize(20);

	sxj::vector<int> v1(v);
	for (auto e : v1)
	{
		std::cout << e << ' ';
	}
	std::cout << std::endl;
	sxj::vector<int> v3;
	v3 = v1;
	std::cout << "V3" << std::endl;

	for (auto& e : v3)
	{
		std::cout << e << ' ';
	}
	std::cout << std::endl;

	return 0;
}