#include <cstring>
#include <iostream>
using namespace std;
#define N 51
int dp1[N][N]; // N划分成K个正整数之和的划分数目。
int dp2[N][N]; // N划分成若干个不同正整数之和的划分数目。
int dp3[N][N]; // N划分成若干个可相同的正整数之和的划分数目。
int f[N][N];   // N划分成K个奇正整数之和的划分数目。
int g[N][N];   // N划分成K个偶正整数之和的划分数目。

void initDivideInt() {
  memset(dp1, 0, sizeof(dp1)); // dp[n][k]=dp[n-k][k]+dp[n-1][k-1]
  memset(dp2, 0, sizeof(dp2)); // dp[n][m]=dp[n][m-1]+dp[n-m][m-1]
  memset(dp3, 0, sizeof(dp3)); // dp[n][m]=dp[n][m-1]+dp[n-m][m]

  for (int i = 1; i < N; i++) {
    for (int j = 1; j < N; j++) {
      if (i < j) {
        dp1[i][j] = 0;
        dp2[i][j] = dp2[i][i];
        dp3[i][j] = dp3[i][i];
      } else if (i == j) {
        dp1[i][j] = 1;
        dp2[i][j] = dp2[i][j - 1] + 1;
        dp3[i][j] = dp3[i][j - 1] + 1;
      } else {
        dp1[i][j] = dp1[i - j][j] + dp1[i - 1][j - 1];
        dp2[i][j] = dp2[i][j - 1] + dp2[i - j][j - 1];
        dp3[i][j] = dp3[i][j - 1] + dp3[i - j][j];
      }
    }
  }
}

// f[i][j]=f[i-1][j-1]+g[i-j][j]
void initDivideOdd() {
  f[0][0] = 1;
  g[0][0] = 1;
  for (int i = 1; i < N; i++) {
    for (int j = 1; j <= i; j++) {
      g[i][j] = f[i - j][j];
      f[i][j] = f[i - 1][j - 1] + g[i - j][j];
    }
  }
}

int main() {
  //  freopen("in.txt", "r", stdin);
  int n, k;
  initDivideInt();
  initDivideOdd();
  while (cin >> n >> k) {
    cout << dp1[n][k] << endl;
    cout << dp2[n][n] << endl;

    int sum = 0;
    for (int i = 0; i <= n; i++) {
      sum += f[n][i];
    }
    cout << sum << endl;
  }
  return 0;
}
