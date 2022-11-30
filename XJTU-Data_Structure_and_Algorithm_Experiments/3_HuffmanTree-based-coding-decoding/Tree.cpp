#include "Tree.h"
#include "Node.h"
#include "My_Vector.h"
#include <string>
#include <iostream>
using namespace std;

Tree::~Tree()
{
	if (Head)
		delete[] Head;
}

Node* Tree::Creat_New_Node(int input)
{
	Node* n = new Node(input);
	return n;
}

Node* Tree::Creat_New_Node(int input, char ch)
{
	Node* n = new Node(input, ch);
	return n;
}

void Tree::Connect_Node(Node& n1, Node& n2, string pos)
{
	if (pos == "left")
	{
		n1.ModifyLeftChild(&n2);
		n2.ModifyParents(&n1);
	}
	else if (pos == "right")
	{
		n1.ModifyRightChild(&n2);
		n2.ModifyParents(&n1);
	}
	else
		cout << "Wrong Pos" << endl;
}

void Tree::PreOrder()
{
	Node* tmp = Head;
	int level = 1;
	char none[10] = "None";
	while (tmp != NULL)
	{
		if (tmp->If_Output == false)
		{
			int degree = 0;
			degree += tmp->GetLeft() ? 1 : 0;
			degree += tmp->GetRight() ? 1 : 0;

			string tmp_char;
			if (tmp->Char) tmp_char = tmp->Char;
			else tmp_char = "None";

			cout << "结点：" << tmp_char << endl;
			cout << "结点的权值：" << tmp->data << endl;
			cout << "结点的度：" << degree << endl;
			cout << "结点的层次：" << level << endl;
			cout << endl;

			tmp->If_Output = true;
		}

		if (tmp->GetLeft() && tmp->GetLeft()->If_Output == false)
		{
			tmp = tmp->GetLeft();
			level++;
			continue;
		}
		else if ((!tmp->GetLeft() || tmp->GetLeft()->If_Output == true) && (tmp->GetRight() && tmp->GetRight()->If_Output == false))
		{
			tmp = tmp->GetRight();
			level++;
			continue;
		}
		else if ((!tmp->GetLeft() && !tmp->GetRight()) || (tmp->GetLeft()->If_Output == true && tmp->GetRight()->If_Output == true))
		{
			tmp = tmp->GetParents();
			level--;
			continue;
		}
	}
}

/*
* 先序遍历也可使用栈
* 通过Push和Pop达到If_Output数组的作用
*/

void Tree::Print_Code()
{
	Ans_Code.Print_My_Vector();
}

void Tree::Print_Decode()
{
	Ans_Decode.Print_My_Vector();
}

void Tree::Create_Tree(char* S)
{
	typedef struct tmp_ch_record
	{
		char ch;
		int amount = 0;
	}tmp_ch_record;

	My_Vector<tmp_ch_record> tmp_amount_pun;
	My_Vector<tmp_ch_record> tmp_amount_ch;

	for (int i = 0; i < strlen(S); i++)
	{
		if (S[i] >= 'a' && S[i] <= 'z')
		{
			if (tmp_amount_ch[S[i] - 'a'].amount == 0) tmp_amount_ch[S[i] - 'a'].amount = 1;
			else tmp_amount_ch[S[i] - 'a'].amount++;
			continue;
		}
		else
		{
			int flag = 0;
			for (int j = 0; j < tmp_amount_pun.Length(); j++)
			{
				if (S[i] == tmp_amount_pun[j].ch)
				{
					tmp_amount_pun[j].amount++;
					flag = 1;
					break;
				}
			}
			if (!flag)
			{
				tmp_ch_record tmp;
				tmp.ch = S[i];
				tmp.amount = 1;
				tmp_amount_pun.Push(tmp);
			}
		}
	}

	typedef struct MultiArray
	{
		Node* node = NULL;
		bool flag = true;
	}MultiArray;

	My_Vector<MultiArray> M_Array;
	for (int i = 0; i < tmp_amount_pun.Length(); i++)
	{
		if (tmp_amount_pun[i].amount != 0)
		{
			MultiArray tmpMA;
			tmpMA.node = new Node(tmp_amount_pun[i].amount, tmp_amount_pun[i].ch);
			M_Array.Push(tmpMA);
		}
	}
	for (int i = 0; i < tmp_amount_ch.Length(); i++)
	{
		if (tmp_amount_ch[i].amount != 0)
		{
			char tmp_char = 'a' + i;
			MultiArray tmpMA;
			tmpMA.node = new Node(tmp_amount_ch[i].amount, tmp_char);
			M_Array.Push(tmpMA);
		}
	}

	int length_judge = M_Array.Length();
	while (length_judge != 1)
	{
		int tmp_pos1 = 0, tmp_pos2;  // 在flag = true的前提下选择pos1, pos2
		while (M_Array[tmp_pos1].flag == false) tmp_pos1++;
		tmp_pos2 = tmp_pos1 + 1;
		while (M_Array[tmp_pos2].flag == false) tmp_pos2++;
		int pos1, pos2;  // M_Array[pos1].node->data <= M_Array[pos2].node->data
		pos1 = M_Array[tmp_pos1].node->data >= M_Array[tmp_pos2].node->data ? tmp_pos2 : tmp_pos1;
		pos2 = M_Array[tmp_pos1].node->data >= M_Array[tmp_pos2].node->data ? tmp_pos1 : tmp_pos2;

		for (int i = max(pos1, pos2) + 1; i < M_Array.Length(); i++)
		{
			if (M_Array[i].flag == true)
			{
				if ((M_Array[i].node->data <= M_Array[pos1].node->data) && (M_Array[i].node->data < M_Array[pos2].node->data))
				{
					if (M_Array[pos1].node->data == M_Array[pos2].node->data && pos1 > pos2)  // 修补逻辑：pos1 = 2, pos1.weight = 3; pos2 = 1, pos2.weight = 3时，i = 4,i.weight = 2
						                                                                      // 此时需要使pos2指向靠前的位置，即直接让pos1为i
					{
						pos1 = i;
					}
					else
					{
						pos2 = pos1;
						pos1 = i;
					}
				}
				else if ((M_Array[i].node->data < M_Array[pos2].node->data) && (M_Array[i].node->data >= M_Array[pos1].node->data))
				{
					pos2 = i;
				}
			}
		}
		if (M_Array[pos1].node->data == M_Array[pos2].node->data)  // 权值相等时，字母序列小的为pos1
		{
			if (pos1 > pos2)
			{
				int tmp;
				tmp = pos1;
				pos1 = pos2;
				pos2 = tmp;
			}
		}

		MultiArray tmp;
		Node* new_node;
		new_node = Creat_New_Node(M_Array[pos1].node->data + M_Array[pos2].node->data);
		tmp.node = new_node;

		Head = new_node;

		Connect_Node(*new_node, *M_Array[pos1].node, "left");
		Connect_Node(*new_node, *M_Array[pos2].node, "right");

		if (M_Array[pos1].node->GetLeft() == NULL && M_Array[pos1].node->GetRight() == NULL) ChCoding.Push(M_Array[pos1].node);
		if (M_Array[pos2].node->GetLeft() == NULL && M_Array[pos2].node->GetRight() == NULL) ChCoding.Push(M_Array[pos2].node);

		M_Array[pos1].flag = false;
		M_Array[pos2].flag = false;

		M_Array.Push(tmp);

		length_judge--;
	}
}

void Tree::Coding(char* S)
{
	typedef struct coding
	{
		My_Vector<char> code;
		char ch;
	}coding;

	My_Vector<coding> cd;
	int num_coding = 0;
	for (int i = 0; i < ChCoding.Length(); i++)
	{
		Node* tmp_node = ChCoding[i];
		while (tmp_node != Head)
		{
			if (tmp_node->GetParents()->GetLeft() == tmp_node)
			{
				cd[num_coding].code.Push('0');
				tmp_node = tmp_node->GetParents();
			}
			else if (tmp_node->GetParents()->GetRight() == tmp_node)
			{
				cd[num_coding].code.Push('1');
				tmp_node = tmp_node->GetParents();
			}
		}
		cd[num_coding].ch = ChCoding[i]->Char;
		num_coding++;
	}

	for (int i = 0; i < num_coding; i++) cd[i].code.Reverse();

	int k = 0;
	for (int i = 0; i < strlen(S); i++)
	{
		for (int j = 0; j < num_coding; j++)
		{
			if (S[i] == cd[j].ch)
			{
				for (int n = 0; n < cd[j].code.Length(); n++) Ans_Code.Push(cd[j].code[n]);
			}
		}
	}
}

void Tree::Decoding(char* S)
{
	Node* tmpNode = Head;
	for (int i = 0; i < strlen(S) + 1; i++)
	{
		if (tmpNode->Char)
		{
			Ans_Decode.Push(tmpNode->Char);
			tmpNode = Head;
		}
		if (S[i] == '0' && i < strlen(S))
			tmpNode = tmpNode->GetLeft();
		else if (S[i] == '1' && i < strlen(S))
			tmpNode = tmpNode->GetRight();
	}

	if (tmpNode != Head)
	{
		cout << "ERROR_03";
		exit(0);
	}
}