#include "My_Stack.h"
#include "solving.h"
#include <iostream>
using namespace std;

int solving::pri(char c1, char c2)  // c1为*(op.top - 1)，c2为*(op.top- 2)。
// 返回1表示c2优先级高于c1（c2为*，c1为+），要计算c2；返回-1表示c2优先级低于c1，要继续读入运算符。
// 也可以用二维数组表达优先级
{
	if (c1 == '!')
		return 1;
	switch (c2)
	{
	case '+':
	{
		if ((c1 == '*') || (c1 == '/') || (c1 == '^') || (c1 == '('))
			return -1;
		else
			return 1;
	}
	case '-':
	{
		if ((c1 == '*') || (c1 == '/') || (c1 == '^') || (c1 == '('))
			return -1;
		else
			return 1;
	}
	case '*':
	{
		if ((c1 == '^') || (c1 == '('))
			return -1;
		else
			return 1;
	}
	case '/':
	{
		if ((c1 == '^') || (c1 == '('))
			return -1;
		else
			return 1;
	}
	case '^':
	{
		if (c1 == '(')
			return -1;
		else
			return 1;
	}
	case ')':
		return -1;
	case '(':
		return -1;
	}
}

double solving::calculate(char c, double a, double b)  // a b c
{
	switch (c)
	{
	case '+':
	{
		return (a + b);
		break;
	}
	case '-':
	{
		return (a - b);
		break;
	}
	case '*':
	{
		return (a * b);
		break;
	}
	case '/':
	{
		if (b == 0)
		{
			cout << "ERROR_03";
			exit(0);
		}
		else
		{
			return (a / b);
			break;
		}
	}
	case '^':
	{
		return pow(a, b);
		break;
	}
	default:
	{
		cout << "ERROR_02";  // c若不是运算符，则为表达式存在格式错误
		exit(0);
	}
	}
}

double solving::solving_m_exp(char* input)
{
	my_stack<double> num;
	my_stack<char> op;

	int flag;  // 判断读取到的是否为运算符
	int i = 0;  // 循环
	int fix = 0;  // 是否添加'!'
	while (input[i] != '\0' || ((op.top - op.base) != fix || *(op.top - 1) != '!')) // 不断读取数字和运算符，并在读取结束之后继续循环，以计算表达式的值
	{						// ((op.top - op.base) != fix || *(op.top - 1) != '!') 读取结束之后，Operator中有且只有'!'时结束
		flag = 1;  // 判断读取到的是否为运算符，每读取到一次运算符，即进入判断优先级并决定是否计算的环节
		if (input[i] != '\0')
		{
			if (input[i] >= '0' && input[i] <= '9')  // 读取一位数
			{
				if ((input[i + 1] < '0' || input[i + 1] > '9') && input[i + 1] != '.')
				{
					num.Push((double)(input[i] - 48));  // 一位数读取结束
					flag = 0;
					i++;
				}
				else  // 读取多位数
				{
					double temp = (double)(input[i] - 48);
					for (int m = 0; ; m++)
					{
						if (input[i + m + 1] >= '0' && input[i + m + 1] <= '9')
						{
							temp = temp * 10 + (input[i + m + 1] - 48);  // 读取多位数
							if ((input[i + m + 2] < '0' || input[i + m + 2] > '9') && input[i + m + 2] != '.')  // 多位数且无小数部分
							{
								i += (m + 2);
								break;
							}
						}
						else if (input[i + m + 1] == '.')  // 读取小数部分
						{
							int k;
							for (k = 1; input[i + m + k + 1] >= '0' && input[i + m + k + 1] <= '9'; k++)
							{
								temp += (pow(10, -k) * (input[i + m + k + 1] - 48));
							}
							i += (m + k + 1);
							break;
						}
					}
					num.Push(temp);  // 多位数读取结束
					flag = 0;
				}
			}
			else
			{
				if (input[i] == '[' || input[i] == '{') input[i] = '(';  // 读取括号时，不区分大/中/小括号
				else if (input[i] == ']' || input[i] == '}') input[i] = ')';
				op.Push(input[i]);
				i++;
			}
		}
		else
		{
			if (!fix)  // 添加过'!'则不再添加
			{
				op.Push('!');  // 通过设置优先级，使"!"低于所有运算符，即可计算最后一个有意义的运算符
				fix = 1;
			}
		}
		if (flag)  // 读取到运算符或读取结束时运行
		{
			switch (pri(*(op.top - 1), *(op.top - 2)))
			{
			case -1:
				break;
			case 1:
			{
				char tempOp, tempOp_;
				double tempNum;
				op.Pop(tempOp);
				num.Pop(tempNum);
				*(num.top - 1) = calculate(*(op.top - 1), *(num.top - 1), tempNum);
				op.Pop(tempOp_);
				op.Push(tempOp);
				if (tempOp == ')' && *(op.top - 2) == '(')  // 若出现'('和')'，则将二者Pop
				{
					op.Pop(tempOp);
					op.Pop(tempOp);
				}
				break;
			}
			}
		}
	}
	return  *(num.top - 1);
}