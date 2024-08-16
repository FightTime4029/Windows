#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include  <assert.h>
using namespace std;

class Str
{
	friend ostream& operator<<(ostream& cout, const Str& str);
public:
	typedef char* iterator;
		iterator begin()
	{
		return _str;
	}
		iterator end()
		{
			return _str + _size;
		}

		void swap(Str& s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
	Str(const char* str = "") 
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
		_size = strlen(str);

		_capacity = _size;
	}
	//深拷贝  传统写法
	//Str(const Str& s) :_str(new char[strlen(s._str)+1])
	//{
	//	strcpy(_str, s._str);
	//}

	//现代写法
	Str(const Str& s) :_str(nullptr),_size(0),_capacity(0)
	{
		Str tmp(s._str);
		this->swap(tmp);
	}
	//这里是拷贝构造进来的一个局部变量，将我们想要的数据交换给this对象 
	//出作用域的时候 局部变量将会调用析构函数
	Str& operator=(Str str)
	{
		/*	if (this != &str)
			{
				Str s(str);
				char* p = str._str;
				s._str = this->_str;
				_str = p;
				_size = s._size;
				_capacity = s._capacity;
			}
			return *this; */
		this->swap(str);
		return *this;
	}

	~Str()
	{
		delete[] _str;
		_str = nullptr;
	}
	void reverse(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp,_str);
			delete[] _str;
			_str = tmp;
			_capacity = n;
		}
	}
	char& operator[](int i)
	{
		return _str[i];
	}
	Str& insert(size_t pos, char ch)
	{
		assert(pos <= _size);
		if (_size == _capacity)
		{
			size_t newcapacity=_capacity == 0 ? 2 : _capacity * 2;
			reverse(newcapacity);
		}

		int end=_size;
		while (end >= (int)pos)
		{
			_str[end + 1] = _str[end];
			end--;
		}
		_str[pos] = ch;
		_size++;
		_str[_size] = '\0';
		return *this;
	}
	Str& insert(size_t pos, const char* str)
	{
		int szstr = strlen(str);
		if (_size + szstr > _capacity)
		{
			reverse(_size + szstr);
		}
		int end = _size;
		//这个地方如果是size_t是无符号，而end是有符号 
		// 当end是负数的时候会发生类型转换变成无符号类型 -1就会变得非常大
			while (end >= (int)pos)
			{
				_str[end+szstr] = _str[end];
				--end;
			}
		strncpy(_str + pos, str, szstr);
		_size += szstr;
		return *this;

	}

	void resize(size_t n,char ch='\0')
	{
		if (n > _capacity)
		{
			reverse(n);
		for (int i = _size; i < n; i++)
		{
			_str[i] = ch;
		}
		_size = n;
		_str[_size] = '\0';
		}
		else
		{
			_size = n;
			_str[_size] = '\0';
		}

	}
	Str& erase(size_t pos,size_t len=npos)
	{
		assert(pos < _size);
		if (len > _size - pos)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			size_t i= pos + len;
			while (i <= _size)
			{
				_str[i - len] = _str[i];
				++i;
			}
			_size -= len;
		}
		return *this;
	}

	size_t find(char ch,size_t pos=0) const
	{
		for (size_t i = pos;i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return npos;
	}
	size_t size()const
	{
		return _size;
	}
	size_t capacity()const
	{
		return _capacity;
	}


private:
	char* _str;
	size_t _size;
	size_t _capacity;

	static unsigned int npos;
};
unsigned int Str::npos = -1;
	
	ostream& operator<<(ostream& cout, const Str& str)
	{
		cout << str._str << ' ';
		return cout;
	}

	int main()
	{
		Str s1("Hello World");
		Str s2(s1);
		Str s3 = s1;
		Str::iterator it = s1.begin();
		while (it != s1.end())
		{
			cout << *it << ' ';
			it++;
		}
		cout << endl;
		return 0;
	}