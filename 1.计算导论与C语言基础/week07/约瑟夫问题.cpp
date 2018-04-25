#include <iostream>
using namespace std;

int main()
{

	int n = 0, m = 0;

	while (cin >> n >> m)
	{
		if (n == 0 && m == 0)
		{
			break;
		}

		int id[300]; // id 记录猴子的编号
		int state[300];  // state 记录猴子状态，1表示圈内，0表示圈外

		for (int i = 0; i < n; i++)
		{
			id[i] = i + 1;
			state[i] = 1;
		}

		int count = 1; // 从1开始报数
		for (int i = 0, num = n; num != 1; i++) // num：圈内猴数
		{
			// i >= n 表示绕了一圈
			if (i >= n)
			{
				i -= n;
			}

			if (state[i] != 0)
			{
				if (count % m == 0)
				{
					state[i] = 0;
					num--;
				}
				count = (count + 1) % m;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (state[i] == 1)
			{
				cout << id[i] << endl;
			}
		}
	}
	return 0;
}