/*
描述

在一个字符串中找出元音字母a,e,i,o,u出现的次数。

输入

输入一行字符串（字符串中可能有空格，请用cin.getline(s,counts)方法把一行字符串输入到字符数组s中，其中counts是s的最大长度，这道题里面可以直接写80。），字符串长度小于80个字符。

输出

输出一行，依次输出a,e,i,o,u在输入字符串中出现的次数，整数之间用空格分隔。
*/

#include <iostream>
using namespace std;

int main()
{
	char str[80];
	int count[5] = { 0 };
	cin.getline(str, 80);

	for (int i = 0; str[i] != '\0'; i++)
	{
		switch (str[i])
		{
		case 'a':
			count[0]++;
			break;
		case 'e':
			count[1]++;
			break;
		case 'i':
			count[2]++;
			break;
		case 'o':
			count[3]++;
			break;
		case 'u':
			count[4]++;
			break;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		cout << count[i] << ' ';
	}

	return 0;
}
