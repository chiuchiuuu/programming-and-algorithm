#include <iostream>
#include <vector>
#include <map>
using namespace std;

unsigned int dp[250][250];

class Solution
{
public:
    unsigned int fun(int n)
    {
        //初始化数据, 边界条件
        for (int num = 0; num < 250; num++)
        {
            for (int k = 0; k < 250; k++)
            {
                if (num == 0)
                {
                    dp[num][k] = 1;
                }
                else if (k > num)
                {
                    dp[num][k] = 0;
                }
                else
                {
                    dp[num][k] = 1;
                }
            }
        }
        //动态规划
        for (int num = 2; num <= n; num++)
        {
            for (int k = num / 2; k >= 1; k--)
            {
                dp[num][k] = dp[num - 2 * k][k] + dp[num][k + 1];
            }
        }
        return dp[n][1];
    }
};

int main()
{
    Solution sol;
    int n;
    cin >> n;
    while (n != 0)
    {
        cout << n << ' ' << sol.fun(n) << endl;
        cin >> n;
    }
    return 0;
}