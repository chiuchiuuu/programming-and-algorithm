#include <iostream>
#include <stack>
#include <cstring>
using namespace std;
int R, C; //the number of row/col
int rooms[60][60];
int color[60][60]; //marker whether a room has been searched
int maxRoomArea = 0, roomNum = 0;
int roomArea;
void Dfs(int i, int k)
{
    if (color[i][k])
        return;
    ++roomArea;
    color[i][k] = roomNum;
    if (rooms[i][k] & 1 == 0)
        Dfs(i, k - 1); // go west
    if (rooms[i][k] & 2 == 0)
        Dfs(i - 1, k); //go north
    if (rooms[i][k] & 4 == 0)
        Dfs(i, k + 1);
    if (rooms[i][k] & 8 == 0)
        Dfs(i + 1, k); //go south
}
int main()
{
    cin >> R >> C;
    for (int i = 1; i <= R; ++i)
        for (int k = 1; k <= C; ++k)
            cin >> rooms[i][k];
    memset(color, 0, sizeof(color));
    for (int i = 1; i <= R; ++i)
        for (int k = 1; k <= C; ++k)
        {
            if (!color[i][k])
            {
                ++roomNum;
                roomArea = 0;
                Dfs(i, k);
                maxRoomArea = max(roomArea, maxRoomArea);
            }
        }
    cout << roomNum << endl;
    cout << maxRoomArea << endl;
    return 0;
}
/*
 Input:
 First row: row numbers R
 Second row: col number C
 R rows: The walls sourrding a room
 1 stands for west wall, 2 for north wall
 4 for east wall, 8 for south wall
 the sum stands for one cell
 */

/*
4
7
11 6  11  6  3 10 6
7  9  6  13  5 15 5
1  10 12  7 13 7  5
13 11 10  8 10 12 13
Output:
5
9
 */