/*
描述

我们拍摄的一张CT照片用一个二维数组来存储，假设数组中的每个点代表一个细胞。每个细胞的颜色用0到255之间（包括0和255）的一个整数表示。我们定义一个细胞是异常细胞，如果这个细胞的颜色值比它上下左右4个细胞的颜色值都小50以上（包括50）。数组边缘上的细胞我们不检测。现在我们的任务是，给定一个存储CT照片的二维数组，写程序统计照片中异常细胞的数目。

输入

第一行包含一个整数N（100>=N>2）.

下面有 N 行，每行有 N 个0~255之间的整数，整数之间用空格隔开。

输出

输出只有一行，包含一个整数，为异常细胞的数目。
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int N = 0;
	int CT[100][100];
	int numOfExceptions = 0;

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> CT[i][j];
		}
	}

	for (int i = 1; i < N - 1; i++)
	{
		for (int j = 1; j < N - 1; j++)
		{
			int val = CT[i][j];
			if ((CT[i - 1][j] - val) >= 50 && (CT[i][j - 1] - val) >= 50 && (CT[i][j + 1] >= 50) && (CT[i + 1][j] >= 50))
			{
				numOfExceptions++;
			}
		}
	}
	cout << numOfExceptions << endl;
	return 0;
}
