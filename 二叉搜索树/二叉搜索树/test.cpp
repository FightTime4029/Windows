#define _CRT_SECURE_NO_WARNINGS

#include "BSTreeKV.hpp"
#include <string>


int main()
{
	/*BSTree<std::string, std::string> b;
	b.insert("insert", "����");
	b.insert("earse", "ɾ��");
	b.insert("laowei", "��κɵ��");
	b.insert("priority_queue", "���ȼ�����");
	b.insert("contrl", "����");
	b.insert("child", "����");
	
	std::string str;
	while (std::cin>>str)
	{
		struct BTNode<std::string, std::string>* st = b.find(str);
		if (st == nullptr)
		{
			std::cout << "δ���ڸõ���!\n" << std::endl;
		}
		else
		{
			std::cout << st->_val << std::endl;

		}
	}*/


	//��ѯ�ж���ˮ��
	// �O��N��
	std::string str1[] = { "����","����", "����", "����", "����", "����", "����", "�㽶","����","����"\
		,"ƻ��","����","����","����","����","����", "�㽶" };

	BSTree<std::string, int> b;
	for (auto str : str1)
	{
		auto ret = b.find(str);
		if (ret == nullptr)
		{
			b.insert(str,1);
		}
		else
		{
			ret->_val++;
		}
	}
	b.InOrder();

	return 0;
}