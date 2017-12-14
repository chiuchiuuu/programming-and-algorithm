/*
描述

一个以'.'结尾的简单英文句子，单词之间用空格分隔，没有缩写形式和其它特殊形式

输入

一个以'.'结尾的简单英文句子（长度不超过500），单词之间用空格分隔，没有缩写形式和其它特殊形式

输出

该句子中最长的单词。如果多于一个，则输出第一个
*/

#include <iostream>
using namespace std;

int main()
{
	char sentence[500];
	int len = 0, maxLen = 0;
	int ptr = 0, maxPtr = 0;

	cin.getline(sentence, 500);

	int i = 0;
	while (sentence[i] != '.')
	{
		if (sentence[i] == ' ')
		{
			ptr = i + 1;
			len = 0;
		}
		else
		{
			len++;
		}
		if (len > maxLen)
		{
			maxLen = len;
			maxPtr = ptr;
		}
		i++;
	}

	for (int i = maxPtr; i < maxPtr + maxLen; i++)
	{
		cout << sentence[i];
	}

	cout << endl;
	return 0;
}
