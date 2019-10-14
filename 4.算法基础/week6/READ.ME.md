## 深度优先搜索

将问题的各状态之间的转移关系描述为一个图，则深度优先搜索遍历整个图的框架为：

```cpp
Dfs(v)
{
    if(v访问过)
        return;
    将v标记为访问过;
    对和v相邻的每个点u：Dfs(u);
}
```

### 引入例题：城堡问题

如图是一个城堡的地形图。请编写一个程序，计算城堡一共有多少房间，最大的房间有多大。

![1571043425068](READ.ME.assets/1571043425068.png)

![1571043450400](READ.ME.assets/1571043450400.png)

#### 解题思路：

 对每一个 方块，深度优先搜索，从而给这个方 块能够到达的所有位置染色。最后统计一共用 了几种颜色，以及每种颜色的数量。 



```cpp
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;
int R, C; //the number of row/col
int rooms[60][60];
int color[60][60]; //marker whether a room has been searched
int maxRoomArea = 0, roomNum = 0;
int roomArea;
void Dfs(int i, int k)
{
    if (color[i][k])
        return;
    ++roomArea;
    color[i][k] = roomNum;
    if (rooms[i][k] & 1 == 0)
        Dfs(i, k - 1); // go west
    if (rooms[i][k] & 2 == 0)
        Dfs(i - 1, k); //go north
    if (rooms[i][k] & 4 == 0)
        Dfs(i, k + 1);
    if (rooms[i][k] & 8 == 0)
        Dfs(i + 1, k); //go south
}
int main()
{
    cin >> R >> C;
    for (int i = 1; i <= R; ++i)
        for (int k = 1; k <= C; ++k)
            cin >> rooms[i][k];
    memset(color, 0, sizeof(color));
    for (int i = 1; i <= R; ++i)
        for (int k = 1; k <= C; ++k)
        {
            if (!color[i][k])
            {
                ++roomNum;
                roomArea = 0;
                Dfs(i, k);
                maxRoomArea = max(roomArea, maxRoomArea);
            }
        }
    cout << roomNum << endl;
    cout << maxRoomArea << endl;
    return 0;
}
/*
 Input:
 First row: row numbers R
 Second row: col number C
 R rows: The walls sourrding a room
 1 stands for west wall, 2 for north wall
 4 for east wall, 8 for south wall
 the sum stands for one cell
 */

/*
4
7
11 6  11  6  3 10 6
7  9  6  13  5 15 5
1  10 12  7 13 7  5
13 11 10  8 10 12 13
Output:
5
9
 */
```

### 例题二：寻路问题

 N个城市，编号1到N。城市间有R条单向道路。 每条道路连接两个城市，有长度和过路费两个属性。 Bob只有K块钱，他想从城市1走到城市N。问最短共需要走多长的路。如果到不了N，输 出-1 。

#### 解题思路

从城市1开始深度优先遍历整个图，找到所有能到达N的走法，并选择一个最优的。

优化：

1. 如果当前已经找到的最优路径长度为L ,那么在继续搜索的过程中，总长度已经大 于L的走法，就可以直接放弃，不用走到底了 
2.  用$midL[ k][m]$ 表示：走到城市k时总过路费为m的条件下，最优路径的长度。若在 后续的搜索中，再次走到k时，如果总路费恰好为m，且此时的路径长度已经超过$ midL[k][m]$,则不必再走下去了。 

```cpp
/*
N citys, R one-way road between each two citys
Every Road connects two citys, and has property of length and cost
Bob has money K, and wants to travel from 1 to City N
Search: the minimum path length
2<=N<=100
0<=K<=10000
1<=R<=10000

Input:
K
N
R
s1 e1 L1 T1
s2 e2 L2 T2
...
sR eR LE TR
*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int K, N, R, S, D, L, T;
struct Road
{
    int d, L, t;
};
vector<vector<Road>> cityMap(110); //Construct an Adjacency List
//cityMap[i] represents the city set that connected to point i with a road
int minLen = 1 << 30; // bit shift to get a big number
int totalLen;         // the current path length
int totalCost;
int visited[110];     // Marker that a city is looped
int minL[110][10100]; //minL[i][j]: from 1 to point i, the minimum path length with cost of j
void Dfs(int s)       //start from s to N
{
    if (s == N)
    {
        minLen = min(minLen, totalLen);
        return;
    }
    for (int i = 0; i < cityMap[s].size(); i++)
    {
        int d = cityMap[s][i].d;
        // exists one road connecting s and d
        if (!visited[d])
        {
            int cost = totalCost + cityMap[s][i].t;
            if (cost > K)
                continue; //the cost is beyond the afford
            if (totalLen + cityMap[s][i].L >= minLen || totalLen + cityMap[s][i].L >= minL[d][cost])
                continue;
            // the length is already not optimum
            totalLen += cityMap[s][i].L;
            totalCost += cityMap[s][i].t;
            minL[d][cost] = totalLen;
            visited[d] = 1;
            Dfs(d);
            visited[d] = 0;
            totalCost -= cityMap[s][i].t;
            totalLen -= cityMap[s][i].L;
        }
    }
}
int main()
{
    cin >> K >> N >> R;
    for (int i = 0; i < R; i++)
    {
        int s;
        Road r;
        cin >> s >> r.d >> r.L >> r.t;
        if (s != r.d)
            cityMap[s].push_back(r);
    }
    for (int i = 0; i < 110; i++)
        for (int j = 0; j < 10100; j++)
            minL[i][j] 1 << 30;
    memset(visited, 0, sizeof(visited));
    totalLen = 0;
    totalLen = 0;
    visited[1] = 1;
    minLen = 1 << 30;
    Dfs(1);
    if (minLen < (1 << 30))
        cout << minLen << endl;
    else
    {
        cout << "-1" << endl;
    }
    return 0;
}
```

### 深搜与剪枝

具体的例题不放在这里了，请参考：

 http://www.voidcn.com/article/p-oxclnehu-qh.html 

仅仅放上从这道题应该学到的经验：

1. 要选择简合适的搜索顺序，如果一个人物分成多步，要优先尝试可能性少的。 （优先尝试长的木棒）

2. 要发现表面上的不同，实质上等效的重复状态，避免重复。

3. 根据实际问题，发现剪枝方案。