# Week2

## 函数指针

声明

```
类型名 (*指针变量名)(参数列表)
```

示例

```c++
void PrintMin(int a, int b)
{
	if(a < b)
    {
		cout << a << endl;
    }
  	else
    {
		cout << b << endl;
    }
}

int main()
{
	void (*pf)(int, int);
  	int x = 4, y = 5;
  	pf = PrintMin;
  	pf(x, y);
  	return 0;
}
```

### `qsort`函数

函数原型：

```c++
void qsort(void *base, int nelem, unsigned int width, int (*pfCompare)(const void *, const void *));
```

- `base`: 排序数组的起始地址
- `nelem`: 元素个数
- `width`: 每个元素大小（以字节为单位）
- `pfCompare`: 比较函数的地址

比较函数原型：

```c++
int 比较函数名(const void *elem1, const void *elem2);
```

- `*elem1` 拍前则返回负整数
- `*elem2` 拍前则返回正整数
- 都可以则返回0

示例：

```c++
#include <iostream>
using namespace std;

int MyCompare(const void * elem1, const void * elem2)
{
	unsigned int *p1, *p2;
  	p1 = (unsigned int *)elem1;
  	p2 = (unsigned int *)elem2;
  	return (*p1 % 10) - (*p2 * 10)
}

int main()
{
	unsigned int a[5] = { 8,123,11,10,4 };
  	qsort(a, 5, sizeof(unsigned int), MyCompare);
  	for (int i = 0; i < 5; i++)
    {
		cout << a[i] << endl;
    }
  	return 0;
}
```



## 命令行参数

命令行方式运行程序

```c++
int main(int argc, char *argv[])
{
	...
}
```



## 位运算

`&`

- 将变量某些位清零且同时保留其他不变

  - 例如将`int`的低8清零：`n = n & 0xffffff00`

- 获取变量的某一位

`|`

- 将某些位置1，且保留其他位不变，例：`n |= 0xff`

`^`

- 将某些位取反，其他不变，例：`n ^= 0xff`
- 特点：如果`a^b = c`，那么就有`c^b = a` 以及 `c^a = b`
  - 此规律可用来简单加密解密。`b`做密钥
- 交换变量的值
  - `a = a ^ b; b = b ^ a; a = a ^ b`

`~`

`<<`

- 低位补0
- 左移n位等价于乘以 $2^n$，速度比乘法操作快

`>>`

- 符号位是什么就补什么
- 右移，除以 $2^n$ ，向下取整

例：给定`int a, n` 求第a的第n位

```c++
(a >> n) & 1
(a & (1 << n)) >> n  // (n != 31)
```



## 引用

定义

```c++
类型名 &引用名 = 某变量名
```

- 一定要初始化，初始化后不能改变
- 只能引用变量，不能引用常量和表达式

应用

- 引用做参数：交换

```c++
void swap(int &a, int &b)
{
	int tmp = a;
  	a = b;
  	b = tmp;
}
```

- 引用做函数返回值

```c++
int n = 4;
int &SetValue()
{
	return n;
}
int main()
{
	SetValue() = 40;
  	cout << n;
  	return 0;
}
```

- 常引用

```c++
int n = 100;
const int &r = n;
r = 200; // error
```



## const关键字和常量

定义常量

定义常量指针

- 不可通过常量指针修改其指向的内容
- 常量指针的指向可以修改
- 不能把常量指针赋值给非常量指针，但可以强制类型转换



## 动态内存分配

用`new`运算符实现动态内存分配

- 分配
  - 分配一个变量：`Pointer = new Type;`
  - 分配一个数组：`Pointer = new Type[Number]`
- `new`的返回类型都是相应类型的**指针**
- 释放（不能释放多次）
  - `delete Pointer;`
  - `delete [] Pointer;`



## 内联函数

函数调用是有时间开销的（参数入栈，返回地址）。如果函数本身只有几条语 句，执行非常快，而且函数被反复执行很多次，相比 之下调用函数所产生的这个开销就会显得比较大。

为了减少函数调用的开销，引入了**内联函数机制**。编译器处理对内联函数的调用语句时，是将整个函数的代码插入到调用语句处，而不会产生调用函数的语句。

定义，关键字 `inline`

```c++
inline int Max(int a, int b);
```

弊端：函数体积增大



## 函数重载

一个或多个函数，名字相同，然而参数个数或参数类型不相同，这叫做函数的重载。 （返回值不能不同！！）

```c++
int Max(double f1, double f2);
int Max(int n1, int n2);
int Max(int n1, int n2, int n3);
```

函数重载使得函数命名变得简单。

编译器根据调用语句的中的实参的个数和类型判断应该调用哪个函数。如果有歧义则会报错，如`Max(3, 2.4)`