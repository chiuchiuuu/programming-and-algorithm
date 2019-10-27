## 引入例题：抓住那头牛
农夫知道一头牛的位置，想要抓住它。农夫和牛都位于数轴上，农夫起始位于点N(0<=N<=100000)，牛位于点K(0<=K<=100000)。农夫有两种移动方式：
1、从X移动到X-1或X+1，每次移动花费一分钟
2、从X移动到2*X，每次移动花费一分钟
 假设牛没有意识到农夫的行动，站在原地不动。农夫最少要花多少时间才能抓住牛？
 ### 场景分析
 假设农夫起始位于3，牛位于5，如何搜索一条到5的路径？
[![Ksx7nS.png](https://s2.ax1x.com/2019/10/27/Ksx7nS.png)](https://imgchr.com/i/Ksx7nS)

#### 策略一：深度优先搜索：

从起点出发，随机挑选一个方向，能往前走就往前走（扩展），走不动了则回溯。

运气好的话： 3->4->5

运气最坏的话： 3->2->1->0->4->5

如果想要求最优解，需要遍历所有走法，但可以使用一定方法进行剪枝。

运算过程中需要存储路径上的节点，数量较少，用栈存储。

#### 策略二：广度优先搜索

给节点分层。起点就是第0层，从起点最少需要N步就能到达的点就属于第n层。

依层次顺序，从小到大的扩展节点。把层次低的点全部扩展出来后，才会扩展层次高得点。

搜索过程：

3

12 4 6

1 5

注意：扩展时，不能扩展已经走过的节点。可确保找到最优解，但是因扩展出 来的节点较多，且多数节点都需要 保存，因此需要的存储空间较大。 用队列存节点。 

## 广搜算法：

 广度优先搜索算法如下：（用QUEUE ）

[![KsxH0g.png](https://s2.ax1x.com/2019/10/27/KsxH0g.png)](https://imgchr.com/i/KsxH0g)

1. 把初始节点S0放入Open表中；
2.  如果Open表为空，则问题无解，失败 退出； 
3. 把Open表的第一个节点取出放入 Closed表，并记该节点为 n ； 
4. 考察节点 n是否为目标节点。若是， 则得到问题的解，成功退出；
5. 若节点 n不可扩展，则转第(2)步； 
6. 扩展节点 n，将其不在Closed表和 Open表中的子节点 (判重）放入Open表的尾部 ，并为每一个子节点设置指向父节点的指针 ( 或记录节点的层次），然后转第(2)步 

代码实现如下：

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int N, K;
const int MAXN = 100000;
int visited[MAXN + 10]; //判重标记，为true表示该点已经扩展过了
struct Step
{
    int x;     //位置
    int steps; //到达x需要的步数
    Step(int xx, int ss) : x(xx), steps(ss) {}
};
queue<Step> q; //队列，即open表
int main()
{
    cin >> N >> K;
    memset(visited, 0, sizeof(visited));
    q.push(Step(N, 0)); //把起始位置放入Open表
    while (!q.empty())
    {
        Step s = q.front(); //拿出Open表中第一个元素
        if (s.x == K)
        { //找到目标
            cout << s.steps << endl;
            return 0;
        }
        else
        {
            if (s.x - 1 >= 0 && !visited[s.x - 1])
            {
                q.push(Step(s.x - 1, s.steps + 1));
                visited[s.x - 1] = 1;
            }
            if (s.x + 1 <= MAXN && !visited[s.x + 1])
            {
                q.push(Step(s.x + 1, s.steps + 1));
                visited[s.x + 1] = 1;
            }
            if (s.x * 2 <= MAXN && !visited[s.x * 2])
            {
                q.push(Step(s.x * 2, s.steps + !));
                visited[s.x * 2] = 1;
            }
            q.pop();
        }
    }
    return 0;
}

```











