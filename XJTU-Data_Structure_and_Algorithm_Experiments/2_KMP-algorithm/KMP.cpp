#include "KMP.h"
#include <iostream>
#include "MyString.h"
using namespace std;

KMP::KMP(char* ch_T, char* ch_P) :Text(ch_T), Pattern(ch_P) {};

KMP::~KMP(){}

void KMP::Generate_Next()
{

	Next[0] = 1;
	Next[1] = 1;
	
	for (int i = 1; i + 1 < Pattern.StrLength(); i++)
	{
		int count = 1;  // 开始算Next[i]
		for (int j = 0; j < Pattern.StrLength(); j++)
		{
			if (Pattern[i] == Pattern[j])  // 相等时
			{
				count++;
				Next[i + 1] = count;
				int k = 0;
				int n = i;
				for (k = 1; ; k++)  // 连续相等时
				{
					if (Pattern[n + k] == Pattern[j + k])
					{
						count++;
						Next[n + k + 1] = count;
						i++;
					}
					else
						break;
				}
				break;
			}
			else  // 不等时
			{
				Next[i + 1] = count;
				break;
			}
		}
	}
}

int KMP::KMP_Matching()
{
	Generate_Next();
	int i = 0;
	int j = 0;
	while(i < Text.StrLength() && j < Pattern.StrLength())
	{
		if (Text[i] == Pattern[j])
		{
			i++;
			j++;
		}
		else  // 遇到不相等元素后，利用Next数组重新设定j
		{
			j = Next[j] - 1;
			i++;
		}
	}
	if (j == Pattern.StrLength())  // Pattern被读完，j指向Pattern最后一位，i指向Text中与Pattern相同的最后一位
	{
		return i - j + 1;
	}
	else
		return -1;  // i扫过Text，但j还未扫过Pattern，则未找到
}