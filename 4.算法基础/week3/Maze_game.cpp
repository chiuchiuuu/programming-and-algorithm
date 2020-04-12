#include<iostream>
#include<memory.h>
#define MAXIN 75
char board[MAXIN + 2][MAXIN + 2];//define the board
int minstep, width, height;
int to[4][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };
//define the step motion
bool mark[MAXIN + 2][MAXIN + 2];//set the mark to check whether this board has been explored
using namespace std;

void Search(int now_x, int now_y, int end_x, int end_y, int step, int f) {
	//now_x, now_y: the current position
	//end_x, end_y: the end position
	//step: counter for how many steps have been used
	//f: the direction from last step to (now_x, now_y)
	if (step > minstep)
		return;
	if (now_x == end_x && now_y == end_y) {
		// arrive the end point
		if (minstep > step) {
			minstep = step;
		}
		return;
	}
	for (int i = 0; i < 4; i++) {
		int x = now_x + to[i][0];
		int y = now_y + to[i][1];
		bool position_inside_board = (x > -1) && (x < width + 2) && (y > -1) && (y < height + 2);
		bool step_noCard_noMark = (board[y][x] == ' ') && (mark[y][x] == false);
		bool step_to_end = (y == end_y) && (x == end_x) && (board[y][x] == 'X');
		if (position_inside_board && (step_noCard_noMark || step_to_end)) {
			mark[y][x] = true;
			//if the new position is suitable, then mark it as True
			if (f == i)
				Search(x, y, end_x, end_y, step, i);
			else
				Search(x, y, end_x, end_y, step + 1, i);
			// if all the directions from this step are turn out to be unsuitable
			mark[y][x] = false;
		}
	}
}
int main() {
	int Boardnum = 0;
	while (cin >> width >> height) {
		if (!height && !width) {
			break;
		}
		Boardnum++;
		for (int i = 0; i < height + 2; i++) {
			board[i][0] = ' ';
			board[i][width + 1] = ' ';
		}
		for (int i = 0; i < width + 2; i++) {
			board[0][i] = ' ';
			board[height + 1][i] = ' ';
		}
		for (int i = 1; i <= height; i++) {
			cin.get();
			for (int j = 1; j <= width; j++) {
				board[i][j] = cin.get();
			}
		}
		int x, y, end_x, end_y;
		int pair = 0;
		while (cin >> x >> y >> end_x >> end_y)
		{
			pair++;
			minstep = 100000;
			memset(mark, false, sizeof(mark));
			if (x && y && end_x && end_y)
			{
				Search(x, y, end_x, end_y, 0, -1);//at first, the direction flag do not set
				cout << "Pair " << pair << ": ";
				if (minstep == 100000)
				{
					cout << "impossible." << endl;
				}
				else
				{
					cout << minstep << " segments." << endl;
				}
			}
			else
			{
				break;
			}
		}
		cout << endl;

	}

}