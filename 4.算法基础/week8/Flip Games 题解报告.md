# Flip Games 题解报告

## 问题描述：

具体问题描述就不在此展开，有兴趣的朋友可以参看下面的链接：http://cxsjsxmooc.openjudge.cn/test2/G/ 。简单来说就是给定一个棋盘的状态量（黑白相间），每次点击一个棋子，会把其及周围的棋子改变颜色，问最少需要点击几次棋子才能达到纯黑或者纯白的状态。

![KLZKoj.png](https://s2.ax1x.com/2019/11/02/KLZKoj.png)

## 问题分析

由于题目中问的是最优解，我们很容易想到使用广度优先搜索的方法来获得答案，关于BFS算法的初步介绍请参考我的上一篇博客。 https://blog.csdn.net/qq_27848347/article/details/102874472 

### 状态表达

BFS算法背后的思想并不复杂，就是用队列来模拟分层搜索的过程，但在搜索时，我们需要对当前的状态加一标记，以避免重复搜索。那么如何在保证有较快的搜素速度的前提下，以较小的空间存储状态(节点)数目巨大的状态？显然简单粗暴的使用一个字符串实在是浪费空间。作者在这里使用了一个16位的2进制数来表达当前棋盘的状态量，一是比较直观，二则方便后面的翻转操作。

以上图为例，其状态量可直接表达为：

```cpp
0 1 0 1
1 1 1 1
0 0 1 0
0 1 1 0
```

在计算机存储为：

```cpp
010111100100110
```

显然一个int变量就足以满足我们需求，大大节省了相对于字符串的空间开支。

### 翻转操作

按照题目要求，每点击一个棋子，会将其及其周围的棋子的颜色发生改变，如果按照常规思路，需要对当前棋盘的棋子进行遍历，然后逐个进行翻转操作，时间复杂度较高。考虑到上文中，我们将每个棋子的状态用一个bit的0-1表达，使用位运算是一个很直接的考虑。

考虑到与或运算的性质：

- 0 与或 任何数，任何数不发生变化：对应于棋盘棋子在效果范围外，不受影响
- 1 与或 任何数，任何数取反：对应于棋子在效果范围内，状态取反

我们很自然的想到将当前棋盘状态与一个操作对应的数值进行与或操作，达到翻转的效果。

以点击棋盘右下角为例，其二进制表达可以写为：

```cpp
0 0 0 0
0 0 0 0
0 0 0 1
0 0 1 1
```

将其与状态表达进行与或的位运算，可以很方便的改变棋盘的当前状态。

### 源代码

其他就没有什么注意事项，直接看代码就好。

```cpp
#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;

const int board_size = 4;
const int direction_num = 4;
struct Piece
{
    int status; //状态值
    int steps;  //步数
    Piece(int st, int step) : status(st), steps(step) {}
};
int direction[direction_num][2] = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int pos[board_size * board_size];            //16种点击反转可能性
bool marker[1 << (board_size * board_size)]; //2^16次方摆放状态

bool inBoard(int x, int y)
{
    if (x >= 0 && x < board_size && y >= 0 && y < board_size)
        return true;
    else
        return false;
}
void FlipInitialize()
{
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            // i*size+j  即为编号
            int value = 1 << (i * board_size + j);
            for (int k = 0; k < direction_num; k++)
            {
                int next_x = i + direction[k][0];
                int next_y = j + direction[k][1];
                if (inBoard(next_x, next_y))
                    value += 1 << (next_x * board_size + next_y);
            }
            pos[i * board_size + j] = value;
        }
    }
}
int BFS(int value)
{
    queue<Piece> q;
    Piece s = Piece(value, 0);
    q.push(s);
    marker[s.status] = true;
    while (!q.empty())
    {
        Piece cur = q.front();
        q.pop();
        //盘面全黑或者全白(2^16 -1)时结束，并返回步数
        if (cur.status == 0 || cur.status == (1 << (board_size * board_size)) - 1) //注意加减运算符比位运算符等级高！！
        {
            return cur.steps;
        }
        //搜索16个位置
        for (int i = 0; i < board_size * board_size; ++i)
        {
            //通过异或运算得到翻转后的状态
            Piece next = Piece(cur.status ^ pos[i], cur.steps + 1);
            if (!marker[next.status])
            {
                q.push(next);
                marker[next.status] = true;
            }
        }
    }
    return -1; //无法到达目标状态 返回-1
}
int main()
{
    freopen("E:\\text.txt", "r", stdin);
    FlipInitialize();
    char str[5];
    int value = 0;
    for (int i = 0; i < board_size; i++)
    {
        cin >> str;
        for (int j = 0; j < board_size; j++)
        {
            if (str[j] == 'w')
                value += 1 << (i * board_size + j);
            // 加上 1<<(编号) 即可将此位置设置为1
        }
    }
    int ans = BFS(value);
    if (ans >= 0)
        cout << ans << endl;
    else
    {
        cout << "Impossible" << endl;
    }
    return 0;
}
```

