#include <iostream>
using namespace std;
int l, r, c, k, i, j, m, T; // T组数据
char map[201][201];
int num,
    que[40001]
       [3]; //队列，que[i][2]记录走的第几步,que[i][0],记录走过的点横坐标x，que[i][1]纵坐标
int soux, souy, desx, desy, head, tail; //记录出发点、目标点的层数，坐标，
int dx[4] = {-1, 0, 1, 0},
    dy[4] = {0, 1, 0, -1}; //坐标按上、右、下、左四个方向变化
bool ff = false;
int main() {
  cin >> T;
  while (T > 0) // T组数据
  {
    ff = false; //对每 组数据，初始化为无法找到奶酪
    cin >> r >> c;
    for (i = 1; i <= r; i++)
      for (j = 1; j <= c; j++) {
        cin >> map[i][j];
        if (map[i][j] == 'S') {
          soux = i;
          souy = j;
          map[i][j] = '#';
        }
        if (map[i][j] == 'E') {
          desx = i;
          desy = j;
        }
      }
    head = 0;
    tail = 1;
    //将起始点入队
    que[1][0] = soux;
    que[1][1] = souy;
    que[1][2] = 0; //步数初始化为0

    while (head < tail) {
      head++;
      int l1, x1, y1;
      for (i = 0; i < 4; i++) {
        x1 = que[head][0] + dx[i];
        y1 = que[head][1] + dy[i];
        if (1 <= x1 && x1 <= r && 1 <= y1 && y1 <= c) //坐标不超出边界
          if (map[x1][y1] == 'E')                     //找到了终点，输出
          {
            tail++;
            que[tail][0] = x1;
            que[tail][1] = y1;
            que[tail][2] = que[head][2] + 1; //步数加1
            cout << que[tail][2] << endl;
            head = tail + 1;
            ff = true;
            break;
          } else if (map[x1][y1] == '.') //找到了可以走的点，入队
          {
            tail++;
            que[tail][0] = x1;
            que[tail][1] = y1;
            que[tail][2] = que[head][2] + 1; //步数加1
            map[x1][y1] = '#'; //走过的点变为不可通行的点
          }
      }
    }
    if (!ff)
      cout << "oop!" << endl;
    T--;
  }
  return 0;
}
