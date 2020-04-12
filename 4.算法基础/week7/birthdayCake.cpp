#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;
int N, M;
int minArea = 1 << 30;
int area = 0; //正在搭建中的蛋糕的表面积
int minV[30]; //minV[n]表示n层蛋糕最少的体积
int minA[30]; //minA[n]表示n层蛋糕的最少侧面积
int MaxVforNRH(int n, int r, int h)
{ //求在n层蛋糕，底层最大半径r，最高高度h的情况下，能凑出来的最大体积
    int v = 0;
    for (int i = 0; i < n; i++)
    {
        v += (r - i) * (r - i) * (h - i);
    }

    return v;
}
void Dfs(int v, int n, int max_r, int max_h)
{
    //要用n层去凑体积v，最底层半径不能超过r 高度不能超过h
    //求出最小表面积放入minArea
    if (n == 0)
    {
        if (v)
            return;
        else
        {
            minArea = min(minArea, area);
            return;
        }
    }
    if (v <= 0)
        return;
    if (minV[n] > v) //剪枝3： 还没搭建的体积，一定会超过还缺的体积
        return;
    if (area + minA[n] >= minArea) //剪枝1
        return;
    if (max_h < n || max_r < n) //剪枝2
    // 搭建过程中预见到再往上搭建，高度或者半径已经无法安排
        return;
    if (MaxVforNRH(n, max_r, max_h) < v)//剪枝4： 还没搭建的体积，最大也到不了还缺的体积
        return;
    for (int rr = max_r; rr >= n; --rr)
    {
        if (n == M)
            area = rr * rr; //底面积
        for (int hh = max_h; hh >= n; --hh)
        //从大到小比较快。从大的开始，内部的循环可选择范围就较少，符合先做步骤少的思路
        {
            area += 2 * rr * hh;
            Dfs(v - rr * rr * hh, n - 1, rr - 1, hh - 1);
            area -= 2 * rr * hh;
        }
    }
}
int main()
{
    cin >> M >> N;
    // M 层蛋糕 体积为N
    minV[0] = 0;
    minA[0] = 0;
    for (int i = 0; i <= M; i++)
    {
        minV[i] = minV[i - 1] + i * i * i;
        minA[i] = minA[i - 1] + 2 * i * i;
        //第i层半径最少为i 高度至少为i
    }
    if (minV[M] < N)
        cout << 0 << endl;
    else
    {
        int maxH = (N - minV[M - 1]) / (M * M) + 1; //底部最大高度
        //最底层体积不超过 (N-minV[M-1])，且半径最少为M
        int maxR = sqrt(double(N - minV[M - 1]) / M) + 1;
        //底层高度最少为M
        area = 0;
        minArea = 1 << 30;
        Dfs(N, M, maxR, maxH);
        if (minArea == 1 << 30)
            cout << 0 << endl;
        else
            cout << minArea << endl;
    }

    return 0;
}