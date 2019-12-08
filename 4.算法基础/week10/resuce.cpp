#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
queue<int> X;
queue<int> Y;
queue<int> D;
queue<int> Sum;
int t, n, m, k, sx, sy, fx, fy, f;
char S[205][205];
int vis[205][205][50];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool check(int x, int y, int l) {
  if (x < 1 || y < 1 || x > n || y > m) {
    return 0;
  }
  if (S[x][y] >= '0' && S[x][y] <= '4') {
    int h = pow(2, S[x][y] - '0');
    if (!vis[x][y][l + h])
      return 1;
  }
  if (S[x][y] == '#' || vis[x][y][l]) {
    return 0;
  }
  return 1;
}
void bfs() {
  while (!X.empty()) {
    int x = X.front(), y = Y.front(), d = D.front(), sum = Sum.front(), num = 0;
    if (d >= 16) {
      num++;
    }
    if (d % 16 >= 8) {
      num++;
    }
    if (d % 8 >= 4) {
      num++;
    }
    if (d % 4 >= 2) {
      num++;
    }
    if (d % 2 >= 1) {
      num++;
    }
    for (int i = 0; i < 4; i++) {
      int xx = x + dir[i][0], yy = y + dir[i][1];
      if (check(xx, yy, d)) {
        if (xx == fx && yy == fy && num >= k) {
          f = 1;
          printf("%d\n", sum + 1);
          return;
        }
        if (S[xx][yy] >= '0' && S[xx][yy] <= '4') {
          int o = pow(2, S[xx][yy] - '0');
          if (d % (o * 2) < o) {
            X.push(xx);
            Y.push(yy);
            D.push(d + pow(2, S[xx][yy] - '0'));
            Sum.push(sum + 1);
            vis[xx][yy][d + 1] = 1;
            continue;
          }
        }
        if (S[xx][yy] == '$') {
          for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
              if ((i != xx || j != yy) && S[i][j] == '$' && vis[i][j][d] == 0) {
                vis[i][j][d] = 1;
                X.push(i);
                Y.push(j);
                D.push(d);
                Sum.push(sum + 1);
              }
            }
          }
        }
        X.push(xx);
        Y.push(yy);
        D.push(d);
        Sum.push(sum + 1);
        vis[xx][yy][d] = 1;
      }
    }
    X.pop();
    Y.pop();
    D.pop();
    Sum.pop();
  }
}
int main() {
  scanf("%d", &t);
  for (; t; t--) {
    scanf("%d %d %d\n", &n, &m, &k);
    while (!X.empty()) {
      X.pop();
      Y.pop();
      Sum.pop();
      D.pop();
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        S[i][j] = getchar();
        if (S[i][j] == 'S') {
          vis[i][j][0] = 1;
          sx = i;
          sy = j;
          X.push(i);   //纵坐标
          Y.push(j);   //横坐标
          D.push(0);   //收集的宝石数据化
          Sum.push(0); //行走的步数
        }
        if (S[i][j] == 'E') {
          fx = i;
          fy = j;
        }
      }
      getchar();
    }
    bfs();
    if (!f) {
      printf("oop!\n");
    }
    memset(vis, 0, sizeof(vis));
    memset(S, 0, sizeof(S));
    f = 0;
  }
}
