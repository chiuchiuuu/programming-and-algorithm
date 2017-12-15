# Week5

## 字符串与指针

```c++
char *c = "hello";
cout << c << endl; // 打印字符串
cout << static_cast<void*>(c) << endl; // 打印地址
```

## 再谈一维数组的地址

```c++
#include <iostream>
using namespace std;

int mian()
{
	int a[4] = { 1,3,5,7 };
  	cout << a << endl; // 指向数组首元素
  	cout << a + 1 << endl; // 跨过一个元素
  	cout << &a <<endl; // 指向整个数组
  	cout << &a + 1 << endl; // 跨过整个数组
  	cout << *(&a) << endl; // 指向数组首元素
  	cout << *(&a) + 1 << endl;
  	return 0;
}
```

## 二维数组

概念部分见PPT，很重要！