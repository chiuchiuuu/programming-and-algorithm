#include <iostream>
#include <cmath>
using namespace std;

int wall[17][17], paint[17][17];
int width;
int minCount;

int Count()
{
	int sum = 0;
	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			sum += paint[i][j];
		}
	}
	return sum;
}

// 初始化数组和处理输入
void init()
{
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			wall[i][j] = 0;
			paint[i][j] = 0;
		}
	}

	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			char tmp;
			cin >> tmp;
			switch (tmp)
			{
			case 'y':
				wall[i][j] = 0;
				break;
			case 'w':
				wall[i][j] = 1;
				break;
			}
		}
	}
}

// 验证答案是否正确，主要验证最后一行
bool guess()
{
	for (int j = 1; j <= width; j++)
	{
		if ((paint[width][j - 1] + paint[width][j] + paint[width][j + 1] + paint[width - 1][j]) % 2 != wall[width][j])
			return false;
	}
	return true;
}

// 根据第一行的枚举更新剩余几行
void update()
{
	for (int i = 1; i < width; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			paint[i + 1][j] = (wall[i][j] + paint[i][j] + paint[i][j - 1] + paint[i][j + 1] + paint[i - 1][j]) % 2;
		}
	}
}

// 枚举第一行的所有情况，直到得出答案
void enumerate()
{
	// 初始情况
	update();

	for (int i = 0; i < pow(2, width); i++)
	{
		if (guess())
		{
			int count = Count();
			if (count < minCount)
			{
				minCount = count;
			}
		}
		paint[1][1]++;
		int k = 1;
		while (paint[1][k] > 1) // 进位
		{
			paint[1][k] = 0;
			paint[1][++k]++;
		}
		update();
	}
}

int main()
{
	cin >> width;
	minCount = 226; // 最大15*15 = 225
		init();
		enumerate();

		if (minCount == 226)
		{
			cout << "inf" << endl;
		}
		else
		{
			cout << minCount << endl;
		}
}