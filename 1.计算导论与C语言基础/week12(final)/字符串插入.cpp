/*
描述

有两个字符串str和substr，str的字符个数不超过10，substr的字符个数为3。（字符个数不包括字符串结尾处的'\0'。）将substr插入到str中ASCII码最大的那个字符后面，若有多个最大则只考虑第一个。

输入

输入包括若干行，每一行为一组测试数据，格式为

str substr

输出

对于每一组测试数据，输出插入之后的字符串。
*/

#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char str[11];
	char substr[4];
	char newstr[14];

	while (cin >> str >> substr)
	{
		int len = strlen(str);
		int maxIndex = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (str[i] > str[maxIndex])
			{
				maxIndex = i;
			}
		}

		for (int i = 0; i <= maxIndex; i++)
		{
			newstr[i] = str[i];
		}
		for (int i = maxIndex + 1, j = 0; substr[j] != '\0'; i++, j++)
		{
			newstr[i] = substr[j];
		}
		for (int i = maxIndex + 1; i < strlen(str) + 1; i++)
		{
			newstr[i + 3] = str[i];
		}

		cout << newstr << endl;
	}
	return 0;
}
