#pragma once
#include <iostream>
#include <assert.h>
namespace sxj
{
	template <class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}
		//vector(const vector<int>& v)
		//	:_start(nullptr)
		//	, _finish(nullptr)
		//	, _endofstorage(nullptr)
		//{
		//	_start = new T[v.capacity()];
		//	_finish = _start;
		//	_endofstorage = _start + v.capacity();

		//	for (int i = 0; i < v.size(); i++)
		//	{
		//		_finish = v[i];
		//		++_finish;
		//	}
		//}
		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(v.capacity());
			for (const auto& e : v)	
			{
				push_back(e);
			}
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}
	

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}
		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}
		T& operator[](size_t i) const
		{
			assert(i < size());
			return _start[i];
		}

		void Swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}

		vector<T>& operator=(vector<T> v)
		{
			Swap(v);
			return *this;
		}

		void reserve(const size_t& n)
		{
				if (n > capacity())
				{
					size_t sz = size();
					T* tmp = new T[n];
					if (_start)
					{
						//如果T是string类型 重新开空间 两个数组会指向同一个地方 之后释放就找不到了 //按字节拷贝 浅拷贝
						//memcpy(tmp,_start,sizeof(T)*size());
						for (int i = 0; i < sz; i++)
						{
							tmp[i] = _start[i]; //深拷贝  相当于 string = string 调用的是string的operator=
						}
						delete[] _start;
					}
					_start = tmp;
					_finish = tmp + sz;
					_endofstorage = tmp + n;
				}
		}

		void push_back(const T& x)
		{
			/*if (_finish == _endofstorage)
			{
				size_t n = capacity() == 0 ? 2 : capacity() * 2;
				reserve(n);
			}
			*_finish = x;
			++_finish;*/

			insert(_finish,x);
		}

		void pop_back()
		{
			/*assert(_finish >= _start);
			_finish--;*/
			earse(_finish - 1);
		}

		void insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);

			if (_finish == _endofstorage)
			{
				size_t sz = pos - _start;
				size_t n = capacity() == 0 ? 2 : capacity() * 2;
				reserve(n);
				//如果增容成功，就会导致迭代器失效 指向原本的地址，需要修正 指向新的地址
				pos = _start + sz;
			}

			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				end--;
			}
			*pos = x;
			_finish++;
		}

		void resize(size_t n, const T& val= T())
		{
			assert(n >= 0);
			iterator newsize = _start + n;
			if (newsize < _finish)
			{
				_finish = newsize;
			}
			else 
			{
				if (newsize > _endofstorage)
				{
					reserve(n);
				}
					while (_finish < _endofstorage)
					{
						*_finish = val;
						_finish++;
					}
			}
		}

		iterator earse(iterator pos)
		{
			assert(pos < _finish);
			iterator it = pos + 1;
			while (it < _finish)
			{
				*(it - 1) = *it;
				it++;
			}
			_finish--;
			return pos;
		}

		size_t size()
		{
			return _finish - _start;
		}

		size_t capacity()
		{
			return _endofstorage - _start;
		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endofstorage - _start;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};



}