# Week10

## 再谈一维数组

使数组长度易于修改的两种方式

```c++
const int i = 4;
int a[i];
```

```c++
#define N 4

int a[N];
```

## 二维数组

```c++
#include <iomanip>

cout << setw(3) << a[i][j] << endl; // setw 设定输出字符宽度
```

## 数组作用

存储数据，数字统计

筛法求素数

```c++
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int a[100] = {0};
	for (int i = 2; i < sqrt(100.0); i++)
    {
      	int sum = i;
      	if (a[sum] == 0)
        {
            while (sum < 100)
            {
                sum += i;
                if (sum < 100)
                {
                    a[sum] = 1;
                }
            }
        }
    }
    for (int i = 0; i < 100; i++)
    {
      	if (a[i] == 0)
      	{
          	cout << i << " ";
      	}
    }
    return 0;
}
```

