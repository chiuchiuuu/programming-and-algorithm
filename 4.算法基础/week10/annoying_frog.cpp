#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <string>
using namespace std;
int r, c, rnum;
int sum;
int n;
int ma[53][53] = {};
int ans = 14;
struct point {
  int x;
  int y;
  bool operator<(const point &a) const {
    if (a.x == x)
      return y < a.y;
    return x < a.x;
  }
  point(){};
} p[702];
struct route {
  point start;
  int dx;
  int dy;
  int step;
  bool operator<(const route &a) const { return step > a.step; };
  route(point a, int b, int c, int d) {
    start = a;
    dx = b;
    dy = c;
    step = d;
  };
  route(){};
} ro[1000001];
bool inside(int x, int y) { return (1 <= x && x <= r && 1 <= y && y <= c); }
int match(point start, int dx, int dy) {
  if (inside(start.x - dx, start.y - dy))
    return 0;
  int k;
  for (k = 0;; k++) {
    if (inside(start.x + k * dx, start.y + k * dy)) {
      if (ma[start.x + k * dx][start.y + k * dy] == 0) {
        return 0;
      }
    } else
      break;
  }
  if (k > 2)
    return k;
  return 0;
}
void dfs(int code, int s, int num) {
  if (sum == s) {
    ans = min(ans, num);
    return;
  }
  for (int i = code; i < rnum; ++i) {
    if (num + (sum - s) / ro[i].step >= ans)
      return;
    if (match(ro[i].start, ro[i].dx, ro[i].dy) == 0)
      continue;
    for (int x = ro[i].start.x, y = ro[i].start.y;
         1 <= x && x <= r && y >= 1 && y <= c; x += ro[i].dx, y += ro[i].dy)
      --ma[x][y];
    dfs(i, s + ro[i].step, num + 1);
    for (int x = ro[i].start.x, y = ro[i].start.y;
         1 <= x && x <= r && y >= 1 && y <= c; x += ro[i].dx, y += ro[i].dy)
      ++ma[x][y];
  }
  return;
}
int main() {
  int t;
  cin >> t;
  while (t--) {
    rnum = 0;
    ans = 14;
    cin >> r >> c;
    cin >> n;
    sum = 0;
    for (int i = 0; i < n; ++i) {
      cin >> p[i].x >> p[i].y;
      int l;
      cin >> l;
      sum += l;
      ma[p[i].x][p[i].y] = l;
    }
    sort(p, p + n);
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int st = match(p[i], p[j].x - p[i].x, p[j].y - p[i].y);
        if (st != 0) {
          ro[rnum++] = route(p[i], p[j].x - p[i].x, p[j].y - p[i].y, st);
        }
      }
    }
    sort(ro, ro + rnum);
    dfs(0, 0, 0);
    cout << ans << endl;
  }
}
