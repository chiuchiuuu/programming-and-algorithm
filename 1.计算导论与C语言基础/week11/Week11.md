# Week11

## 字符数组与字符串

## 输入缓冲区

键盘输入的数据先传送到输入缓冲区，程序感应到输入缓冲区的数据后再到缓冲区获取数据。

连续输入：`while (cin >> n)`

## 一个字符的输入

`cin.get()`

- 可用于读入**一个字符**
- 2种形式：无参数和一个参数
  - `cin.get()`
  - `cin.get(char)`

```c++
// cin.get()不跳过空格和回车 
while ((c = cin.get()) != EOF)
while (cin.get(c))
// 不跳过任何字符
while (c = getchar()) 
```

## 一串字符串的输入

`cout` 输入普通数组名，输出的时地址。

`cin` 字符串，以空格和回车为间隔符

`cin.get(ch, 10, '\n')`

- 读入10-1个字符赋给数组`ch`
- `'\n'` 为终止符

`cin.getline(ch, 10, 'o')`

- 与`cin.get()`作用差不多

`get` 与 `getline` 的区别：缓冲区指针

- `getline`遇到终止标志字符时结束，缓冲区指针移到终止标志字符之后
- `get` 遇到终止字符时停止读取，指针不移动

一个重要的例子

```c++
#include <iostream>
using namespace std;

int main()
{
	char a[10][10];
	int n = 0;
	cin >> n;
  	// 纠正
  	// cin.get(); 读走换行符
	for (int i = 0; i < n; i++)
    {
      	cin.getline(a[i], 10);
    }
  	for (int i = 0; i < n; i++)
    {
	cout << a[i] << endl;}
}
```

## 字符串应用例题

实现字符串拼接

```c++
#include <iostream>
using namespace std;

int main()
{
	int len1, len2;
	char str1[40], str2[40];
	cin.getline(str1, 20);
	cin.getline(str2, 20);
	for (len1 = 0; str1[len1] != '\0'; len1++);
	for (len2 = 0; str2[len2] != '\0'; len2++);

	if (len1 >= len2)
	{
		for (len2 = 0; str2[len2] != '\0'; len2++)
		{
			str1[len1++] = str2[len2];
		}
		str1[len1] = '\0';
	}
	else
	{
		for (len1 = 0; str1[len1] != '\0'; len1++)
		{
			str2[len2++] = str1[len1];
		}
		str2[len2] = '\0';
	}
	cout << str1 << endl;
	cout << str2 << endl;
	return 0;
}
```

统计单词数

```c++
#include <iostream>
using namespace std;

int main()
{
	char str[80];
	int num = 0;
	bool flag = false;
	cin.getline(str, 80);
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			flag = false;
		}
		else if (!flag)
		{
			num++;
			flag = true;
		}
	}
	cout << num << endl;
	return 0;
}
```

