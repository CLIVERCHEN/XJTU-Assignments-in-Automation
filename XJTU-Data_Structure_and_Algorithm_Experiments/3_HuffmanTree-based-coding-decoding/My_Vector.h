#pragma once
#ifndef MY_VECTOR_
#define MY_VECRTOR_

#define MY_VECTOR_LENGTH 200
#define LENGTH_INCREASEMENT 20

// 实现动态数组

#include <iostream>
#include <assert.h>
using namespace std;

template<class T>
class My_Vector
{
private:
	T* start = NULL;
	T* finish = NULL;
	int size = MY_VECTOR_LENGTH;
	int length = 0;

public:
	My_Vector()
	{
		start = new T[MY_VECTOR_LENGTH];
		finish = start;
	}

	My_Vector(const My_Vector& t)
	{
		start = new T[t.Length()];
		finish = start;
		for (int i = 0; i < Length(); i++) *(finish + i) = *(t.start + i);
		size = t.size;
	}

	~My_Vector()
	{
		if (start)
		{
			delete[] start;
			start = NULL;
			finish = NULL;
		}
	}

	void Push(T input)
	{
		if (Length() + 1 > size)
		{
			ReInit(size + LENGTH_INCREASEMENT);
			*finish = input;
			finish++;
			length++;
		}
		else
		{
			*finish = input;
			finish++;
			length++;
		}
	}

	void Pop()
	{
		finish--;
		length--;
	}

	void ReInit(int L)
	{
		assert(L > Length());
		T* tmp_start = new T[L];
		memcpy(tmp_start, start, Length() * sizeof(T));
		start = tmp_start;

		finish = start + Length();
		size = L;
	}

	T& operator[](int pos)
	{
		if (pos > size)
		{
			ReInit(Length() + pos);
			finish = start + pos + 1;
			length = pos + 1;
			return *(start + pos);
		}
		else if (pos < Length())
		{
			return *(start + pos);
		}
		else
		{
			finish = start + pos + 1;
			length = pos + 1;
			return *(start + pos);
		}
	}

	int Length()
	{
		return length;
	}

	void Print_My_Vector()
	{
		for (int i = 0; i < Length(); i++)
			cout << *(start + i);
	}

	void Reverse()
	{
		for (int j = 0; j < Length() / 2; j++)
		{
			T tmp;
			tmp = *(start + j);
			*(start + j) = *(start + Length() - j - 1);
			*(start + Length() - j - 1) = tmp;
		}
	}
};

#endif // !MY_VECTOR_
