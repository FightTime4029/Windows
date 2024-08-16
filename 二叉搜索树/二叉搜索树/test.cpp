#define _CRT_SECURE_NO_WARNINGS

#include "BSTreeKV.hpp"
#include <string>


int main()
{
	/*BSTree<std::string, std::string> b;
	b.insert("insert", "插入");
	b.insert("earse", "删除");
	b.insert("laowei", "老魏傻逼");
	b.insert("priority_queue", "优先级队列");
	b.insert("contrl", "控制");
	b.insert("child", "孩子");
	
	std::string str;
	while (std::cin>>str)
	{
		struct BTNode<std::string, std::string>* st = b.find(str);
		if (st == nullptr)
		{
			std::cout << "未存在该单词!\n" << std::endl;
		}
		else
		{
			std::cout << st->_val << std::endl;

		}
	}*/


	//查询有多少水果
	// 最坏O（N）
	std::string str1[] = { "西瓜","西瓜", "西瓜", "西瓜", "西瓜", "西瓜", "西瓜", "香蕉","西瓜","西瓜"\
		,"苹果","西瓜","西瓜","西瓜","西瓜","西瓜", "香蕉" };

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