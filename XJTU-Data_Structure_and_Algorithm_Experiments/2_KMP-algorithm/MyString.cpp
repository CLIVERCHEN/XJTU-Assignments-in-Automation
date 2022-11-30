#include "MyString.h"
#include <iostream>
using namespace std;

MyString::MyString(char* input)
{
	int Length = 0;
	while (*(input + Length) != '\0') Length++;
	length = Length;

	ch = new char[length];
	for (int i = 0; i < length; i++) *(ch + i) = *(input + i);
}

MyString::~MyString()
{
	ClearString();
}
	
int MyString::StrLength()
{
	return length;
}

char MyString::operator[](int pos)
{
	return *(ch + pos);
}

int MyString::ClearString()
{
	if (ch)
	{
		delete[]ch;
		ch = NULL;
		length = 0;
		return 1;
	}
	else return 0;
}
	
int MyString::StrCompare(MyString s1, MyString s2)
{
	for (int i = 0; i < s1.StrLength() && i < s2.StrLength(); i++)
	{
		if (s1.ch[i] != s2.ch[i]) return ((s1.ch[i] < s2.ch[i]) ? -1 : 1);
	}

	if (s1.StrLength() == s2.StrLength()) return 0;
	else return ((s1.StrLength() < s2.StrLength()) ? -1 : 1);
}