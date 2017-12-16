/*
分离整数的各个数位

描述

从键盘输入一个任意的三位整数，要求正确地分离出它的百位、十位和个位数，并分别在屏幕上输出，输出采用每行输出一个数的方式，不带其它符号。

输入

一个任意的三位整数

输出

一个任意的三位整数
*/

#include <iostream>
using namespace std;

int main()
{
	int n = 0;
	int a[3];
	cin >> n;

	for (int i = 2; i >= 0; i--)
	{
		a[i] = n % 10;
		n /= 10;
	}

	for (int i = 0; i < 3; i++)
	{
		cout << a[i] << endl;
	}
	return 0;
}
