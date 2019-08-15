# Week2：枚举

## 枚举的基本思想

枚举是基于已有知识进行答案猜测的一种问题求解策略。

枚举从可能的集合中一一列举各元素， 对问题可能解集合的每一项，根据问题给定的检验条件判定哪些是成立的，使条件成立的即是问题的解。

### 枚举过程

- 判断猜测的答案是否正确
- 进行新的猜测: 有两个关键因素要注意
  - 猜测的结果必须是前面的猜测中没有出现过的. 
  - 猜测的过程中要及早排除错误的答案. 

### 枚举中的三个关键问题

问题一：给出解空间

- 给出解空间，建立简洁的数学模型 
- 模型中变量数尽可能少, 它们之间相互独立 

问题二：减少搜索空间

- 利用知识缩小模型中各变量的取值范围, 避免不必要的计算 
- 减少代码中循环体执行次数

问题三：合适的搜索顺序

- 搜索空间的遍历顺序要与模型中条件表达式一致 

例：求小于N的最大素数

- 2是素数, 记为PRIM0
- 根据PRIM0, PRIM1 , …, PRIMk, 寻找比PRIMk大的最小素数PRIMk+1
- 如果PRIMk+1大于N, 则PRIMk是我们需要找的素数, 否则继续寻找 
- 解空间：2到N的所有素数
- 减小搜索空间：排除所有奇数

## 熄灯问题

有一个由按钮组成的矩阵，其中每行有6个按钮, 共5行，每个按钮的位置上有一盏灯，当按下一个按钮后，该按钮以及周围位置(上边, 下边, 左边, 右边)的灯都会改变一次。请你写一个程序, 确定需要按下哪些按钮, 恰好使得所 有的灯都熄灭

### 输入

- 第一行是一个正整数N, 表示需要解决的案例数
- 每个案例由5行组成, 每一行包括6个数字
- 这些数字以空格隔开, 可以是0或1
- 0 表示灯的初始状态是熄灭的
- 1 表示灯的初始状态是点亮的

### 输出

- 对每个案例, 首先输出一行, 输出字符串 “PUZZLE #m”, 其中m是该案例的序号
- 接着按照该案例的输入格式输出5行
- 1 表示需要把对应的按钮按下
- 0 表示不需要按对应的按钮
- 每个数字以一个空格隔开

### 解题分析

枚举法。

解空间：5x6的0-1矩阵的所有可能情况：$2^{30}$种可能

减小搜索空间：

- 当第一行的按钮情况确定以后，要使第一行全熄灭，第二行已经被确定，同理剩余几行都被确定了
- 因此枚举的情况减小为第一行的所有可能：$2^6 = 64$
- 最后只需验证最后一行

合适的搜索顺序：

- 六个循环嵌套
- 把第一行当作二进制数，每次加1，然后处理进位✓

### 解答程序

```cpp
#include<stdio.h>
#include<iostream>
using namespace std;
int puzzle[6][8], press[6][8];

void init() {
	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			cin >> puzzle[i][j];
		}
	}
	for (int i = 0; i < 6; i++) {
		press[i][0] = 0;
		press[i][7] = 0;
	}
	for (int i = 0; i < 8; i++) {
		press[0][i] = 0;
	}
}
bool guess() {
	for (int c = 1; c < 7; c++) {
		if ((press[5][c - 1] + press[5][c] + press[5][c + 1] + press[4][c]) % 2 != puzzle[5][c]) {
			return false;
		}
		return true;
	}
}

void update(){
	for (int i = 1; i < 5; i++)
		{
		for (int j = 1; j < 7; j++)
			{
				press[i + 1][j] = (puzzle[i][j] + press[i][j] + press[i][j - 1] + press[i][j + 1] + press[i - 1][j]) % 2;
			}
		}
	}

void enmuerate() {
	for (int j = 1; j < 7; j++) {
		press[1][j] = 0;
	}
	update();
	while (!guess())
	{
		press[1][1]++;
		int c = 1;
		while (press[1][c] > 1) {
			press[1][c] = 0;
			press[1][++c] ++;
		}
		update();
	}
	
}
int main()
{
	int ncase;
	cin >> ncase;
	for (int i = 0; i < ncase; i++)
	{
		cout << "PUZZLE #" << i + 1 << endl;
		init();
		enmuerate();
		for (int i = 1; i < 6; i++)
		{
			for (int j = 1; j < 7; j++)
			{
				cout << press[i][j] << " ";
			}
			cout << endl;
		}
	}
}
```

## 讨厌的青蛙

### 问题描述

有一种小青蛙，每到晚上，这种青蛙会跳跃稻田，从而踩踏稻子。农民早上看到被踩踏的稻子, 希望找到造成最大损害的那只青蛙经过的路径。每只青蛙总是沿着一条直线跳跃稻田，且每次跳跃的距离都相同。请写一个程序，确定在各条青蛙行走路径中, 踩踏水稻最多的那一条上，有多少颗水稻被踩踏。

### 输入

- 从标准输入设备上读入数据
- 第一行上两个整数R, C, 分别表示稻田中水稻的行数和 列数, 1≤R, C≤5000
- 第二行是一个整数N, 表示被踩踏的水稻数量, 3≤N≤5000
- 在剩下的N行中, 每行有两个整数, 分别是一颗被踩踏水 稻的行号(1~R)和列号(1~C), 两个整数用一个空格隔开
- 且每棵被踩踏水稻只被列出一次

### 输出

- 从标准输出设备上输出一个整数
- 如果在稻田中存在青蛙行走路径, 则输出包含最多水稻 的青蛙行走路径中的水稻数量, 否则输出0

### 样例输入

```cpp
6 7
14
2 1
6 6
4 2
2 5
2 6
2 7
3 4
6 1
6 2
2 3
6 3
6 4
6 5
6 7
```

### 样例输出

```cpp
7
```

### 解题思路

解空间：所有可能的直线路径

减小搜索空间：

- 每条青蛙行走路径中至少有3颗水稻（看了半天题目没搞懂为什么，就当题设吧）
- 路径的起点和终点在稻田外

枚举方法：

- 枚举所有点（低效，不可行）
- 任取两个点作为稻田内的起始点，计算步长得到整条路径
  - `sort`
  - `binary_search`

### 解题程序

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int row, col, numOfPoints;

struct Point
{
	int x, y;
};
Point points[5001];

bool operator<(const Point &p1, const Point &p2)
{
	if (p1.x == p2.x)
	{
		return p1.y < p2.y;
	}
	else
	{
		return p1.x < p2.x;
	}
}

int searchPath(Point p, int dx, int dy)
{
	Point tmp;
	int steps;
	tmp.x = p.x + dx;
	tmp.y = p.y + dy;
	steps = 2;
	while (tmp.x <= row && tmp.x >= 1 && tmp.y <= col && tmp.y >= 1)
	{
		if (binary_search(points, points + numOfPoints, tmp))
		{
			tmp.x += dx;
			tmp.y += dy;
			steps++;
		}
		else
		{
			steps = 0;
			break;
		}
	}
	return steps;
}

int main()
{

	cin >> row >> col >> numOfPoints;

	for (int i = 0; i < numOfPoints; i++)
	{
		cin >> points[i].x >> points[i].y;
	}
	sort(points, points + numOfPoints);

	int maxStep = 2;
	for (int i = 0; i < numOfPoints - 1; i++)
	{
		for (int j = i + 1; j < numOfPoints; j++)
		{
			int dx = points[j].x - points[i].x;
			int dy = points[j].y - points[i].y;
			// 起点在稻田内，更换第二个点
			if (points[i].x - dx >= 1 && points[i].x - dx <= row && points[i].y - dy >= 1 && points[i].y - dy <= col)
			{
				continue;
			}
			// 当走 maxStep 时在x方向已经走出稻田，更换第一个点
			if (points[i].x + (maxStep - 1) * dx > row)
			{
				break;
			}
			// 当走 maxStep 时在y方向已经走出稻田，更换第二个点
			if (points[i].y + (maxStep - 1) * dy > col || points[i].y + (maxStep - 1) * dy < 1)
			{
				continue;
			}
			int steps = searchPath(points[j], dx, dy);
			if (steps > maxStep)
			{
				maxStep = steps;
			}
		}
	}
	maxStep = maxStep == 2 ? 0 : maxStep;
	cout << maxStep << endl;
	return 0;
}
```

