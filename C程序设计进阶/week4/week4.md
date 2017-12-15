# Week4

## 指针

变量三要素

- 地址：指向该变量的指针
- 名字
- 值

## 指针变量

运算优先级：

后置`++` `--` 高于 `*` `&`

## 指针变量示例

## 指针的`++` `--`

指针的`++` `--` 要基于基类型

## 数组与指针

数组名相当于指向数组第一个元素的指针

数组名不是变量，不能赋值

## 用指针访问数组

`pointer[i] == *(pointer + i)`

```c++
int main()
{
	int a[10];
  	for (int i = 0; i < 10; i++)
    {
		cin >> a[i];
    }
  	for (int i = 9; i >= 0; i--)
    {
		cout << setw(3) << a[i];
    }
  	return 0;
}
```

```c++
int main()
{
	int a[10];
  	int *p = a;
  	for (int i = 0; i < 10; i++)
    {
      	cin >> *p++;
    }
  	for (int i = 9; i >= 0; i--)
    {
      	cout << setw(3) << *p--;
    }
  	return 0;
}
```

