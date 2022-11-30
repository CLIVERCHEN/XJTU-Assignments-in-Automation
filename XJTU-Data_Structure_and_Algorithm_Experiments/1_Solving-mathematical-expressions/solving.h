// 实现数学表达式的求解

#pragma once
#ifndef SOLVING

#include "My_Stack.h"
#include <iostream>
using namespace std;

class solving
{
public:
	int pri(char c1, char c2);
	double calculate(char c, double a, double b);
	double solving_m_exp(char* input);
};

#endif // !SOLVING
