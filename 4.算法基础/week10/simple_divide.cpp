#include<iostream>
#include<cstring>
using namespace std;
 
const int NMAX = 55;
int dp[NMAX][NMAX] = {};
 
int main()
{
	int n,i,j,k,ans=0;
	while (cin >> n)
	{
		for (i=0; i<NMAX; i++)
		{
			memset(dp[i], 0, sizeof(dp[i]));
		}
		ans = 0;
		dp[1][1] = 1;
		if (n==1)
		{
			cout << 1 << endl;
			continue;
		}
		for (i=2; i<=n; i++)
		{
			for (j=1; j<i; j++)
			{
				for (k=1; k<=j; k++)
				{
					dp[i][j] += dp[i-j][k];
				}
			}
			dp[i][i] = 1;
		}
		for (i=1; i<=n; i++)
		{
			ans += dp[n][i];
		}
		cout << ans << endl;
	}
	return 0;
}
