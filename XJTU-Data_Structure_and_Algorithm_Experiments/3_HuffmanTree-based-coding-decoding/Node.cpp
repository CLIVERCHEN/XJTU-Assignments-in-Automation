#include "Node.h"

Node::Node(int Cinput) :data(Cinput) {};

Node::Node(int Cinput, char ch) :data(Cinput), Char(ch) {};

Node::~Node() {};

void Node::ModifyLeftChild(Node* n)
{
	Left_Child = n;
}

void Node::ModifyRightChild(Node* n)
{
	Right_Child = n;
}

void Node::ModifyParents(Node* n)
{
	Parents = n;
}

void Node::ModifyChar(char s)
{
	Char = s;
}