/*
找出第k大的数

描述

用户输入N和K，然后接着输入N个正整数（无序的），程序在不对N个整数排序的情况下，找出第K大的数。注意，第K大的数意味着从大到小排在第K位的数。

输入

N

K

a1 a2 a3 a4 ..... aN

输出

b
*/

#include <iostream>
using namespace std;

int main()
{
	int n = 0, k = 0;
	cin >> n >> k;
	// 没有给n的范围，所以动态创建数组
	int *a = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	for (int i = 0; i < n; i++)
	{
		// 找到比a[i]大的个数，若为k-1则a[i]是第k大的数
		int bigger = 0;
		for (int j = 0; j < n; j++)
		{
			if (a[j] > a[i])
			{
				bigger++;
			}
		}
		if (bigger == k - 1)
		{
			cout << a[i] << endl;
			break;
		}
	}
	delete[] a;
	return 0;
}
