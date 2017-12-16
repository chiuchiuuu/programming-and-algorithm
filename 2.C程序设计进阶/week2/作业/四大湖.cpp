/*
编程题＃2：四大湖

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述

我国有4大淡水湖。

A说：洞庭湖最大，洪泽湖最小，鄱阳湖第三。

B说：洪泽湖最大，洞庭湖最小，鄱阳湖第二，太湖第三。

C说：洪泽湖最小，洞庭湖第三。

D说：鄱阳湖最大，太湖最小，洪泽湖第二，洞庭湖第三。

已知这4个湖的大小均不相等，4个人每人仅答对一个，

请编程按照鄱阳湖、洞庭湖、太湖、洪泽湖的顺序给出他们的大小排名。

输入

无。

输出

输出为4行，第1行为鄱阳湖的大小名次，从大到小名次分别表示为1、2、3、4；第2、3、4行分别为洞庭湖、太湖、洪泽湖的大小名次。

样例输入
(无)

样例输出
3
2
1
4
*/

#include <iostream>
using namespace std;

int check(int guess[], int order[]);


int main()
{
	// 顺序：鄱阳湖、洞庭湖、太湖、洪泽湖
	int guessA[4] = { 3,1,0,4 };
	int guessB[4] = { 2,4,3,1 };
	int guessC[4] = { 0,3,0,4 };
	int guessD[4] = { 1,3,4,2 };

	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (j == i)
			{
				continue;
			}
			for (int k = 1; k <= 4; k++)
			{
				if (k == i || k == j)
				{
					continue;
				}
				for (int l = 1; l <= 4; l++)
				{
					if (l == i || l == j || l == k)
					{
						continue;
					}
					int order[4] = { i, j, k, l };
					if (check(guessA, order) == 1 && check(guessB, order) == 1 && check(guessC, order) == 1 && check(guessD, order) == 1)
					{
						for (int m = 0; m < 4; m++)
						{
							cout << order[m] << endl;
						}
						return 0;
					}
				}
			}
		}
	}
	return 0;
}

int check(int guess[], int order[])
{
	int result = 0;
	for (int i = 0; i < 4; i++)
	{
		if (order[i] == guess[i])
		{
			result++;
		}
	}
	return result;
}
