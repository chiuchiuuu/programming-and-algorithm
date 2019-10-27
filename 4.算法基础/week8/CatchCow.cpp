/*
//农夫知道一头牛的位置，想要抓住它。农夫和牛都位于数轴上，农夫起始位于点N(0<=N<=100000)，牛位于点K(0<=K<=100000)
农夫有两种移动方式：
1、从X移动到X-1或X+1，每次移动花费一分钟
2、从X移动到2*X，每次移动花费一分钟
 假设牛没有意识到农夫的行动，站在原地不动。农夫最少要花多少时间才能抓住牛？
*/
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
