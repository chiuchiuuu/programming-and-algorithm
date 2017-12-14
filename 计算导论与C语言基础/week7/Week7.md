# Week7

## 变量定义的含义

- 内存的直观认识
- 变量定义与内存

> 这里一个很棒的地方是，在介绍变量定义的时候就介绍内存分配，这对以后介绍指针应该很有好处

## 整数型的类别

- `int`
- `short`
- `long`
- `signed` & `unsigned`

`sizeof()`

## 整数型的存储

负整数的存储：补码

正整数补码 = 原码取反 + 1

补码利于计算

## 整数的输入输出

打印一个数的十六进制表示

```c++
#include <iostream>
using namespace std;
int main()
{
	int a = -123;
	cout << hex << a << endl;
	// 八进制：oct, 十进制： dec
  	return 0;
}
```

输入八进制，十六进制数

八进制：`0` 开头

十六进制：`0x` 开头

## 最大与最小数

`unsigned int`: 最大大约42亿

`signed int`: 

- max：大约21亿
- min：当最高位是1其他位是0时，最高为即表示负号也表示整数最高位1

详细见PPT

## 浮点型

`float` 精度7位

`double` & `long double` 精度15位

## 字符型

## 布尔型

字节是计算机能控制的最小存储单位

## 常量

- 字面常量
- 符号常量

整型常量后缀

- `L`: long
- `U`: unsigned int
- `LU`: unsigned long

浮点型常量后缀

- `F`: float
- `L`: double
- 默认`double`

## 变量命名

- 匈牙利命名法
- 变量命名法