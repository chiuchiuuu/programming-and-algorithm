# 递归

## 递归的基本思想

递归 — 某个函数直接或间接的调用自身

问题的求解过程

- 划分成许多相同性质的子问题的求解
- 而小问题的求解过程可以很容易的求出

这些子问题的解就构成里原问题的解

### 递归与枚举

枚举把一个问题划分成一组子问题，依次对这些子问题求解

- 子问题之间是横向的，同类的关系

把一个问题逐级分解成子问题

- 子问题与原问题之间是纵向的, 同类的关系
- 语法形式上: 在一个函数的运行过程中, 调用这个函数自己
  - 直接调用: 在`fun()`中直接执行`fun()`
  - 间接调用: 在`fun1()`中执行`fun2()`; 在`fun2()`中又执行`fun1()`

### 三个要点

- 递归式
  - 如何将原问题划分成子问题
- 递归出口
  - 递归终止的条件, 即最小子问题的求解,可以允许多个出口
- 界函数
  - 问题规模变化的函数, 它保证递归的规模向出口条件靠拢

### 关键

- 找出递推公式
- 找到递归终止条件

注意事项: 由于函数的局部变量是存在栈上的，如果有体积大的局部变量（比如数组）而递归层次可能很深的情况下，也许会导致栈溢出。可以考虑使用全局数组或动态分配数组。



## 连连看小游戏

###  问题描述

游戏在一个分割成 w * h 个正方格 子的矩形板上进行，每个正方格子上可以有一张游戏卡 片，当然也可以没有

当下面的情况满足时，认为两个游戏卡片之间有一条路径相连：

- 路径只包含水平或者竖直的直线段
- 路径不能穿过别的游戏卡片
- 但是允许路径临时的离开矩形板

判断是否存在一条满足题意的路径能连接给定的两个游戏卡片

### 输入

- 输入包括多组数据
- 一个矩形板对应一组数据
- 第一行包括两个整数 w和h (1 <= w, h <= 75，分别表示矩形板的宽度和长度
- 下面的h行, 每行包括w个字符，表示矩形板上的游戏卡 片分布情况：
  - 使用 ‘X’ 表示这个地方有一个游戏卡片
  - 使用 空格 表示这个地方没有游戏卡片
- 之后每行上包括4个整数: x1, y1, x2, y2 (1 <= x1, x2 <= w, 1 <= y1, y2 <= h)给出两个卡片在矩形板上的位置 
  - 注意: 矩形板左上角的坐标是(1,1)
  - 输入保证这两个游戏卡片所处的位置是不相同的
  - 如果一行上有4个0, 表示这组测试数据的结束
- 如果一行上给出w = h = 0，那么表示所有的输入结束了

### 输出

- 对每一个矩形板, 输出一行 “Board #n:”, n是输入数据的编号
- 对每一组需要测试的游戏卡片输出一行。这一行的开头 是 “Pair m: ”, 这里m是测试卡片的编号（对每个矩形板, 编号都从1开始）
- 如果可以相连，找到连接这两个卡片的所有路径中包括线段数最少的路径, 输出 “k segments.” k是找到的最优路径中包括的线段的数目
- 如果不能相连, 输出 “impossible.”
- 每组数据之后输出一个空行

### 样例输入

```
5 4
xxxxx
x   x
xxx x
 xxx 
2 3 5 3
1 3 4 4
2 3 3 4
0 0 0 0
0 0
```

样例输出

```
Board #1:
Pair 1: 4 segments.
Pair 2: 3 segments.
Pair 3: impossible.
```

### 解题分析

迷宫求解问题：自相似性表现在每走一步的探测方式相同，可以用递归方法求解

通过枚举方式找到从起点到终点的路径, 朝一个方向走下去：

- 如果走不通, 则换个方向走
- 四个方向都走不通, 则回到上一步的地方, 换个方向走
- 依次走下去, 直到走到终点

### 解题程序

```c++
#include <iostream>
using namespace std;

char Board[77][77] = { 0 };
bool Mark[77][77] = { 0 };
int minstep;
int width, height;
int to[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };

void searchPath(int x, int y, int end_x, int end_y, int step, int dir)
{
	if (step > minstep)
	{
		return;
	}
	if (x == end_x && y == end_y)
	{
		if (step < minstep)
		{
			minstep = step;
			return;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		int new_x = x + to[i][0];
		int new_y = y + to[i][1];
		if ((new_x > -1 && new_x < width + 2 && new_y > -1 && new_y < height + 2)
			&& ((Board[new_y][new_x] == ' ' && !Mark[new_y][new_x])
				|| (Board[new_y][new_x] == 'x' && new_x == end_x && new_y == end_y)))
		{
			Mark[new_y][new_x] = true;
			if (i == dir)
			{
				searchPath(new_x, new_y, end_x, end_y, step, i);
			}
			else
			{
				searchPath(new_x, new_y, end_x, end_y, step + 1, i);
			}
			// 这条路径没搜到，撤回标记
			Mark[new_y][new_x] = false;
		}
	}
}

int main()
{
	while (cin >> width >> height)
	{
		if (!height && !height)
		{
			break;
		}
		// 输入Board
		for (int i = 1; i <= height; i++)
		{
			cin.get();
			for (int j = 1; j <= width; j++)
			{
				Board[i][j] = cin.get();
			}
		}
		// 处理Board边缘
		for (int i = 0; i < height + 2; i++)
		{
			Board[i][0] = ' ';
			Board[i][width + 1] = ' ';
		}
		for (int j = 0; j < width + 2; j++)
		{
			Board[0][j] = ' ';
			Board[height + 1][j] = ' ';
		}

		int x, y, end_x, end_y;
		int pair = 0;
		while (cin >> x >> y >> end_x >> end_y)
		{
			pair++;
			minstep = 100000;
			if (x && y && end_x && end_y)
			{
				searchPath(x, y, end_x, end_y, 0, -1);
				cout << "Pair " << pair << ": ";
				if (minstep == 100000)
				{
					cout << "impossible." << endl;
				}
				else
				{
					cout << minstep << " segments." << endl;
				}
			}
			else
			{
				break;
			}
		}
		cout << endl;
	}
	return 0;
}
```



## 棋盘分割

### 问题描述

将一个8*8的棋盘进行如下分割：将原棋盘割下一块矩形棋盘并使剩下部分也是矩形，再将剩下的部分继续如此分割，这样割了(n-1)次后，连同最后剩下的矩形棋盘共有n块矩形棋盘。（每次切割都只能沿着棋盘格子的边进行）

原棋盘上每一格有一个分值，一块矩形棋盘的总分为其所含各格分值之和。现在需要把棋盘按上述规则分割成 n 块矩形棋盘，并使各矩形棋盘总分的均方差最小。
$$
\sigma = \sqrt{\frac{\sum\limits_{i=1}^n (x_i - \overline x)^2}{n}} \\
\overline x = \frac{\sum\limits_{i=1}^n x_i}{n}
$$

$x_i$ 为第 $i$ 块矩形棋盘的总分，请编程对给出的棋盘及 n, 求出 $\sigma$ 的最小值

### 输入

第1行为一个整数n (1 < n < 15)，第2行至第9行每行为8个小于100的非负整数，表示棋盘上 相应格子的分值，每行相邻两数之间用一个空格分隔。

### 输出

$\sigma$ 四舍五入精确到小数点后三位

### 样例输入

```
3
1 1 1 1 1 1 1 3
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 0
1 1 1 1 1 1 0 3
```

### 样例输出

```
1.633
```

### 解题分析

1. 均方差最小转化为求最小 $\sum x_i^2$ （$\sum x_i^2 - n \overline x^2$）

2. 编写 `split(n, x1, y1, x2, y2)` 递归实现对棋盘的分割。返回值是以(x1, y1)为左上角，(x2, y2) 为右下角棋盘分割成 n 份后的最小平方和

3. 棋盘的分割方式有四种
   $$
   \begin{aligned}
   split(n, x1, y1, x2, y2) = \min\{ &\min_{i=x1}^{x2-1} \{ split(n-1,x1,y1,i,y2)+split(1,i+1,y1,x2,y2\}, \\
   & \min_{i=x1}^{x2-1} \{ split(1,x1,y1,i,y2)+split(n-1,i+1,y1,x2,y2\}, \\
   &\min_{i=y1}^{y2-1} \{ split(n-1,x1,y1,x2,i)+split(1,x1,i+1,x2,y2\}, \\
   & \min_{i=y1}^{y2-1} \{ split(1,x1,y1,x2,i)+split(n-1,x1,i+1,x2,y2\} \}
   \end{aligned}
   $$


一些优化

- 计算`split(n,x1,y1,x2,y2)`过程中共有很多重复计算，会造成 `TIME LIMITED EXEED`，所以用一个数组`res[n][x1][y1][x2][y2]`来保存结果
- 为方便计算子棋盘的分数和，用`sum[9][9]`保存从 (1,1) 到 (i,j) 矩形的分数之和

```c++
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int score[9][9];  // 每个格子的分数
int sum[9][9];   // (1,1)到(i,j)的矩形的分数之和
int res[15][9][9][9][9];  // split函数的记录表

// (x1,y1)到(x2,y2)的矩形的分数之和
int calSum(int x1, int y1, int x2, int y2)
{
	return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}

// 将(x1,y1)到(x2,y2)的矩形分割成n份且返回最小平方和
int split(int n, int x1, int y1, int x2, int y2)
{
	int MIN = 10000000;
	if (res[n][x1][y1][x2][y2] != -1)
	{
		return res[n][x1][y1][x2][y2];
	}
	if (n == 1)
	{
		int tmp = calSum(x1, y1, x2, y2);
		res[n][x1][y1][x2][y2] = tmp * tmp;
		return tmp * tmp;
	}

	for (int i = x1; i <= x2 - 1; i++)
	{
		int left = calSum(x1, y1, i, y2);
		int right = calSum(i + 1, y1, x2, y2);
		int tmp = min(split(n - 1, x1, y1, i, y2) + right*right, split(n - 1, i + 1, y1, x2, y2) + left*left);
		if (tmp < MIN)
		{
			MIN = tmp;
		}
	}
	for (int i = y1; i <= y2 - 1; i++)
	{
		int up = calSum(x1, y1, x2, i);
		int down = calSum(x1, i + 1, x2, y2);
		int tmp = min(split(n - 1, x1, y1, x2, i) + down*down, split(n - 1, x1, i + 1, x2, y2) + up*up);
		if (tmp < MIN)
		{
			MIN = tmp;
		}
	}
	res[n][x1][y1][x2][y2] = MIN;
	return MIN;
}

int main()
{
	// 初始化
	memset(sum, 0, sizeof(sum));
	memset(res, -1, sizeof(res));
	int numOfRec = 0;
	cin >> numOfRec;
	for (int i = 1; i <= 8; i++)
	{
		int rowsum = 0;
		for (int j = 1; j <= 8; j++)
		{
			cin >> score[i][j];
			rowsum += score[i][j];
			sum[i][j] += sum[i - 1][j] + rowsum;
		}
	}

	double result = numOfRec*split(numOfRec, 1, 1, 8, 8) - sum[8][8] * sum[8][8];
	cout << fixed << setprecision(3) << sqrt(result/(numOfRec*numOfRec)) << endl;
	return 0;
}
```



## 用栈代替递归

Hanoi tower的递归解法

```c++
#include <iostream>
using namespace std;

void Hanoi(int n, char src,char mid,char dest)
//将src座上的n个盘子，以mid座为中转，移动到dest座
{
	if (n == 1)
	{ 
		//只需移动一个盘子
		cout << src << "->" << dest << endl; //直接将盘子从src移动到dest即可
		return ; //递归终止
	}
	Hanoi(n - 1, src, dest, mid); //先将n-1个盘子从src移动到mid
	cout << src << "->" << dest << endl; //再将一个盘子从src移动到dest
	Hanoi(n-1,mid,src,dest); //最后将n-1个盘子从mid移动到dest
	return;
}

int main()
{
	int n;
	cin >> n;
	Hanoi(n, 'A', 'B', 'C');
	return 0;
}
```

栈解法

```c++
#include <iostream>
#include <stack>
using namespace std;

//一个Problem变量代表一个子问题，将src上的n个盘子，以mid为中介，移动到dest
struct Problem
{
	int n;
	char src, mid, dest;
	Problem(int _n, char s, char m, char d) :n(_n), src(s), mid(m), dest(d) {}
};

stack<Problem> stk;

int main()
{
	int n;
	cin >> n;
	stk.push(Problem(n, 'A', 'B', 'C'));
	while (!stk.empty())
	{
		Problem curPrb = stk.top();
		stk.pop();
		if (curPrb.n == 1)
		{
			cout << curPrb.src << "->" << curPrb.dest << endl;
		}
		else
		{
			// 分解为三个子问题
			stk.push(Problem(curPrb.n - 1, curPrb.mid, curPrb.src, curPrb.dest));
			stk.push(Problem(1, curPrb.src, curPrb.mid, curPrb.dest));
			stk.push(Problem(curPrb.n - 1, curPrb.src, curPrb.dest, curPrb.mid));
		}
	}
	return 0;
}
```

