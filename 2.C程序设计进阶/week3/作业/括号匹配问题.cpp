/*
编程题＃4：扩号匹配问题
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在某个字符串（长度不超过100）中有左括号、右括号和大小写字母；规定（与常见的算数式子一样）任何一个左括号都从内到外与在它右边且距离最近的右括号匹配。写一个程序，找到无法匹配的左括号和右括号，输出原来字符串，并在下一行标出不能匹配的括号。不能匹配的左括号用"$"标注,不能匹配的右括号用"?"标注.

输入
输入包括多组数据，每组数据一行，包含一个字符串，只包含左右括号和大小写字母，字符串长度不超过100

注意：cin.getline(str,100)最多只能输入99个字符！

输出
对每组输出数据，!!!输出两行，第一行包含原始输入字符!!!，第二行由"$","?"和空格组成，"$"和"?"表示与之对应的左括号和右括号不能匹配。
*/

#include <iostream>
#include <cstring>
using namespace std;

/*
匹配括号
输入：
	char str[]: 匹配的字符串
	int start: 匹配起始位置
	bool *matched: 一维数组，匹配成功为true，否则为false
返回值：
	int n：
		匹配成功返回右括号index
		匹配结束返回-1
*/
int match(char str[], int start, bool *matched)
{
	if (strlen(str) == start)
	{
		return -1; //匹配结束
	}
	else
	{
		if (str[start] == '(')
		{
			int n = match(str, start + 1, matched);
			if (str[n] == ')')
			{
				matched[start] = true;
				matched[n] = true;
				return match(str, n + 1, matched);
			}
			else
			{
				return n;
			}
		}
		else if (str[start] == ')')
		{
			return start;
		}
		else
		{
			return match(str, start + 1, matched);
		}
	}
}

int main()
{
	char str[100];
	// 多组输入
	while (cin.getline(str, 101))
	{
		bool matched[101] = { 0 };

		// 匹配括号
		int n = match(str, 0, matched);
		while (n != -1)
		{
			n = match(str, n + 1, matched);
		}

		// 输出结果
		cout << str << endl;
		for (int i = 0; str[i] != '\0'; i++)
		{
			char output = ' ';
			if (!matched[i])
			{
				switch (str[i])
				{
				case '(':
					output = '$';
					break;
				case ')':
					output = '?';
					break;
				}
			}
			cout << output;
		}
		cout << endl;
	}
	return 0;
}