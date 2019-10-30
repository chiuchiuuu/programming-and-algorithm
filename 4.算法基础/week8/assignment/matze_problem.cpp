#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

bool is_wall[5][5];
int a[5][5];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct Node
{
    int x;
    int y;
    int s;
    short father[30];
};

bool Judge_Invalid(int x, int y)
{
    if(x<0 || x >=5 || y <0 || y>=5)
        return true;
    if(is_wall[x][y])
        return true;
    if(a[x][y] ==1)
        return true;
    return false;
}
Node Bfs()
{
    queue<Node> q;
    Node cur, next;
    cur.x = 0;
    cur.y = 0;
    cur.s = 0;
    is_wall[cur.x][cur.y] = true;
    q.push(cur);
    while (!(q.empty()))
    {
        cur = q.front();
        q.pop();
        if(cur.x == 4 && cur.y ==4)
            return cur;
        int i, nx, ny;
        for(i=0; i<4; i++)
        {
            nx = cur.x + dx[i];
            ny = cur.y + dy[i];
            if(Judge_Invalid(nx,ny))
                continue;
            next = cur;
            next.x = nx;
            next.y = ny;
            next.s = cur.s + 1;
            next.father[cur.s] = i;
            q.push(next);
        }
    }
    return cur;
}
int main()
{
     int i,j;
    for(i=0;i<5;i++){   //读入迷宫
        for(j=0;j<5;j++){
            scanf("%d",&a[i][j]);
        }
    }
    memset(is_wall,0,sizeof(is_wall));
    Node ans = Bfs();
    int x,y;
    x = 0,y = 0;
    for(i=0;i<=ans.s;i++){
         printf("(%d, %d)\n",x,y);
         x+=dx[ans.l[i]];
         y+=dy[ans.l[i]];
    }        
    return 0;
}