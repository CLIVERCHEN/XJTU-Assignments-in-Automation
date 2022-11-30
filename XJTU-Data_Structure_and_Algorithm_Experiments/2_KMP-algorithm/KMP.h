// 用于实现KMP算法

#pragma once
#include "MyString.h"
#include <iostream>
using namespace std;

#ifndef KMP_
#define KMP_

#define MAX_PATTERN_LENGTH 100

class KMP
{
private:
	MyString Text;
	MyString Pattern;

	int Next[MAX_PATTERN_LENGTH];

private:
	void Generate_Next();

public:
	KMP(char* t, char* p);
	~KMP();

	int KMP_Matching();
};

#endif // !KMP_
