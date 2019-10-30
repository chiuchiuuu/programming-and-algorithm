#include<iostream>
#include<queue>
using namespace std;

const int board_size = 4;
const int direction_num = 4;
struct Piece
{
    int status;//状态值
    int steps; //步数
    Piece(int st, int step):status(st),steps(step){}
};
int direction[direction_num][2] = {
    {-1,0}, {0,1},{1,0},{0,-1}
};
int pos[board_size *board_size]; //16种反转可能性
bool marker[1<<(board_size*board_size)];

bool inBoard(int x, int y)
{
    if(x>=0 && x<board_size && y>=0 && y<board_size)
        return true;
    else
        return false;
}
void FlipInitialize()
{
    for (int i = 0; i < board_size; i++)
    {
        for(int j = 0; j< board_size; j++)
        {
            // i*size+j  即为编号
            int value = 1 << (i * board_size + j);
            for(int k = 0; k<direction_num; k++)
            {
                int next_x = i + direction[k][0];
                int next_y = j + direction[k][1];
                if(inBoard(next_x, next_y))
                    value += 1 << (next_x *board_size + next_y);
            }
            pos[i * board_size + j] = value;
        }
    }
    
}
int BFS(int value)
{
    queue<Piece> q;
    Piece s = {value, 0};
    q.push(s);
    marker[s.status] = true;
    while (!q.empty())
    {
        Piece cur = q.front();
        q.pop();
        //盘面全黑或者全白(2^16 -1)时结束，并返回步数
        if(cur.status == 0 || cur.status == (1<<(board_size*board_size))-1)
        {
            return cur.steps;
        }
        //搜索16个位置
        for(int i = 0; i< board_size*board_size; ++i)
        {
            //通过异或运算得到翻转后的状态
            Piece next = {cur.status ^ pos[i], cur.steps+1};
            if(!marker[next.status])
            {
                q.push(next);
                marker[next.status] = true;
            }

        }
    }
    return -1; //无法到达目标状态 返回-1
}
int main()
{
    FlipInitialize();
    char str[5];
    int value = 0;
    for(int i=0; i<board_size; i++)
    {
         cin>>str;
         for(int j=0; j<board_size; j++)
         {
             if(str[j]== 'w')
                value += 1<<(i*board_size + j);
                  // 加上 1<<(编号) 即可将此位置设置为1
         }
    }
    int ans = BFS(value);
    if(ans >= 0)
        cout<<ans<<endl;
    else
    {
        cout<<"impossible"<<endl;
    }
    return 0;
}