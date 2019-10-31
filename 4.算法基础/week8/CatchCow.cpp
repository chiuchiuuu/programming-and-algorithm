#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int N, K; //农民位置 和 牛的位置
const int MAXN = 10000;
int visited[MAXN + 10]; //判重标记
struct Step
{
    int x;     //当前位置
    int steps; //到达x所需要的步数
    Step(int xx, int ss) : x(xx), steps(ss) {}
};
queue<Step> open_table; //队列，即open表
int main()
{
    cin >> N >> K;
    memset(visited, 0, sizeof(visited));
    open_table.push(Step(N, 0));
    visited[N] = 1;
    while (!open_table.empty())
    {
        Step s = open_table.front();
        if (s.x == K)
        {
            //找到目标
            cout << s.steps << endl;
            return 0;
        }
        else
        {
            if (s.x - 1 >= 0 && !visited[s.x - 1])
            {
                //向左走一步
                open_table.push(Step(s.x - 1, s.steps + 1));
                visited[s.x - 1] = 1;
            }
            if (s.x + 1 <= MAXN && !visited[s.x + 1])
            {
                open_table.push(Step(s.x + 1, s.steps + 1));
                visited[s.x + 1] = 1;
            }
            if (s.x * 2 <= MAXN && !visited[s.x * 2])
            {
                open_table.push(Step(s.x * 2, s.steps + 1));
                visited[s.x * 2];
            }
            open_table.pop(); //z依据当前点搜索完后，弹出
        }
    }
    return 0;
}