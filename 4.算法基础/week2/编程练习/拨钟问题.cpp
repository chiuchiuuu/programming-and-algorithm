#include <iostream>
#include <numeric>
using namespace std;

/*
A: 1 2 4
B: 1 2 3 5 
C: 2 3 6
D: 1 4 5 7
E: 1 3 5 7 9
F: 3 5 6 9 *
G: 4 7 8
H: 5 7 8 9 *
I: 6 8 9 *
*/

int Clock[10] = { 0 };
int tic[10] = { 0 };
int minStep = 1000000;
int minTic[10] = { 0 };

// 根据 tic[1] tic[2] tic[3] 更新其余值
void update()
{
	tic[4] = (4 - (Clock[1] + tic[1] + tic[2]) % 4) % 4;
	tic[5] = (4 - (Clock[2] + tic[1] + tic[2] + tic[3]) % 4) % 4;
	tic[6] = (4 - (Clock[3] + tic[2] + tic[3]) % 4) % 4;
	tic[7] = (4 - (Clock[4] + tic[1] + tic[4] + tic[5]) % 4) % 4;
	tic[9] = (4 - (Clock[5] + tic[1] + tic[3] + tic[5] + tic[7]) % 4) % 4;
	tic[8] = (4 - (Clock[7] + tic[4] + tic[7]) % 4) % 4;
}

bool check()
{
	if ((Clock[6] + tic[3] + tic[5] + tic[6] + tic[9]) % 4)
	{
		return false;
	}
	if ((Clock[8] + tic[5] + tic[7] + tic[8] + tic[9]) % 4)
	{
		return false;
	}
	if ((Clock[9] + tic[6] + tic[8] + tic[9]) % 4)
	{
		return false;
	}
	return true;
}

void enumerate()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				tic[1] = i;
				tic[2] = j;
				tic[3] = k;
				update();
				if (check())
				{
					int tmp = accumulate(tic, tic + 10, 0);
					if (tmp < minStep)
					{
						minStep = tmp;
						for (int i = 0; i < 10; i++)
						{
							minTic[i] = tic[i];
						}
					}
				}
			}
		}
	}
}

int main()
{
	for (int i = 1; i <= 9; i++)
	{
		cin >> Clock[i];
	}
	enumerate();
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 0; j < minTic[i]; j++)
		{
			cout << i << " ";
		}
	}
	cout << endl;
	return 0;
}