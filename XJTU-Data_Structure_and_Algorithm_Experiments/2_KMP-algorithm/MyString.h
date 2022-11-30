// 用于实现string

#pragma once
#ifndef MYSTRING_
#define MYSTRING_

class MyString
{
private:
	char* ch;
	int length;

public:
	MyString(char* input);
	~MyString();
	char operator[](int pos);

public:
	int StrLength();
	int ClearString();
	int StrCompare(MyString s1, MyString s2);
};

#endif // !MYSTRING_
