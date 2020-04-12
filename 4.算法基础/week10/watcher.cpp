#define LL 0
#define LV 1
#define VL 2
#define VV 3
#define MAX_N 22

#include <memory.h>
#include <stdio.h>

int n, k;
int num[4], target; // L:0,V:1
long long int dp[4][MAX_N * 2][MAX_N * 2][MAX_N][MAX_N], ans;

void initialize() {
  dp[0][2][1][1][1] = 1;
  dp[1][1][2][1][1] = 1;
  dp[2][1][1][2][1] = 1;
  dp[3][1][1][1][2] = 1;
  for (int ll = 1; ll < MAX_N * 2; ll++)
    for (int lv = 1; lv < MAX_N; lv++)
      for (int vl = 1; vl < MAX_N; vl++)
        for (int vv = 1; vv < MAX_N; vv++)
          if (ll + lv + vl + vv > 5) {
            dp[LL][ll][lv][vl][vv] =
                dp[LV][ll][lv][vl - 1][vv] + dp[LL][ll - 1][lv][vl][vv];
            dp[LV][ll][lv][vl][vv] =
                dp[LV][ll][lv][vl][vv - 1] + dp[LL][ll][lv - 1][vl][vv];
            dp[VL][ll][lv][vl][vv] =
                dp[VV][ll][lv][vl - 1][vv] + dp[VL][ll - 1][lv][vl][vv];
            dp[VV][ll][lv][vl][vv] =
                dp[VV][ll][lv][vl][vv - 1] + dp[VL][ll][lv - 1][vl][vv];
          }
  return;
}

inline int code(char ch1, char ch2) {
  return ((ch1 == 'V') << 1) + (ch2 == 'V');
}

int main() {
  // freopen("input.txt","r",stdin);
  char ch1, ch2;
  int j, nt[4];
  initialize();
  while (scanf("%d %d\n", &n, &k) == 2) {
    ans = 0;
    memset(num, 0, sizeof(num));
    scanf("%c%c\n", &ch1, &ch2);
    target = code(ch2, ch1);
    for (int i = 1; i <= n; i++) {
      scanf("%c%c\n", &ch1, &ch2);
      num[code(ch1, ch2)]++;
    }
    j = 0;
    for (int i = LL; i <= VV; i++)
      if (num[i] > num[j])
        j = i;
    j = (j & 2) + ((j & 2) >> 1);
    for (int i = 0; i < 4; i++)
      nt[i] = num[i];
    for (int i = 0; i < 4; i++)
      num[i] = nt[i ^ j];
    target ^= j;
    // printf("%d %d %d %d:%d",num[0],num[1],num[2],num[3],target);
    for (int ll = 0; ll <= num[LL]; ll++)
      for (int lv = 0; lv <= num[LV] && ll + lv <= k; lv++)
        for (int vl = 0; vl <= num[VL] && ll + lv + vl <= k; vl++)
          if (k - ll - lv - vl <= num[VV])
            ans += dp[target][ll + 1][lv + 1][vl + 1][k - ll - lv - vl + 1];
    if (ans)
      printf("YES\n%lld\n", ans);
    else
      printf("NO\n");
  }
  return 0;
}
