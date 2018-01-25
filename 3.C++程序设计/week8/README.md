# 标准模板库 STL

## 概述

STL：standard template library

c++里的重用

- 面向对象：继承、多态、标准类库
- 泛型程序设计：模板机制，STL

### 泛型程序设计

将一些常用的数据结构（比如链表，数组，二叉树）和算法（比如排序，查找）写成模板，以后则不论数据结构里放的是什么对象，算法针对什么样的对象，则都不必重新实现数据结构，重新编写算法。

### 标准模板库

- 常用数据结构和算法的模板的集合

基本概念

- 容器：容纳数据结构，是类模板
- 迭代器：可用于依次存取容器中元素，类似指针
- 算法：用来操作容器中的元素的函数模板

```c++
int array[100];
sort(array, array+70);
// 容器：数组
// 迭代器，int*
// 算法：sort
```

## 容器

可以用于存放各种类型的数据（基本类型的变量，对象等）的数据结构，都是类模板

- 顺序容器：`vector`, `deque`, `list`
- 关联容器：`set`, `multiset`, `map`, `multimap`
- 容器适配器：`stack`, `queue`, `priority_queue`

对象被插入容器中时，被插入的是对象的一个复制品。许多算法，比如排序，查找，要求对容器中的元素进行比较，有的容器本身就是排序的，所以，放入容器的对象所属的类，往往还应该重载 `==` 和 `<` 运算符。

### 顺序容器

容器并非排序的，元素的插入位置同元素的值无关。

- `vector`：头文件 `<vector>`
  - 动态数组。元素在内存连续存放。随机存取任何元素都能在常数时 间完成。在**尾端**增删元素具有较佳的性能(大部分情况下是常数时间）。
- `deque`：头文件 `<deque>`
  - 双向队列。元素在内存连续存放。随机存取任何元素都能在常数时间完成(但次于vector)。在**两端**增删元素具有较佳的性能(大部分情况下是常数时间）
  - 有两个指针：`head`, `tail`
- `list`：头文件 `<list>`
  - 双向链表。元素在内存不连续存放。在任何位置增删元素都能在常 数时间完成。**不支持随机存取**。

### 关联容器

- 元素是**排序**的
- 插入任何元素，都按相应的排序规则来确定其位置
- 在查找时具有非常好的性能
- 通常以平衡二叉树方式实现，插入和检索的时间都是 $O(\log(N))$
- `set/muitiset`：头文件 `<set>`
  - 集合。set中不允许相同元素，multiset中允许存在相同的元素。
- `map/multimap`： 头文件 `<map>`
  - map与set的不同在于map中存放的元素有且仅有两个成员变量，一个名为 `first`,另一个名为 `second`, `map`根据 `first` 值对元素进行从小到大排序， 并可快速地根据 `first` 来检索元素。 
  - `map` 同 `multimap` 的不同在于是否允许相同 `first` 值的元素。

### 容器适配器

- `stack`：头文件 `<stack>`
  - 栈。是项的有限序列，并满足序列中被删除、检索和修改的项只能是最近插入 序列的项（栈顶的项）。**后进先出**。
- `queue`：头文件 `<queue>`
  - 队列。插入只可以在尾部进行， 删除、检索和修改只允许从头 部进行。**先进先出**。
- `priority_queue`： 头文件 `<queue>`
  -  优先级队列。最高优先级元素总是第一个出列

### 成员函数

顺序容器和关联容器共有：

- `begin` 返回指向容器中第一个元素的迭代器
- `end` 返回指向容器中最后一个元素后面的位置的迭代器 
- `rbegin` 返回指向容器中最后一个元素的迭代器 
- `rend` 返回指向容器中第一个元素前面的位置的迭代器 
- `erase` 从容器中删除一个或几个元素 
- `clear` 从容器中删除所有元素

顺序容器：

- `front` :返回容器中第一个元素的引用 
- `back` : 返回容器中最后一个元素的引用 
- `push_back` : 在容器末尾增加新元素 
- `pop_back` : 删除容器末尾的元素
- `erase` :删除迭代器指向的元素(可能会使该迭代器失效），或删除一个区间，返回被删除元素后面的那个元素的迭代器

## 迭代器

- 用于指向顺序容器和关联容器中的元素
- 迭代器用法和指针类似
- 有 `const` 和非 `const` 两种
- 通过迭代器可以读取它指向的元素
- 通过非 `const` 迭代器还能修改其指向的元素

定义

```c++
容器类名::iterator 变量名;
容器类名::const_interator 变量名;
```

访问

```c++
*迭代器变量名
```

迭代器上可以执行 `++` 操作, 以使其指向容器中的下一个元素。 如果迭代器到达了容器中的最后一个元素的后面，此时再使用它，就会出错，类似于使用NULL或未初始化的指针一样。

例

```c++
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  	vector<int> v;
  	v.push_back(1);
  	v.push_back(2);
  	v.push_back(3);
  	vector<int>::const_iterator i;
  	for (i = v.begin(); i != v.end(); i++)
    {
      	cout << *i << ",";
    }
  	cout << endl;
  	// 反向迭代器
  	vector<int>::reverse_iterator r;
  	for (r = v.rbegin(); r != v.rend(); r++)
    {
		cout << *r << ",";
    }
  	cout << endl;
  	vector<int>::iterator j;
  	for (j = v.begin(); j != v.end(); j++)
    {
      	*j = 100;
    }
  	for (i = v.begin(); i != v.end(); i++)
    {
      	cout << *i << ",";
    }
  	return 0;
}
```

### 双向迭代器

可进行的操作：

- `++p`, `p++` 使 `p` 指向容器中下一个元素 
- `--p`, `p--` 使 `p` 指向容器中上一个元素 `*p`
- 赋值，判断相等

### 随机访问迭代器

可进行的操作

- 双向迭代器的所有操作
- `p += i` 将p向后移动i个元素
- `p -= i` 将 `p` 向向前移动i个元素
- `p + i` 值为: 指向 `p` 后面的第i个元素的迭代器
- `p - i` 值为: 指向 `p` 前面的第i个元素的迭代器
- `p[i]` 值为: `p`后面的第i个元素的引用
- 比较大小

| 容器               | 迭代器  |
| :--------------- | :--- |
| `vector`         | 随机访问 |
| `deque`          | 随机访问 |
| `list`           | 双向   |
| `set/multiset`   | 双向   |
| `map/mutimap`    | 双向   |
| `stack`          | 不支持  |
| `queue`          | 不支持  |
| `priority_queue` | 不支持  |

#### 遍历 `vector`

```c++
vector<int> v(100);
// []运算符
for (int i = 0; i < v.size(); i++)
{
  	cou << v[i];
}
// 迭代器
vector<int>::const_iterator i;
for (i = v.begin(); i < v.end(); i++)
{
  	cout << *i;
}
// 间隔一个输出
i = v.begin();
while (i < v.end())
{
  	cout << *i;
  	i += 2;
}
```

#### 遍历 `list`

```c++
list<int> v;
list<int>::const_iterator i;
for (i = v.begin(); i != v.end(); i++)  // 不可写成 i < v.end()
{
  	cout << *i;
}
```

## 算法简介

- 算法就是一个个函数模板, 大多数在 `<algorithm>` 中定义
- STL中提供能在各种容器中通用的算法，比如查找，排序等
- 算法通过迭代器来操纵容器中的元素。许多算法可以对容器中的一个 局部区间进行操作，因此需要两个参数，一个是起始元素的迭代器， 一个是终止元素的后面一个元素的迭代器。比如，排序和查找
- 有的算法返回一个迭代器。比如 `find()` 算法，在容器中查找一个元 素，并返回一个指向该元素的迭代器
- 算法可以处理容器，也可以处理普通数组

### 示例：`find()`

原型：

```c++
template<class InIt, class T>
InIt find(InIt first, InIt last, const T &val);
```

- `first` 和 `last` 这两个参数都是容器的迭代器，它们给出了容器中的 查找区间起点和终点[first,last)，**左闭右开**。区间的起点是位于查找范围之中 的，而终点不是。`find()`在[first,last)查找等于`val`的元素
- 函数返回值是一个迭代器。如果找到，则该迭代器指向被找到的元素。 如果找不到，则该迭代器等于 `last`

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namesapce std;

int main()
{
  	int array[10] = { 10,20,30,40 };
  	vector<int> v;
  	v.push_back(1);
  	v.push_back(2);
  	v.push_back(3);
  	v.push_back(4);
  	vector<int>::iterator p;
  	p = find(v.begin(), v.end(), 3);
  	if (p != v.end())
    {
      	cout << *p << endl;
    }
  	p = find(v.begin(), v.end(), 9);
  	if (p == v.end())
    {
      	cout << "not found" << endl;
    }
  	p = find(v.begin() + 1, v.end() - 2, 1);
  	if (p != v.end())
    {
      	cout << *p << endl;
    }
  	int *pp = find(array, array + 4, 20); // 数组名就是迭代器
  	cout << *pp << endl;
  	return 0;
}
```

## STL中的大小与相等

#### 大小

- 关联容器内部的元素是从小到大排序的
- 有些算法要求其操作的区间是从小到大排序的，称为“有序区间算法” 例：binary_search
- 有些算法会对区间进行从小到大排序，称为“排序算法” 例： sort
- 还有一些其他算法会用到“大”，“小”的概念 


>  使用STL时，在缺省的情况下，以下三个说法等价： 
>
>  - x比y小
>  - `op(x, y)` 返回值为 `true`（`op`为自定义的比较函数）
>  - y比x大

### 相等

x和y相等表示

- `x==y`
  - 例：在未排序的区间上进行的算法，如顺序查找find
- x小于y和y小于x同时为假
  - 有序区间算法，如 `binary_search` 
  - 关联容器自身的成员函数find

示例

```c++
#include <iostream>
#include <algorithm>
using namespace std;

class A
{
	int v;
public:
  	A(int n):v(n){}
  	bool operator<(const A &a2) const
    {
      	cout << v << "<" << a2.v << "?" << endl;
      	return false;
    }
  	bool operator==(const A &a2) const
    {
      	cout << v << "==" << a2.v << "?" << endl;
      	return v == a2.v;
    }
};

int main()
{
  	A a[] = { A(1),A(2),A(3),A(4),A(5) };
  	cout << binary_search(a, a+4, A(9)); // 用 < 做比较
  	return 0；
}
```

输出结果：找到了 `A(9)`

```
3<9? 
2<9? 
1<9? 
9<1? 
1
```



## `vector`

- 可变长的动态数组
- 头文件 `#include <vector>`
- 支持随机访问迭代器
  - 根据下标随机访问某个元素时间为常数
  - 在尾部添加速度很快（超出预留空间需要重新分配空间）
  - 在中间插入慢（需要移动后面所有的元素）
- 所有STL算法都能对 `vector` 操作

### 成员函数

构造函数初始化

| 成员函数                                    | 作用                                   |
| --------------------------------------- | :----------------------------------- |
| `vector()`                              | 无参构造函数, 将容器初始化成空的                    |
| `vector(int n)`                         | 将容器初始化成有n个元素                         |
| `vector(int n, const T &val)`           | 假定元素类型是T, 将容器初始化成 有n个元素, 每个元素的值都是val |
| `vector(iterator first, iterator last)` | 将容器初始化为与别的容器上区间 [first, last)一致的内容   |

其他常用函数

| 成员函数                           | 作用             |
| ------------------------------ | -------------- |
| `void pop_back()`              | 删除容器末尾的元素      |
| `void push_back(const T &val)` | 将val添加到容器末尾    |
| `int size()`                   | 返回容器中元素的个数     |
| `T &front()`                   | 返回容器中第一个元素的引用  |
| `T &back()`                    | 返回容器中最后一个元素的引用 |

示例

```c++
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  	int a[5] = { 1,2,3,4,5 };
  	vector<int> v(5);
  	cout << v.end() - v.begin() << endl; // vector大小
  	for (int i = 0; i < v.size(); i++)
    {
		v[i] = i;
    }
  	v.at(4) = 100;
  	for (int i = 0; i < v.size(); i++)
    {
		cout << v[i] << ",";
    }
  	cout << endl;
  	vector<int> v2(a, a + 5);
  	v2.insert(v2.begin() + 2, 13);
  	for (int i = 0; i < v2.size(); i++)
    {
      	cout << v2.at(i) << ",";
    }
}
```

### 二维动态数组

```c++
vector<vector<int>> v(3);
// v有三个元素
// 每个元素都是 vector<int>
```

使用例子

```c++
#include <iostream>
#include <vector>
using namespace std;
int main()
{
  	vector<vector<int>> v(3);
  	for (int i = 0; i < v.size(); i++)
    {
      	for (int j = 0; j < 4; j++)
        {
          	v[i].push_back(j);
        }
    }
    for (int i = 0; i < v.size(); i++)
    {
          for (int j = 0; j < 4; j++)
          {
              cout << v[i][j] << ",";
          }
          cout << endl;
    }
    return 0
}
```



## `list`

- 双向链表
- `#include <list>`
- 在任何位置插入/删除都是常熟时间
- 不支持根据下标随机存取元素
- 只支持双向迭代器

### 成员函数

| 成员函数         | 作用                                      |
| ------------ | :-------------------------------------- |
| `push_front` | 在链表最前面插入                                |
| `pop_front`  | 删除链表最前面的元素                              |
| `sort`       | 排序 (list 不支持 STL 的算法 sort)              |
| `remove`     | 删除和指定值相等的所有元素                           |
| `unique`     | 删除所有和前一个元素相同的元素                         |
| `merge`      | 合并两个链表, 并清空被合并的链表                       |
| `reverse`    | 颠倒链表                                    |
| `splice`     | 在指定位置前面插入另一链表中的一个或多个元素, 并在另一链表中删除被插入的元素 |

> 由于`list`的迭代器不支持随机访问，故不能用STL中的`sort`函数对它进行排序
>
> `list` 自带排序函数
>
> ```c++
> list<T> classname
> classname.sort(compare); // 自定义比较函数
> classname.sort() // 缺省情况下按 < 排序
> ```

应用程序

见PPT

## `deque`

- 双向队列
- `#include <deque>`
- 所用适用于`vector`的操作都适用于`deque`
- 特有的函数：`push_front()`, `pop_front()`



## 函数对象

如果一个类重载了运算符`()`则该类的对象就成为函数对象

例1

```c++
class MyAverage
{
public:
  	double operator()(int a1, int a2, int a2)
    {
		return (double)(a1 + a2 + a3) / 3;
    }
};
MyAverage average; // 函数对象
cout << average(3,2,3);   // 类似调用函数
```

例2：`accumulate`源码

```c++
template<typename _InputIterator, typename _Tp>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init)
{
	for (; __first != __last; ++__first)
    {
		__init = __init + *__first;
    }
  	return __init
}

template<typename _InputIterator, typename _Tp, typename _BinaryOperation>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _BinaryOPeartion __binary_op)
{
  	for (;__first != __last; __first++)
    {
      	__init = __binary_op(__init, *__first);
    }
  	return __init;
}
// _binary_op对应的实参可以是个函数或函数对象
```

例3：求n次方的和

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

int SumSquares(int total, int value)
{
	return total + value * value;
}

// 输出区间[first,last)中的元素
template<class T>
void PrintInterval(T first, T last)
{
	for (; first != last; first++)
	{
		cout << *first << " ";
	}
	cout << endl;
}

// 求n次方的函数对象的类
template<class T>
class SumPowers
{
private:
	int power;
public:
	SumPowers(int n) :power(n) {}
	const T operator()(const T &total, const T &value)
	{
		T v = value;
		for (int i = 0; i < power - 1; i++)
		{
			v = v * value;
		}
		return total + v;
	}
};

int main()
{
	const int SIZE = 10;
	int a1[] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v(a1, a1 + SIZE);
	cout << "1)";
	PrintInterval(v.begin(), v.end());
	int result = accumulate(v.begin(), v.end(), 0, SumSquares);
	cout << "2)平方和：" << result << endl;
	result = accumulate(v.begin(), v.end(), 0, SumPowers<int>(3));
	cout << "3)立方和：" << result << endl;
	result = accumulate(v.begin(), v.end(), 0, SumPowers<int>(4));
	cout << "4)四次方和：" << result << endl;
	return 0;
}
```

函数对象类模板

- `equal_to`
- `greater`
- `less`
- ...

头文件：`<functional>`

### `greater` 的应用

原型

```c++
template<class T>
struct greater:public binary_function<T, T, bool>
{
	bool operator()(const T &x, const T &y) const
	{
		return x > y;
	}
}
```

应用：用于`list`的`sort`带参数成员函数

```c++
#include <iostream>
#include <list>
#include <functional>
using namespace std;

class Myless
{
public:
	bool operator()(const int &c1, const int &c2)
	{
		return (c1 % 10) < (c2 % 10); 
	}
};

template<class T>
void Print(T first, T last)
{
	for (; first != last; first++)
	{
		cout << *first << ",";
	}
	cout << endl;
}

int main()
{
	const int SIZE = 5;
	int a[SIZE] = { 5,21,14,2,3 };
	list<int> lst(a, a + SIZE);
	lst.sort(Myless());   // 个位数小的排前面
	Print(lst.begin(), lst.end());
	lst.sort(greater<int>());  // 从大到小排序
	Print(lst.begin(), lst.end());
	return 0;
}
```

