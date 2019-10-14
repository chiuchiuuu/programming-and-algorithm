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
