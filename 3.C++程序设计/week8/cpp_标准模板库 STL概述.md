# 标准模板库 STL

## 概述

STL：standard template library

c++里的重用

- 面向对象：继承、多态、标准类库
- 泛型程序设计：模板机制，STL

### 泛型程序设计

将一些常用的数据结构（比如链表，数组，二叉树）和算法（比如排序，查找）写成模板，以后则不论数据结构里放的是什么对象，算法针对什么样的对象，则都不必重新实现数据结构，重新编写算法。

### 基本概念

- 容器：容纳各种数据类型的通用数据结构，是类模板
- 迭代器：可用于依次存取容器中元素，类似指针
- 算法：用来操作容器中的元素的函数模板
  - $sort()$ 来对一个*vector* 中的数据进行排序
  - *find()*来搜索*list()*中的对象
  - 算法本身与他们操作的数据的类型无关

```c++
int array[100];
sort(array, array+70); //将前70个元素进行排序
// 容器：数组
// 迭代器，int*类型的指针
// 算法：sort
```

## 容器

可以用于存放各种类型的数据（基本类型的变量，对象等）的数据结构，都是**类模板**

- 顺序容器：`vector动态数组`, `deque双向队列`, `list双向链表`
- 关联容器：`set`, `multiset`, `map`, `multimap`
- 容器适配器：`stack`, `queue`, `priority_queue`

对象被插入容器中时，被插入的是对象的一个复制品。许多算法，比如排序，查找，要求对容器中的元素进行比较，有的容器本身就是排序的，所以，放入容器的对象所属的类，往往还应该重载 `==` 和 `<` 运算符。

### 顺序容器

容器并非排序的，元素的插入位置同元素的值无关。

- `vector`：头文件 `<vector>`
  - 动态数组。元素在内存连续存放。随机存取任何元素都能在常数时间完成。在**尾端**增删元素具有较佳的性能(大部分情况下是常数时间，如果超出预分配空间的大小时为$O(n)$,此时需要重新分配空间）。在开头或者中间插入为$O(n)$.
- `deque`：头文件 `<deque>`
  - 双向队列。元素在内存连续存放。随机存取任何元素都能在常数时间完成(但次于vector: 考虑情况，$tail$指针在$head$的前方，此时在数据读取的过程中，需要多一步的逻辑判断)。相较于$vector$在**两端**增删元素具有较佳的性能(大部分情况下是常数时间）
  - 有两个指针：`head`, `tail`
- `list`：头文件 `<list>`
  - 双向链表。元素在内存不连续存放。在任何位置增删元素都能在常数时间完成( 元素位置确定的情况下)。**不支持随机存取**，即不能通过下标$i$直接访问元素。

### 关联容器

- 元素是**排序**的
- 插入任何元素，都按相应的排序规则来确定其位置
- 在查找时具有非常好的性能
- 通常以平衡二叉树方式实现，插入和检索的时间都是 $O(\log(N))$
- `set/muitiset`：头文件 `<set>`
  - 集合。set中不允许相同元素，multiset中允许存在相同的元素。
- `map/multimap`： 头文件 `<map>`
  - map与set的不同在于map中存放的元素有且仅有两个成员变量，一个名为 `first`,另一个名为 `second`, `map`根据 `first` 值对元素进行从小到大排序， 并可快速地根据 `first` 来检索元素。 $first$相当于关键字，$second$相当于$value$值。
  - `map` 同 `multimap` 的不同在于是否允许相同 `first` 值的元素。

### 容器适配器

- `stack`：头文件 `<stack>`
  - 栈。是项的有限序列，并满足序列中被删除、检索和修改的项只能是最近插入 序列的项（栈顶的项）。**后进先出**。
- `queue`：头文件 `<queue>`
  - 单向队列。插入只可以在尾部进行， 删除、检索和修改只允许从头部进行。**先进先出**。
- `priority_queue`： 头文件 `<queue>`
  -  优先级队列。最高优先级元素总是第一个出列

### 成员函数

顺序容器和关联容器共有：

- `begin` 返回指向容器中第一个元素的迭代器
- `end` 返回指向容器中最后一个元素**后面**的位置的迭代器 
- `rbegin` 返回指向容器中最后一个元素的迭代器 
- `rend` 返回指向容器中第一个元素前面的位置的迭代器 
- `erase` 从容器中删除一个或几个元素 
- `clear` 从容器中删除所有元素

顺序容器：

- `front` :返回容器中第一个元素的引用 
- `back` : 返回容器中最后一个元素的引用 
- **`push_back`** : 在容器末尾增加新元素 
- `pop_back` : 删除容器末尾的元素
- `erase` :删除迭代器指向的元素(可能会使该迭代器失效），或删除一个区间，返回被删除元素后面的那个元素的迭代器

## 迭代器

- 用于指向顺序容器和关联容器中的元素
- 迭代器用法和指针类似
- 有 `const` 和非 `const` 两种
- 通过迭代器可以读取它指向的元素
- 通过非 `const` 迭代器还能修改其指向的元素

定义一个容器类的迭代器的方法：（容器类：从容器模板实例化出来的类）

```c++
容器类名::iterator 变量名;
容器类名::const_interator 变量名;
```

访问一个迭代器指向的元素：

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
  	vector<int> v; //一个存放int元素的数组，一开始里面没有元素。
  	v.push_back(1);
  	v.push_back(2);
  	v.push_back(3);//在尾部添加
  	vector<int>::const_iterator i; //常量迭代器。const:只能访问，不能修改
  	for (i = v.begin(); i != v.end(); i++) //注意v.end()返回的是最后一个元素的后一个位置
    {
      	cout << *i << ",";
    }
  	cout << endl;
  	// 反向迭代器
  	vector<int>::reverse_iterator r;//与iterator类型不兼容
  	for (r = v.rbegin(); r != v.rend(); r++)//对反响迭代器的++操作，会指向前一个元素
    {
		cout << *r << ",";
    }
  	cout << endl;
  	vector<int>::iterator j;//非常量迭代器
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

STL常用的迭代器有两种：双向迭代器和随机访问迭代器。

### 双向迭代器

可进行的操作：

- `++p`, `p++` 使 `p` 指向容器中下一个元素 
- `--p`, `p--` 使 `p` 指向容器中上一个元素 
- `*p` 取`p`指向的值
- 赋值，判断相等 `p==p1` `p!=p1` 

### 随机访问迭代器

可进行的操作

- 双向迭代器的所有操作
- `p += i` 将p向后移动`i`个元素
- `p -= i` 将 `p` 向向前移动`i`个元素
- `p + i` 值为: 指向 `p` 后面的第`i`个元素的**迭代器**
- `p - i` 值为: 指向 `p` 前面的第`i`个元素的迭代器
- `p[i]` 值为: `p`后面的第`i`个元素的**引用**
- 比较大小`< >` `p<p1`: `p`指向的元素，在`p1`指向的元素的前面

| 容器             | 迭代器             |
| :--------------- | :----------------- |
| `vector`         | 随机访问(下标访问) |
| `deque`          | 随机访问           |
| `list`           | 双向               |
| `set/multiset`   | 双向               |
| `map/mutimap`    | 双向               |
| `stack`          | 不支持             |
| `queue`          | 不支持             |
| `priority_queue` | 不支持             |

#### 遍历 `vector`

```c++
vector<int> v(100);
for (int i = 0; i < v.size(); i++)
{
  	cou << v[i];//通过下标随机访问
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
for (i = v.begin(); i != v.end(); i++)  // 不可写成 i < v.end()。因为list上面的迭代器是双向迭代器，双向迭代器不能用<进行比较。
//list没有[]成员函数
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

- `first` 和 `last` 这两个参数都是容器的迭代器，它们给出了容器中的 查找区间起点和终点`[first,last)`，**左闭右开**。区间的起点是位于查找范围之中 的，而终点不是。`find()`在[first,last)查找等于`val`的元素
- 用`==`运算符判断相等
- 函数返回值是一个迭代器。如果找到，则该迭代器指向被找到的元素。 如果找不到，则该迭代器等于 `last`
- 顺序查找的时间复杂度是$O(n)$ 

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
  	p = find(v.begin(), v.end(), 3); //注意find()函数的返回值是一个迭代器
    //v.begin()也是一个迭代器
  	if (p != v.end())
    {
      	cout << *p << endl;
    }
  	p = find(v.begin(), v.end(), 9);
  	if (p == v.end())
    {
      	cout << "not found" << endl;
    }
  	p = find(v.begin() + 1, v.end() - 2, 1);//查找区间： [2,3);查找不到，会返回查找时地last,此处为3
  	if (p != v.end())
    {
      	cout << *p << endl;
    }
  	int *pp = find(array, array + 4, 20); // 数组名就是迭代器，因为数组名就是int*类型的指针
  	cout << *pp << endl;
  	return 0;
}
```

## STL中的大小与相等

### 大小

- 关联容器内部的元素是从小到大排序的
- 有些算法要求其操作的区间是从小到大排序的，称为“有序区间算法” 例：binary_search
- 有些算法会对区间进行从小到大排序，称为“排序算法” 例： sort
- 可以认为对**从小到大**的概念进行定义，比如按照数字的个位数字的大小关系进行比较——自定义大小
- 还有一些其他算法会用到“大”，“小”的概念 
- 使用STL时，在缺省的情况下，以下三个说法等价： 
  - x比y小
  - `op(x, y)` 返回值为 `true`（`op`为自定义的比较函数）
  - y比x大

### 相等

x和y相等表示

- `x==y`
  - 例：在未排序的区间上进行的算法，如顺序查找find
- x小于y**和**y小于x同时为假，注意此处的小于可以自定义
  - 有序区间算法，如 `binary_search` 
  - 关联容器自身的成员函数find

### 示例： STL中“相等”概念演示

```c++
#include <iostream>
#include <algorithm>
using namespace std;

class A
{
	int v;
public:
  	A(int n):v(n){}
  	bool operator<(const A &a2) const //运算符重载:两个class A的对象，一个都不会小于另一个
    {
      	cout << v << "<" << a2.v << "?" << endl;
      	return false;
    }
  	bool operator==(const A &a2) const //判断两个类是否相等
    {
      	cout << v << "==" << a2.v << "?" << endl;
      	return v == a2.v;
    }
};

int main()
{
  	A a[] = { A(1),A(2),A(3),A(4),A(5) };
  	cout << binary_search(a, a+4, A(9)); // 用 < 做比较，折半查找
  	return 0；
}
```

输出结果：

```
3<9? 
2<9? 
1<9? 
9<1? 
1
```

注意到在输出中没有用到`==`号，而是多次调用`<`。对程序而言，如果`1<9`不成立，同时`9<1`不成立，就会认为`9=1`

## `vector`

- 可变长的动态数组
- 必须头文件 `#include <vector>`
- 支持随机访问迭代器
  - 根据下标随机访问某个元素时间为常数
  - 在尾部添加速度很快（超出预留空间需要重新分配空间，通常为32个预留空间）
  - 在中间插入慢（需要移动后面所有的元素）
- 所有STL算法都能对 `vector` 操作

### 成员函数

#### 构造函数初始化

| 成员函数                                | 作用                                                         |
| --------------------------------------- | :----------------------------------------------------------- |
| `vector()`                              | 无参构造函数, 将容器初始化成空                               |
| `vector(int n)`                         | 将容器初始化成有n个元素的数组                                |
| `vector(int n, const T &val)`           | 假定元素类型是T, 将容器初始化成有n个元素, 每个元素的值都是val |
| `vector(iterator first, iterator last)` | 将容器初始化为与**别的**容器上区间 [first, last**)**一致的内容 |

#### 其他常用函数

| 成员函数                       | 作用                         |
| ------------------------------ | ---------------------------- |
| `void pop_back()`              | 删除容器末尾的元素           |
| `void push_back(const T &val)` | 将val添加到容器末尾          |
| `int size()`                   | 返回容器中元素的个数         |
| `T &front()`                   | 返回容器中第一个元素的引用   |
| `T &back()`                    | 返回容器中最后一个元素的引用 |

### 一维动态数组

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  	int a[5] = { 1,2,3,4,5 };
  	vector<int> v(5);//动态数组，其中的每一个元素都是int类型的，包含有5个元素
  	cout << v.end() - v.begin() << endl; // 返回vector大小，注意vector对应的迭代器是随机迭代器
  	for (int i = 0; i < v.size(); i++)
    {
		v[i] = i;//使用下标访问
    }
  	v.at(4) = 100;//第五个元素
  	for (int i = 0; i < v.size(); i++)
    {
		cout << v[i] << ",";
    }
  	cout << endl;
  	vector<int> v2(a, a + 5);//使用第四种方法初始化：vector(iterator first, iterator last)
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
  	vector<vector<int>> v(3);//v有三个元素，每个元素都是vector<int>容器
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
    return 0；
}
```



## `list`

- 双向链表
- `#include <list>`
- 在任何位置插入/删除都是常熟时间
- 不支持根据下标随机存取元素
- 具有所有顺序容器的成员函数
- ![ZCCoJe.png](https://s2.ax1x.com/2019/06/23/ZCCoJe.png)



### 成员函数

| 成员函数     | 作用                                                         |
| ------------ | :----------------------------------------------------------- |
| `push_front` | 在链表最前面插入                                             |
| `pop_front`  | 删除链表最前面的元素                                         |
| `sort`       | 排序 (list 不支持 STL 的算法 sort)                           |
| `remove`     | 删除和指定值相等的所有元素                                   |
| `unique`     | 删除所有和前一个元素相同的元素                               |
| `merge`      | 合并两个链表, 并清空其中被合并的链表                         |
| `reverse`    | 颠倒链表                                                     |
| `splice`     | 在指定位置前面插入另一链表中的一个或多个元素, 并在另一链表中删除被插入的元素 |

> 由于`list`的迭代器不支持随机访问，故不能用STL中的`sort`函数对它进行排序
>
> `list` 自带排序函数sort成员函数
>
> ```cpp
> list<T> classname
> classname.sort(compare); // 自定义比较函数
> classname.sort() // 缺省情况下按 < 排序
> ```

此外，由于`list`容器只能使用双向迭代器，故而不支持大小/小于比较运算符，[]下标运算符和随机移动（如“i+2”）。



### 应用举例

```cpp
#include<list>
#include<iostream>
#include<algorithm>
#include<stdlib.h>
using namespace std;
class A {
private:
	int n;
public:
	A(int n_) { n = n_; }
	friend bool operator<(const A & a1, const A& a2);
	friend bool operator==(const A & a1, const A& a2);
	friend ostream &operator<<( ostream  & o, const A& a);//重载输出操作符，为了与IO库保持一致，重载函数
	//应该把ostream& 作为其第一个参数，把类类型const对象的引用作为第二个参数，并返回对ostream形参的引用


};
bool operator<(const A &a1, const A &a2) {
	return a1.n < a2.n;
}//当容器中元素是标准类型（int float char)或者string时，可以直接使用这些函数模板。
//但如果是自己定义的类型或者需要按照其他方式排序，可以有两种方法来达到效果：
//一种是自己写比较函数。另一种是重载类型的'<'操作赋。
bool operator==(const A &a1, const A & a2) {
	return a1.n == a2.n;
}
ostream & operator<<(ostream &o, const A& a) {
	o << a.n;
	return o;
}
//定义函数模板，打印列表中的对象
template<class T>
void PrintList(const list<T> &lst) {
	int tmp = lst.size();
	if (tmp > 0) {
		typename list<T>::const_iterator i;//typename用来说明list<T>::const_isterator是个类型
		i = lst.begin();
		for (i = lst.begin(); i != lst.end(); i++)
			cout << *i << ",";//此处的cout<<调用了输出符重载
		for (i = lst.begin(); i != lst.end(); i++)
			cout << *i << ",";
	}
}
int main() {
	list<A>lst1, lst2;
	lst1.push_back(1);
	lst1.push_back(2);
	lst1.push_back(2);
	lst1.push_back(4);
	lst1.push_back(2);
	lst2.push_back(10); lst2.push_back(20); lst2.push_back(30); lst2.push_back(30);
	lst2.push_back(30); lst2.push_back(40); lst2.push_back(40);
	cout << "1)"; PrintList(lst1); cout << endl;
	cout << "2)"; PrintList(lst2); cout << endl;
	lst2.sort();//
	cout << "3)"; PrintList(lst2); cout << endl;
	lst2.pop_front();
	cout << "4)"; PrintList(lst2); cout << endl;
	lst1.remove(2);
	cout << "5)"; PrintList(lst1); cout << endl;
	lst1.unique();
	cout << "6)"; PrintList(lst1); cout << endl;
	lst1.merge(lst2);
	cout << "7)"; PrintList(lst1); cout << endl;
	cout << "8)"; PrintList(lst2); cout << endl;
	lst1.reverse();
	cout << "9)"; PrintList(lst1); cout << endl;
	lst2.push_back(100); lst2.push_back(200);
	lst2.push_back(300); lst2.push_back(400);
	list<A>::iterator p1, p2, p3;
	p1 = find(lst1.begin(), lst1.end(), 3);
	p2 = find(lst2.begin(), lst2.end(), 200);
	p3 = find(lst2.begin(), lst2.end(), 400);
	lst1.splice(p1, lst2, p2, p3);
	cout << "11)"; PrintList(lst1); cout << endl;
	cout << "12)"; PrintList(lst2); cout << endl;
	system("pause");
}
```



运行结果如下：

[![ZkCysH.md.png](https://s2.ax1x.com/2019/06/24/ZkCysH.md.png)](https://imgchr.com/i/ZkCysH)

## `deque`

- 双向**队列**
- `#include <deque>`
- 所用适用于`vector`的操作都适用于`deque`
- 特有的函数：`push_front()`, `pop_front()`



## 函数对象

如果一个类重载了运算符“`()`”则该类的对象就成为函数对象

### 函数对象的引用

#### 例1

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
//等价于：average.operator()(3,2,3)
```

#### 例2：`accumulate`源码

```c++
//版本一：
template<typename _InputIterator, typename _Tp>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init)
{
	for (; __first != __last; ++__first)
    {
		__init = __init + *__first;//进行累加工作
    }
  	return __init
}
//版本二：
template<typename _InputIterator, typename _Tp, typename _BinaryOperation>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _BinaryOPeartion __binary_op)
{
  	for (;__first != __last; __first++)
    {
      	__init = __binary_op(__init, *__first);
    }
  	return __init;
}
// _binary_op对应的实参可以是个函数，函数指针或函数对象
```

#### 例3：求n次方的和

```cpp
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

// 求power次方的函数对象的类模板
template<class T>
class SumPowers
{
private:
	int power;
public:
	SumPowers(int n) :power(n) {} //构造函数
	const T operator()(const T &total, const T &value)
	{//计算value的power次方，并加到total上面
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
	result = accumulate(v.begin(), v.end(), 0, SumPowers<int>(3));//函数对象
    //SumPowers:类模板
    //SumPowers<int>:模板类
    //SumPowers<int>(3):(临时)对象
	cout << "3)立方和：" << result << endl;
	result = accumulate(v.begin(), v.end(), 0, SumPowers<int>(4));
	cout << "4)四次方和：" << result << endl;
	return 0;
}
```

其中，经由

```cpp
int result = accumulate(v.begin(), v.end(), 0, SumSquares);
//注意：函数名字SumSquares可以和函数指针相匹配
```

实例化的过程如下：

```cpp
int accumulate(vector<int>::iterator first, vector<int>::iterator last, int init, int (*op)(int,int)) {
    for(;, first != last; ++first)
        init = op(init, *first); //函数指针在此相当于调用了SumSquares
    return init
}
```

而，经由

```cpp
result = accumulate(v.begin(), v.end(), 0, SumPowers<int>(3));
//最后一个为函数对象
```

实例化的过程如下：

```cpp
int accumulate(vector<int>::iterator first, vector<int>::iterator last, int init, int SumPowers<int>op) {
    for(;, first != last; ++first)
        init = op(init, *first); //op的成员变量是3
    return init
}
```

上述例子可以很好的说明函数对象的重要性。如果我们不适用函数对象，呢么对于不同的次数，我们需要写不同的求和函数，如`SumSquares`并分别加以调用。或者声明全局变量，对于不同的函数，修改全局变量的值借此达到不同函数功能的目的，但全局变量的使用违背了OOP的意义。



### 函数对象类模板

- `equal_to`
- `greater`
- `less`
- ...

头文件：`<functional>`

####  `greater` 的应用

原型

```cpp
template<class T>
struct greater:public binary_function<T, T, bool>//派生类
{
	bool operator()(const T &x, const T &y) const//重载圆括号成员函数
	{
		return x > y;//如果x>y返回值为True.
	}
}
//注意，对于一般的容器，如果返回值为True，则会认为X<Y
```

应用：用于`list`的`sort`带参数成员函数

`list`有两个`sort`成员函数：

- void sort();

  将list中的元素按“<”规定的比较方法升序排列

- template <class Compare>

  void sort(Compare op);

  将list中的元素按照op规定的比较方法升序排列。即要比较x,y大小时，看op(x,y)的返回值，为true则认为x小于y。

```cpp
#include <iostream>
#include <list>
#include <functional>
using namespace std;

class Myless
{
public:
	bool operator()(const int &c1, const int &c2)
	{
		return (c1 % 10) < (c2 % 10); //两个整数，谁的个位数小，谁就小
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
    //给出函数对象，用无参构造函数初始化
	Print(lst.begin(), lst.end());
	lst.sort(greater<int>());  // 从大到小排序
    //greater是个类模板
    //greater<int>类
    //greater<int>()生成一个临时函数对象
	Print(lst.begin(), lst.end());
	return 0;
}
```

**`Note:`**

## 在STL中使用自定义的“大”，“小”关系

关联容器和`STL`中的许多算法，都是可以使用函数或者函数对象自定义比较器的。在自定义了比较器`op`的情况下，以下三种说法是等价的：

1. x小于y
2. $op$(x,y)的返回值为True
3. y大于x