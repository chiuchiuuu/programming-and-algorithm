#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
using namespace std;

multimap<int, int> Map;
multimap<int, int>::iterator mi;
multiset<int> Set;
multiset<int>::iterator si;
int mark[1035][1035] = {0}; //标记垃圾的位置及数量
int bomb[1035][1035] = {0}; //标记炸弹在此处可清理多少垃圾

int main() {
  int caseN;
  cin >> caseN;
  while (caseN) {
    --caseN;

    memset(mark, 0, sizeof(mark));
    memset(bomb, 0, sizeof(bomb));
    Map.clear();
    Set.clear();

    int d, n;
    cin >> d >> n;
    int x, y, num;
    for (int i = 0; i < n; ++i) {
      cin >> x >> y >> num;
      mark[x][y] = num;
      Map.insert(map<int, int>::value_type(x, y)); //把点放进去
    }

    int tempsum = 0, sum = 0;
    for (mi = Map.begin(); mi != Map.end(); ++mi) {
      int xstart = max(mi->first - d, 0), xend = min(mi->first + d, 1024),
          ystart = max(mi->second - d, 0), yend = min(mi->second + d, 1024);
      while (1) {
        if (ystart > yend) {
          ++xstart;
          ystart = max(mi->second - d, 0);
          if (xstart > xend) {
            break;
          }
        }
        if (bomb[xstart][ystart] > 0) {
          ++ystart;
          continue;
        }
        int bombxs = max(xstart - d, 0), bombxe = min(xstart + d, 1024),
            bombys = max(ystart - d, 0), bombye = min(ystart + d, 1024);
        for (int i = bombxs; i <= bombxe; ++i) {
          for (int j = bombys; j <= bombye; ++j) {
            bomb[xstart][ystart] += mark[i][j];
          }
        }
        if (bomb[xstart][ystart] >= sum) {
          sum = bomb[xstart][ystart];
          Set.insert(sum); //放入目前最大的能够被清理的垃圾数量
        }
        ++ystart;
      }
    }
    si = Set.end();
    --si;
    int count = Set.count(*si);
    cout << count << " " << *si << endl;
  }

  return 0;
}
