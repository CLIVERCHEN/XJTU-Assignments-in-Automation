// 实现栈及栈的操作

#pragma once
#ifndef MY_STACK_

#include <iostream>
using namespace std;

#define STACK_INIT_SIZE  200
#define STACK_INCREMENT  10

template <class TypeElem>
class my_stack
{
public:
	TypeElem* base;
	TypeElem* top;
	int StackSize;

public:
	my_stack()  // 用TypeElem确定内存分配大小
	{
		base = new TypeElem[STACK_INIT_SIZE];
		if (!base)
			exit(OVERFLOW);
		top = base;
		StackSize = STACK_INIT_SIZE;
	}

	~my_stack()
	{
		if (base)
			delete []base;
	}

	int Push(TypeElem input)
	{
		if (top - base >= StackSize)
		{
			TypeElem* tmp_base = new TypeElem[StackSize + STACK_INCREMENT];
			memcpy(tmp_base, base, StackSize * sizeof(TypeElem));
			base = tmp_base;
			if (!base)
				exit(OVERFLOW);
			top = base + StackSize;
			StackSize += STACK_INCREMENT;
		}
		*top = input;
		top++;
		return 0;
	}

	int Pop(TypeElem& out)
	{
		if (top == base)
		{
			cout << "ERROR_02";  // 操作数或操作符数归零，但还未停止操作，则报错ERROR_02
			exit(0);
		}
		top--;
		out = *top;
		return 0;
	}
};
#endif // !MY_STACK_
