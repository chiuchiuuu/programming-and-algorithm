/*
编程题＃4：寻找平面上的极大点
来源 POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制 1000ms 内存限制 65536kB

描述
在一个平面上，如果有两个点(x,y),(a,b),如果说(x,y)支配了(a,b)，这是指x=a,y=b;

用图形来看就是(a,b)坐落在以(x,y)为右上角的一个无限的区域内。

给定n个点的集合，一定存在若干个点，它们不会被集合中的任何一点所支配，这些点叫做极大值点。

编程找出所有的极大点，按照x坐标由小到大，输出极大点的坐标。

本题规定：n不超过100，并且不考虑点的坐标为负数的情况。

输入
输入包括两行，第一行是正整数n，表示是点数，第二行包含n个点的坐标，坐标值都是整数，坐标范围从0到100，输入数据中不存在坐标相同的点。

输出
按x轴坐标最小到大的顺序输出所有极大点。

输出格式为(x1,y1),(x2,y2),...(xk,yk)

注意：输出的每个点之间有,分隔,最后一个点之后没有,,少输出和多输出都会被判错
*/

#include <iostream>
#include <ctype.h>
using namespace std;

struct Point
{
	int x;
	int y;
};

int main()
{
	// 点的个数
	int n = 0;
	cin >> n;

	Point point[100];
	for (int i = 0; i < n; i++)
	{
		cin >> point[i].x >> point[i].y;
	}

	// 找出所有的极大值点，并保存在maxPoint[100]中
	Point maxPoint[100];
	int num = 0; // 极大值点的个数
	for (int i = 0; i < n; i++)
	{
		bool isMaxPoint = true;
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				continue;
			}
			if (point[i].x <= point[j].x && point[i].y <= point[j].y)
			{
				isMaxPoint = false;
				break;
			}
		}
		if (isMaxPoint)
		{
			maxPoint[num++] = point[i];
		}
	}

	// 根据横坐标排序，冒泡排序
	for (int i = 0; i < num; i++)
	{
		for (int j = 1; j < num; j++)
		{
			if (maxPoint[j - 1].x > maxPoint[j].x)
			{
				Point temp = maxPoint[j - 1];
				maxPoint[j - 1] = maxPoint[j];
				maxPoint[j] = temp;
			}
		}
	}

	// 输出最后结果
	for (int i = 0; i < num - 1; i++)
	{
		cout << "(" << maxPoint[i].x << "," << maxPoint[i].y << "),";
	}
	// 由于格式要求，最后一个单独输出
	cout << "(" << maxPoint[num - 1].x << "," << maxPoint[num - 1].y << ")" << endl;
	return 0;
}