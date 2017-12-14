/*
找和为k的两个元素

描述

在一个长度为n(n < 1000)的整数序列中，判断是否存在某两个元素之和为k。

输入

第一行输入序列的长度n和k，用空格分开。

第二行输入序列中的n个整数，用空格分开。

输出

如果存在某两个元素的和为k，则输出yes，否则输出no。
*/

#include <iostream>
using namespace std;

int main()
{
	int n = 0, k = 0;
	int a[1000];

	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] + a[j] == k)
			{
				cout << "yes" << endl;
				return 0;
			}
		}
	}
	cout << "no" << endl;
	return 0;
}
