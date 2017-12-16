/*
编程题＃3：寻找山顶
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在一个m×n的山地上，已知每个地块的平均高程，请求出所有山顶所在的地块（所谓山顶，就是其地块平均高程不比其上下左右相邻的四个地块每个地块的平均高程小的地方)。

输入
第一行是两个整数，表示山地的长m（5≤m≤20）和宽n（5≤n≤20）。

其后m行为一个m×n的整数矩阵，表示每个地块的平均高程。每行的整数间用一个空格分隔。

输出
输出所有上顶所在地块的位置。每行一个。按先m值从小到大，再n值从小到大的顺序输出。
*/

#include <iostream>
using namespace std;

int main()
{
	int m = 0, n = 0;
	cin >> m >> n;

	int altitude[22][22] = { 0 };
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> altitude[i][j];
		}
	}

	int(*p)[22] = altitude;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (p[i][j] >= p[i][j - 1] && p[i][j] >= p[i][j + 1]
				&& p[i][j] >= p[i - 1][j] && p[i][j] >= p[i + 1][j])
			{
				cout << i - 1 << ' ' << j - 1 << endl;
			}
		}
	}
	return 0;
}
