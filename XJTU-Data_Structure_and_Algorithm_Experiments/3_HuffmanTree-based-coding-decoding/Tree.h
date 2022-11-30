#pragma once
#ifndef TREE_
#define TREE_

#include "Node.h"
#include "My_Vector.h"
#include <string>
using namespace std;

class Tree
{
private:
	Node* Head;
	My_Vector<char> Ans_Code;  // 存放编码的结果
	My_Vector<char> Ans_Decode;  // 存放解码的结果

public:
	Tree() {};
	~Tree();

public:
	My_Vector<Node*> ChCoding;  // 存放每个字母的结点地址

public:
	Node* Creat_New_Node(int input);
	Node* Creat_New_Node(int input, char ch);
	void Connect_Node(Node& n1, Node& n2, string pos);
	void PreOrder();
	void Create_Tree(char* S);
	void Coding(char* S);
	void Decoding(char* S);

public:
	void Print_Code();
	void Print_Decode();
};

#endif // !TREE_

