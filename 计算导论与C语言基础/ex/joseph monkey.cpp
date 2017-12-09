/*
描述

约瑟夫问题：有ｎ只猴子，按顺时针方向围成一圈选大王（编号从１到ｎ），从第１号开始报数，一直数到ｍ，数到ｍ的猴子退出圈外，剩下的猴子再接着从1开始报数。就这样，直到圈内只剩下一只猴子时，这个猴子就是猴王，编程求输入ｎ，ｍ后，输出最后猴王的编号。

输入

每行是用空格分开的两个整数，第一个是 n, 第二个是 m ( 0 < m,n <=300)。最后一行是：

0 0

输出

对于每行输入数据（最后一行除外)，输出数据也是一行，即最后猴王的编号
*/

#include <iostream>
using namespace std;

int main()
{

	int n = 0, m = 0;
    cin >> m >> n;

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
	return 0;
}
