#pragma once
#ifndef NODE_
#define NODE_

class Node
{
private:
	Node* Left_Child;
	Node* Right_Child;
	Node* Parents;

public:
	int data;
	char Char;

public:
	bool If_Output = false;  // 输出时判断是否已经输出

public:
	Node(int Cinput);
	Node(int Cinput, char ch);
	Node() {};
	~Node();

public:
	void ModifyLeftChild(Node* n);
	void ModifyRightChild(Node* n);
	void ModifyParents(Node* n);
	void ModifyChar(char s);
	Node* GetLeft() { return Left_Child; }
	Node* GetRight() { return Right_Child; }
	Node* GetParents() { return Parents; }
};

#endif // !NODE_
