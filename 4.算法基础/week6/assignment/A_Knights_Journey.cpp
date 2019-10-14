#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int path[88][2], book[88][88], p, q;
bool flag;
int dx[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
int dy[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };

void DFS(int r, int c, int step)
{
	path[step][0] = r;
	path[step][1] = c;
	if (step == p * q)
	{
		flag = true;
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		int nx = r + dx[i];
		int ny = c + dy[i];
		if (nx >= 1 && ny >= 1 && nx <= p && ny <= q && !book[nx][ny] && !flag)
		{
			book[nx][ny] = 1;
			DFS(nx, ny, step + 1);
			book[nx][ny] = 0;
		}
	}
}
int main()
{
	//freopen("in.txt", "r", stdin);
	int case_number, cas_ = 0;
	cin >> case_number;
	while (case_number--)
	{
		flag = 0;
		cin >> p >> q;
		memset(book, 0, sizeof(book));
		book[1][1] = 1; //start from (1,1);
		DFS(1, 1, 1);
		cout << "Scenario #" << ++cas_ <<":" <<endl;
		if (flag)
		{
			for (int i = 1; i <= p * q; i++)
			{
				char chara = path[i][1] - 1 + 'A';
				cout << chara << path[i][0];
			}
			cout<<endl;
		}
		else
		{
			cout << "impossible" << endl;
		}
		if(case_number>0)
		    cout<<endl;
	}
	return 0;
}