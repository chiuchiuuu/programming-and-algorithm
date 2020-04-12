#include<iostream>
#include<queue>
#include<cstdio>
#include<string>
#include<cstdio>
using namespace std;

const int board_size = 5;
const int direction_num = 4;

struct Piece
{
	int x;
	int y;
	//Piece(int xx, int yy): x(xx), y(yy){}
};

Piece father[board_size][board_size];
// father[x][y].x 存储的是最短路径的坐标为(x,y)点的下一个坐标x
 int direction[direction_num][2] = {
	{-1, 0}, {0, 1}, {1, 0}, {0,-1}
};

int marker[board_size][board_size];
int board[board_size][board_size];

bool InBoard(int x, int y)
{
	if (x >= 0 && x < board_size && y >= 0 && y < board_size)
		return true;
	else
		return false;
}

void BFS()
{
	queue<Piece>q;
	Piece start;
	start.x = 4;
	start.y = 4;
	marker[4][4] = 1;
	q.push(start);
	while (!q.empty())
	{
		Piece current = q.front();
		q.pop();
		if (current.x == 0 && current.y == 0)
			return;
		for (int i = 0; i < direction_num; i++)
		{
			int next_x = current.x + direction[i][0];
			int next_y = current.y + direction[i][1];
			if (InBoard(next_x, next_y) && !board[next_x][next_y] && !marker[next_x][next_y])
			{
				Piece next;
				next.x = next_x;
				next.y = next_y;
				father[next_x][next_y].x = current.x;
				father[next_x][next_y].y = current.y;
				marker[next_x][next_y] = 1;
				q.push(next);
				//cout <<"the current:" <<current.x<<" "<< current.y <<"searched: "<<next_x << "  " << next_y << endl;
			}
		}
	}
}
void print_answer()
{
	int x = 0, y = 0;
	while (!((x==board_size-1) && (y == board_size-1)))
	{
		cout << '(' << x << ','<<' '  << y << ')' << endl;
		int temp_x, temp_y;
		temp_x = father[x][y].x;
		temp_y = father[x][y].y;

		x = temp_x;
		y = temp_y;

	}
	cout << '(' << x << ','<<' ' << y << ')' << endl;
}
int main()
{
	//freopen("E:\\text.txt", "r", stdin);
	for (int i = 0; i < board_size; i++)
		for (int j = 0; j < board_size; j++)
			cin >> board[i][j];
	BFS();
	print_answer();
	return 0;
}
