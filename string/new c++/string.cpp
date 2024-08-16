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
	//���  ��ͳд��
	//Str(const Str& s) :_str(new char[strlen(s._str)+1])
	//{
	//	strcpy(_str, s._str);
	//}

	//�ִ�д��
	Str(const Str& s) :_str(nullptr),_size(0),_capacity(0)
	{
		Str tmp(s._str);
		this->swap(tmp);
	}
	//�����ǿ������������һ���ֲ���������������Ҫ�����ݽ�����this���� 
	//���������ʱ�� �ֲ��������������������
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
		//����ط������size_t���޷��ţ���end���з��� 
		// ��end�Ǹ�����ʱ��ᷢ������ת������޷������� -1�ͻ��÷ǳ���
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