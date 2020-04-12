
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 12880;
int v[maxn];
int w[maxn];
int dp[maxn];
int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        for (int i = 0; i < n; i++)
            cin >> w[i] >> v[i];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++)
        {
            for (int j = m; j >= w[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
            }
        }
        cout << dp[m] << endl;
    }
    return 0;
}
