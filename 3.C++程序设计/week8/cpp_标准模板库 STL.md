# 标准模板库 STL

## `pair`模板

```cpp
template<class _T1, class _T2>
struct pair
{
  	typedef _T1 first_type;
  	typedef _T2 second_type;
  	_T1 first;
  	_T2 second;
  	pair():first(), second(){};
    //无参构造函数
  	pair(const _T1 &__a, const _T2 &__b):first(__a), second(__b) {}
  	template<class _U1, class _U2>
    pair(const pair<_U1, _U2 &__p):first(__p.first), second(__p.second) {}
    //用函数模板进行初始化
};
```

- map/multimap 里放的都是`pair`模板类的对象，且按`first`从小到大排序

- 第三个构造函数用法示例：

  ```cpp
  pair<int, int>p(pair<double, double>(5.5, 4.6))`
  //p.first = 5
  //p.second = 4
  ```

  

  

## 关联容器

### `multiset`

- 内部元素有序排列
- 新元素插入的位置取决于它的值
- 查找速度快
- 允许有重复元素

原型

```cpp
template<class Key, class Pred = less<Key>, class A = allocator<Key> >
class multiset
{
  	...
};
//key决定了元素的类型
```

- `Pred`类型的变量决定了`multiset` 中的元素，“一个比另一个小”是怎么定义的。 `multiset`运行过程中，比较两个元素x,y的大小的做法，就是生成一个 `Pred`类型的变量，假定为 `op`,若表达式`op(x,y)` 返回值为true,则 x比y小。 Pred的缺省类型是 `less<Key>`。`op`可以是一个函数名字，函数指针或者函数对象，大多数情况下为函数对象。当其为函数对象是，`op(x,y)`是调用`op`这个对象的operator()成员函数。

> `less`模板的定义
>
> ```cpp
> template<class T>
> struct less : public binary_function<T, T, bool>
> {
> 	bool operator()(const T &x, const T &y) const
>  {
>  	return x < y;
>  }
> };//less模板是靠<来比较大小的
> ```

| 成员函数                                              | 作用                                                         |
| ----------------------------------------------------- | :----------------------------------------------------------- |
| `iterator find(const T &val)`                         | 在容器中查找值为val的元素，返回其迭代器。如果找不到，返回end()。注意此处的等于并不是直接使用`==`而是`x<y`与`y<x`同时不成立 |
| `iterator insert(const T & val);`                     | 将val插入到容器中并返回其迭代器。                            |
| `void insert( iterator first,iterator last);`         | 将区间`[first,last)`插入容器。                               |
| `iterator lower_bound(const T & val);`                | 查找一个最大的位置 it,使得`[begin(),it)` 中所有的元素都比 val 小。 |
| `iterator upper_bound(const T & val);`                | 查找一个最小的位置 it,使得`[it,end())` 中所有的元素都比 val 大。 |
| `pair<iterator,iterator> equal_range(const T & val);` | 同时求得`lower_bound`和`upper_bound`。注意返回值pair类模板的 |
| `iterator erase(iterator it);`                        | 删除it指向的元素，返回其后面的元素的迭代器(Visual studio 2010上如此，但是在 C++标准和Dev C++中，返回值不是这样)。 |
| int count(const T &val)                               | 统计有多少个元素的值和val相等                                |

插入元素时，multiset会将被插入元素和已有元素进行比较。由于less模板是用 < 进行 比较的，所以,这都要求对象能用 < 比 较，即适当重载了 <。注意，`find` `insert` `upper_bound` `lower_bound`的时间复杂度都是`log(n)`。而`insert(区间)`的时间复杂度为`O(nlogn)`

应用程序

```cpp
#include <iostream>
#include <set>
using namespace std;

template<class T>
void Print(T first, T last)
{
	for (; first != last; first++)
	{
		cout << *first << " ";
	}
	cout << endl;
}

class A
{
private:
	int n;
public:
	A(int n_) :n(n_) {}
	friend bool operator<(const A &a1, const A &a2)
	{
		return a1.n < a2.n; 
	}
	friend ostream &operator<<(ostream &o, const A &a)
	{
		o << a.n;
		return o;
	}
	friend class MyLess;
};

// 自定义比较对象函数
struct MyLess
{
	bool operator()(const A &a1, const A &a2)//重载圆括号
	{
		return (a1.n % 10) < (a2.n % 10);
        //按个位数比大小
	}
};

typedef multiset<A> MEST1; //MEST1用`<`比大小
typedef multiset<A,MyLess> MEST2; //MEST2用MyLess::operator()比较大小
int main()
{
	const int SIZE = 6;
	A a[SIZE] = { 4,22,19,8,33,40 };
	MEST1 m1; // 默认比较函数 less<A>
	m1.insert(a, a + SIZE);
	m1.insert(22);
	cout << "1)" << m1.count(22) << endl;
	cout << "2)";
	Print(m1.begin(), m1.end());
	MEST1::iterator i = m1.find(19);
	if (i != m1.end()) // true 表示找到
	{
		cout << "found" << endl;
	}
	cout << "3)" << *m1.lower_bound(22) << "," << *m1.upper_bound(22) << endl;
    //通过*把迭代器对应的元素
	i = m1.erase(m1.lower_bound(22), m1.upper_bound(22)); // 返回被删除元素的下一个元素的迭代器
	cout << "4)";
	Print(m1.begin(), m1.end());
	cout << "5)" << *i << endl;

	MEST2 m2;  // 自定义比较函数 MyLess
	m2.insert(a, a + SIZE);
	cout << "6)";
	Print(m2.begin(), m2.end());
	return 0;
}
```



### `set`

原型

```c++
template<class Key, class Pred = less<Key>, class A = allocator<Key> >
class set
{
  	...
}
```

- 不允许有重复元素，故插入已有元素时忽略插入（`insert`返回一个 `pair`）

```c++
#include <iostream>
#include <set>
using namespace std;

int main()
{
	typedef set<int>::iterator IT;
	int a[5] = { 3,4,6,1,2 };
	set<int> myset(a, a + 5);//st: 1 2 3 4 6
	pair<IT, bool> result;
	result = myset.insert(5);
	if (result.second) //插曲成功则输出被插入的元素
	{
		cout << *result.first << " inserted" << endl;
	}
	if (myset.insert(5).second) //再次尝试插入5
	{
		cout << *result.first << endl;
	}
	else
	{
		cout << *result.first << " already exists" << endl;
	}
	pair<IT, IT> bounds = myset.equal_range(4);
	cout << *bounds.first << "," << *bounds.second << endl;
	return 0;
}
```



### `multimap`

- `multimap`中的元素由 `<关键字， 值>`组成，每个元素都是一个`pair`模板类的**对象**，关键字就是`first`，其类型为`Key`
- `multimap` 中允许多个元素的关键字相同。元素按照`first`成员变量从小到大 排列，缺省情况下用 `less<Key>` 定义关键字的“小于”关系。
- 元素的first成员变量不能被修改

原型

```cpp
template<class Key, class T, class Pred = less<Key>, class A = allocator<T> >
class multimap
{
  	...
    typedef pair<const Key, T> value_type;
  	...
};
```

示例

```cpp
#include <iostream>
#include <map>
using namespace std;

int main()
{
	typedef multimap<int, double, less<int> > mmid;
	mmid pairs;
	cout << "1)" << pairs.count(15) << endl;//关键字等于15.输出0
	pairs.insert(mmid::value_type(15, 2.7));
    //mmid::value_type 把key替换成int, T替换成double,得到pair模板类。后面的参数对应构造函数，生成临时的对象。
    //typedef pair<const key, T>value_type;
    //要插入的元素必定是pair模板类的对象
    // pair<const Key, T>
	pairs.insert(mmid::value_type(15, 99.3));
    //Multimap允许有多个元素的first相同
	cout << "2)" << pairs.count(15) << endl;
	pairs.insert(mmid::value_type(30, 111.11));
	pairs.insert(mmid::value_type(10, 22.22));
	pairs.insert(mmid::value_type(25, 33.333));
	pairs.insert(mmid::value_type(20, 9.3));

	for (mmid::const_iterator i = pairs.begin(); i != pairs.end(); i++)
	{
		cout << "(" << i->first << "," << i->second << ")" << ",";
	}
	return 0;
}
```

关联容器很适合用于需要不断地更新数据，不断地在数据里面进行查询的过程。因为其在查询或者增删时，时间的复杂度均为`O(log(n))`.

```cpp
#include<iostream>
#include<map>
#include<string>
using namespace std;
class  CStudent
{
public:
	struct CInfo //类的内部还可以定义类
	{
		int id;
		string name;
	};
	int score;
	CInfo info;//CInfo类型的对象作为成员变量
};

typedef multimap<int, CStudent::CInfo> MAP_STD;
int main() {
	MAP_STD mp;
	CStudent st;
	string cmd;
	while (cin >> cmd) {
		if (cmd == "Add") {
			cin >> st.info.name >> st.info.id >> st.score;
			mp.insert(MAP_STD::value_type(st.score, st.info));//pair模板类的对象来存放信息
    
		}
		else if(cmd == "Query")
		{
			int score;
			cin >> score;
			MAP_STD::iterator p = mp.lower_bound(score);
			if (p != mp.begin()) {//若为begin，说明查找不到
				--p; //返回值为左闭右开
				score = p->first;//比要查询分数低的最高分
				MAP_STD::iterator maxp = p;
				int maxid = p->second.id;
				for (; p != mp.begin() && p->first == score; --p) {
					if (p->second.id > maxid) {
						maxp = p;
						maxid = p->second.id;
					}
				}
				if (p->first == score) {
				//如果上面的循环是因为p==mp.begin()而停止，则p指向的元素也要被处理}
				//如果上面的循环是因为p==mp.begin()而停止，则p指向的元素也要被处理
					if (p->second.id > maxid) {
						maxp = p;
						maxid = p->second.id;
					}
				}
				cout << maxp->second.name << " " << maxp->second.id << " " << maxp->first << endl;
			}
			else
				cout << "Nobodz" << endl;
		}
	}
	return 0;
}
```

注意，

```cpp
mp.insert(MAP_STD::value_type(st.score, st.info));
//也可以写作：
mp.insert(make_pair(st.score,st.info));
```

`make_pair`返回值是`pair`模板类

### `map`

- 关键字`first`各不相同

- 若pairs为map模板类的对象，`pairs[key]`返回对关键字等于`key`的元素的值(`second`成员变量）的**引用**。若没有关键字为`key`的元素，则会往`pairs`里插入一个关键字为`key`的元素，其值用无参构造函数初始化，并返回其值的引用.

  ```cpp
  map<int,double> pairs;
  pairs[50] = 5; //会修改pairs中关键字为50的元素，使其值变为50
  //若不存在关键字等于50的元素，则插入此元素，并使其值为5
  ```

  

示例

```c++
#include <iostream>
#include <map>
using namespace std;

template <class Key, class Value> 
ostream& operator<<(ostream &o, const pair<Key, Value> &p)
{
	o << "(" << p.first << "," << p.second << ")";
	return o;
}

int main()
{
	typedef map<int, double, less<int> > mmid;//两个>>之间最好写一个空格，避免编译器无法识别
	mmid pairs;
	cout << "1) " << pairs.count(15) << endl;
	pairs.insert(mmid::value_type(15, 2.7));
	pairs.insert(make_pair(15, 99.3)); //make_pair生成一个pair对象
	cout << "2) " << pairs.count(15) << endl;
	pairs.insert(mmid::value_type(20,9.3));//如何判定insert是否成功，可以自己定义pair<interator,bool>
	mmid::iterator i;
	cout << "3) ";
	for (i = pairs.begin(); i != pairs.end(); i++)
	{
		cout << *i << ",";
	}
	cout << endl;
	cout << "4) ";
	int n = pairs[40];//如果没有关键字为40的元素，则插入一个.
    //其中第二个元素由无参构造函数进行初始化
	for (i = pairs.begin(); i != pairs.end(); i++)
	{
		cout << *i << ",";
	}
	cout << endl;
	cout << "5) ";
	pairs[15] = 6.28; //把关键字为15的元素值改成6.28
	for (i = pairs.begin(); i != pairs.end(); i++)
	{
		cout << *i << ",";
	}
	return 0;
}
```



## 容器适配器

- 可以用某种顺序容器来实现 (让已有的顺序容器以栈/队列的方式工作)
- 容器适配器上没有迭代器：STL中各种排序, 查找, 变序等算法都不适合容器适配器
- 都有三个成员函数：push,top,pop

### `stack`

- `stack` 是**后进先出**的数据结构
- 只能插入, 删除, 访问栈顶的元素
- 可用 `vector`, `list`, `deque`来实现
  - 缺省情况下, 用`deque`实现 
  - 用 `vector`和`deque`实现比用`list`实现性能好

原型

```c++
template<class T, class Cont = deque<T> > // 存储数据类型 T， 用deque实现
class stack
{
  	...
}
```

| 成员函数                 | 作用                                                         |
| ------------------------ | ------------------------------------------------------------ |
| `void push(const T &x);` | 将x压入栈顶                                                  |
| `void pop();`            | 弹出(即删除)栈顶元素                                         |
| `T& top();`              | 返回栈顶元素的引用. 通过该函数, 可以读取栈顶元素的值, 也可以修改栈顶元素 |



### `queue`

- 和`stack` 基本类似，可以用 `list`和`deque`实现
- 缺省情况下用`deque`实现
- 先进先出

原型

```c++
template<class T, class Cont = deque<T> >
class queue
{
	...
}
```

| 成员函数                 | 作用                                                         |
| ------------------------ | ------------------------------------------------------------ |
| `void push(const T &x);` | 将x加入队尾                                                  |
| `void pop();`            | 弹出(即删除)队头元素                                         |
| `T& top();`              | 返回队头元素的引用. 通过该函数, 可以读取队头 元素的值, 也可以修改队头元素 |



### `priority_queue`

- 和 `queue`类似, 可以用`vector`和`deque`实现

- 缺省情况下用`vector`实现

- `priority_queue` 通常用**堆排序**技术实现, 保证最大的元素总是在最前面 （其他元素不一定完全有序）

  - 执行`pop`操作时, 删除的是最大的元素

  - 执行`top`操作时, 返回的是最大元素的引用 
  
- 默认的元素比较器是 `less<T>`，需要保证能使用`<`进行比较

- 最高优先级的元素总是第一个出列

- 适用于不停地取最大元素

  



## STL算法

STL中的算法大致可以分为以下七类: 

- 不变序列算法
- 变值算法
- 删除算法 
- 变序算法
- 排序算法
- 有序区间算法
- 数值算法

大多重载的算法都是有两个版本的 

- 用 “==” 判断元素是否相等, 或用 “<” 来比较大小
- 多出一个类型参数 `Pred`和函数形参 `Pred op` : 通过表达式 `op(x,y)`的返回值: `ture/false` 判断x是否 “等于” y，或者x是否 “小于” y

### 不变序列算法

- 该类算法不会修改算法所作用的容器或对象
- 适用于顺序容器和关联容器
- 时间复杂度都是O(n)，因为往往会遍历元素

| 算法                    | 功能                                                         |
| ----------------------- | ------------------------------------------------------------ |
| min                     | 求两个对象中较小的(可自定义比较器)                           |
| max                     | 求两个对象中较大的(可自定义比较器)                           |
| min_element             | 求区间中的最小值(可自定义比较器)                             |
| max_element             | 求区间中的最大值(可自定义比较器)                             |
| for_each                | 对区间中的每个元素都做某种操作                               |
| count                   | 计算区间中等于某值的元素个数`==`                             |
| count_if                | 计算区间中符合某种条件的元素个数                             |
| **find**                | 在区间中查找等于某值的元素`==`                               |
| find_if                 | 在区间中查找符合某条件的元素                                 |
| find_end                | 在区间中查找另一个区间最后一次出现的位 置(可自定义比较器)    |
| find_first_of           | 在区间中查找第一个出现在另一个区间中的 元素 (可自定义比较器) |
| adjacent_find           | 在区间中寻找第一次出现连续两个相等元素 的位置(可自定义比较器) |
| search                  | 在区间中查找另一个区间第一次出现的位置(可 自定义比较器)      |
| search_n                | 在区间中查找第一次出现等于某值的连续n个元 素(可自定义比较器) |
| equal                   | 判断两区间是否相等(可自定义比较器)                           |
| mismatch                | 逐个比较两个区间的元素，返回第一次发生不 相等的两个元素的位置(可自定义比较器) |
| lexicographical_compare | 按字典序比较两个区间的大小(可自定义比较器)                   |

#### find

```cpp
template<class InIt, class T>
InIt find(InIt first, InIt last, const T &val);
```

- 返回区间 [first,last) 中的迭代器`i`，使得 `*i == val`。如果没找到，返回`last`

#### find_if

```c++
template<class InIt, class Pred>
InIt find_if(InIt first, InIt last, Pred pr);
```

- 返回区间 [first,last) 中的迭代器`i`, 使得 `pr(*i) == true`

#### for_each

```c++
template<class InIt, class Fun>
Fun for_each(InIt first, InIt last, Fun f);
```

- 对[first, last)中的每个元素`e`, 执行`f(e)`, 要求 `f(e)`不能改变`e`

#### count

```c++
template<class InIt, class T>
size_t count(InIt first, InIt last, const T &val);
```

- 计算[first, last) 中等于`val`的元素个数(`x==y`为true算等于)

#### count_if

```c++
template<class InIt, class Pred>
size_t count_if(InIt first, InIt last, Pred pr);
```

- 计算[first, last) 中符合`pr(e) == true` 的元素e的个数

#### min_element

```c++
template<class FwdIt>
FwdIt min_element(FwdIt first, FwdIt last);
```

- 返回[first,last) 中最小元素的迭代器, 以 `<` 作比较器
- 最小指没有元素比它小, 而不是它比别的不同元素都小，因为即便`a!= b`, `a<b` 和`b<a`有可能都不成立

#### max_element

```c++
template<class FwdIt>
FwdIt max_element(FwdIt first, FwdIt last);
```

- 返回[first,last) 中最大元素(不小于任何其他元素)的迭代器
- 以 `<` 作比较器





### 变值算法

- 此类算法会修改源区间或目标区间元素的值
- 值被修改的那个区间, 不可以是属于关联容器的（因为关联容器是有序的）

| 算法            | 功能                                                         |
| --------------- | ------------------------------------------------------------ |
| for_each        | 对区间中的每个元素都做某种操作                               |
| copy            | 复制一个区间到别处                                           |
| copy_backward   | 复制一个区间到别处, 但目标区前是从后往前 被修改的            |
| transform       | 将一个区间的元素变形后拷贝到另一个区间                       |
| swap_ranges     | 交换两个区间内容                                             |
| fill            | 用某个值填充区间                                             |
| fill_n          | 用某个值替换区间中的n个元素                                  |
| generate        | 用某个操作的结果填充区间                                     |
| generate_n      | 用某个操作的结果替换区间中的n个元素                          |
| replace         | 将区间中的某个值替换为另一个值                               |
| replace_if      | 将区间中符合某种条件的值替换成另一个值                       |
| replace_copy    | 将一个区间拷贝到另一个区间，拷贝时某个值 要换成新值拷过去    |
| replace_copy_if | 将一个区间拷贝到另一个区间，拷贝时符合某 条件的值要换成新值拷过去 |

#### transform

```c++
template<class InIt, class OutIt, class Unop>
OutIt transform(InIt first, InIt last, OutIt x, Unop uop);
```

- 对[first,last)中的每个迭代器I, 
  - 执行 `uop(*I);` 并将结果依次放入从 x 开始的地方
  - 要求 `uop(*I)` 不得改变 `*I` 的值
- 本模板返回值是个迭代器, 即 `x + (last - first)`
  -  x可以和 first相等

#### copy

原型

```c++
template<class InIt, class OutIt>
OutIt copy(InIt first, InIt last, OutIt x);
```

- 本函数对每个在区间[0, last - first)中的N执行一次 `*(x+N) = *(first + N)` 返回 x + N

源代码（简化）

```c++
template<class _II, class _OI> 
inline _OI copy(_II _F, _II _L, _OI _X)
{
	for (; _F != _L; ++_X, ++_F) 
      	*_X = *_F; 
  	return (_X);
}
```

##### copy的特殊用法

```c++
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

// 编写My_ostream_iterator，使得main函数中的copy实现输出
template<class T>
class My_ostream_iterator :public iterator<output_iterator_tag, T>
{
private:
	string sep; // 分隔符
	ostream &os; // 有些ostream对象的构造函数是有参的，所以用引用比较方便
public:
	My_ostream_iterator(ostream &o, string s) :sep(s), os(o) {}
	void operator++() {}
	My_ostream_iterator& operator*()
	{
		return *this;
	}
	My_ostream_iterator& operator=(const T &val)
	{
		os << val << sep;
		return *this;
	}
};

int main()
{
	int a[4] = { 1,2,3,4 };
	My_ostream_iterator<int> oit(cout, "*");
	copy(a, a + 4, oit); //输出 1*2*3*4*
	ofstream oFile("text.txt", ios::out);
	My_ostream_iterator<int> oitf(oFile, "*");
	copy(a, a + 4, oitf);  //向test.txt文件中写入 1*2*3*4*
	oFile.close();
	return 0;
}

```

#### 变值算法示例

```c++
#include <iostream>
#include <vector>
#include <numeric>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

class LessThen9
{
public:
	bool operator()(int n)
	{
		return n < 9;
	}
};

void ouputSquare(int value)
{
	cout << value * value << " ";
}

int calculateCube(int value)
{
	return value * value * value;
}

int main()
{
	const int SIZE = 10;
	int a1[] = { 1,2,3,4,5,6,7,8,9,10 };
	int a2[] = { 100,2,8,1,50,3,8,9,10,2 };
	vector<int> v(a1, a1 + SIZE);
	ostream_iterator<int> output(cout, " ");
	random_shuffle(v.begin(), v.end());  // 随机变换顺序（伪随机）
	cout << endl << "1)";
	copy(v.begin(), v.end(), output);  // 相当于做一串输出
	copy(a2, a2 + SIZE, v.begin());
	cout << endl << "2)";
	cout << count(v.begin(), v.end(), 8);
	cout << endl << "3)";
	cout << count_if(v.begin(), v.end(), LessThen9());
	cout << endl << "4)";
	cout << *(min_element(v.begin(), v.end()));
	cout << endl << "5)";
	cout << *(max_element(v.begin(), v.end()));
	cout << endl << "6)";
	cout << accumulate(v.begin(), v.end(), 0);  // 求和
	cout << endl << "7)";
	for_each(v.begin(), v.end(), ouputSquare);
	vector<int> cubes(SIZE);
	transform(a1, a1 + SIZE, cubes.begin(), calculateCube);
	cout << endl << "8)";
	copy(cubes.begin(), cubes.end(), output);
	return 0;
}
```

- `ostream_iterator<int> output(cout ,“ ”); `定义了一个 `ostream_iterator<int>` 对象, 可以通过`cout`输出以 “ ”(空格) 分隔的一个个整数
- `copy (v.begin(), v.end(), output);` 导致v的内容在 `cout`上输出



### 删除算法

- 删除一个容器里的某些元素
- **删除不会使容器里的元素减少**
  - 将所有应该被删除的元素看做空位子
  - 用留下的元素从后往前移, 依次去填空位子
  - 元素往前移后, 它原来的位置也就算是空位子 
  - 也应由后面的留下的元素来填上
  - 最后, 没有被填上的空位子, 维持其原来的值不变
- 删除算法不应作用于关联容器

| 算法           | 功能                                                         |
| -------------- | ------------------------------------------------------------ |
| remove         | 删除区间中等于某个值的元素                                   |
| remove_if      | 删除区间中满足某种条件的元素                                 |
| remove_copy    | 拷贝区间到另一个区间. 等于某个值的元素不拷贝                 |
| remove_copy_if | 拷贝区间到另一个区间. 符合某种条件的元素不拷贝               |
| unique         | 删除区间中连续相等的元素, 只留下一个(可自定义比较器)         |
| unique_copy    | 拷贝区间到另一个区间. 连续相等的元素, 只拷贝第一个到目 标区间 (可自定义比较器) |

- 复杂度都是 $O(n)$

#### unique

原型1

```c++
template<class FwdIt>
FwdIt unique(FwdIt first, FwdIt last);
```

- 用 `==` 比较是否等

原型2

```c++
template<class FwdIt, class Pred>
FwdIt unique(FwdIt first, FwdIt last, Pred pr);
```

- 用 `pr (x,y)`为 true说明x和y相等
- 对[first,last) 这个序列中连续相等的元素, 只留下第一个
- 返回值是迭代器, 指向元素删除后的区间的最后一个元素的后面



### 变序算法

- 变序算法改变容器中元素的顺序
- 但是不改变元素的值
- 变序算法不适用于关联容器
- 算法复杂度都是 $O(n)$的

| 算法             | 功能                                                         |
| ---------------- | ------------------------------------------------------------ |
| reverse          | 颠倒区间的前后次序                                           |
| reverse_copy     | 把一个区间颠倒后的结果拷贝到另一个区间， 源区间不变          |
| rotate           | 将区间进行循环左移                                           |
| rotate_copy      | 将区间以首尾相接的形式进行旋转后的结果 拷贝到另一个区间，源区间不变 |
| next_permutation | 将区间改为下一个排列(可自定义比较器)                         |
| prev_permutation | 将区间改为上一个排列(可自定义比较器)                         |
| random_shuffle   | 随机打乱区间内元素的顺序                                     |
| partition        | 把区间内满足某个条件的元素移到前面，不满足该 条件的移到后面  |

#### stable_partition

- 把区间内满足某个条件的元素移到前面 
- 不满足该条件的移到后面 
- 而对这两部分元素, 分别保持它们原来的先后次序不变

#### random_shuffle

原型

```c++
template<class RanIt>
void random_shuffle(RanIt first, RanIt last);
```

- 随机打乱[first,last) 中的元素, 适用于能随机访问的容器

#### reverse

原型

```c++
template<class BidIt>
void reverse(BidIt first, BidIt last);
```

- 颠倒区间[first,last)顺序

#### next_permutation

原型

```c++
template<class InIt> 
bool next_permutaion (Init first,Init last);
```

- 求下一个排列

示例

```c++
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	string str = "231";
	char szStr[] = "324";
	while (next_permutation(str.begin(), str.end()))
	{
		cout << str << endl;
	}
	cout << "****" << endl;
	while (next_permutation(szStr, szStr + 3))
	{
		cout << szStr << endl;
	}
	sort(str.begin(), str.end());
	cout << "****" << endl;
	while (next_permutation(str.begin(), str.end()))
	{
		cout << str << endl;
	}
	return 0;
}
```



### 排序算法

- 比前面的变序算法复杂度更高, 一般是 $O(n\log(n))$ 
- 排序算法需要随机访问迭代器的支持 
- 不适用于关联容器和list

| 算法              | 功能                                                         |
| ----------------- | ------------------------------------------------------------ |
| sort              | 将区间从小到大排序(可自定义比较器)                           |
| stable_sort       | 将区间从小到大排序, 并保持相等元素间的相对次序(可自定义比较器) |
| partial_sort      | 对区间部分排序, 直到最小的n个元素就位(可自定义比较器)        |
| partial_sort_copy | 将区间前n个元素的排序结果拷贝到别处, 源区间不变(可自定义比较器) |
| nth_element       | 对区间部分排序, 使得第n小的元素(n从0开始算)就位, 而且比 它小的都在它前面, 比它大的都在它后面(可自定义比较器) |
| make_heap         | 使区间成为一个“堆”(可自定义比较器)                           |
| push_heap         | 将元素加入一个是“堆”区间(可自定义比较器)                     |
| pop_heap          | 从“堆”区间删除堆顶元素(可自定义比较器)                       |
| sort_heap         | 将一个“堆”区间进行排序，排序结束后，该区间就是普 通的有序区间，不再是 “堆”了(可自定义比较器) |

#### sort

原型1

```c++
template<class RanIt>
void sort(RanIt first, RanIt last);
```

- 按升序排序
- 判断x是否应比y靠前, 就看 x < y 是否为true

原型2

```c++
template<class RanIt, class Pred>
void sort(RanIt first, RanIt last, Pred pr);
```

- 按升序排序
- 判断x是否应比y靠前, 就看 `pr(x,y)`是否为true

sort 实际上是快速排序, 时间复杂度 $O(n\log(n)) $

- 平均性能最优 
- 但是最坏的情况下, 性能可能非常差

如果要保证 “最坏情况下” 的性能, 那么可以使用 `stable_sort `

- `stable_sort `实际上是归并排序, 特点是能保持相等元素之间的先后次序
- 在有足够存储空间的情况下, 复杂度为 $n\log(n)$, 否则复杂度为 $n\log(n)\log(n)$
- `stable_sort` 用法和 `sort`相同。



### 有序区间算法

- 要求所操作的区间是已经从小到大排好序的
- 需要随机访问迭代器的支持
- 有序区间算法不能用于关联容器和list

| 算法                     | 功能                                           |
| ------------------------ | ---------------------------------------------- |
| binary_search            | 判断区间中是否包含某个元素                     |
| includes                 | 判断是否一个区间中的每个元素，都在另一个区间中 |
| lower_bound              | 查找最后一个不小于某值的元素的位置             |
| upper_bound              | 查找第一个大于某值的元素的位置                 |
| equal_range              | 同时获取lower_bound和upper_bound               |
| merge                    | 合并两个有序区间到第三个区间                   |
| set_union                | 将两个有序区间的并拷贝到第三个区间             |
| set_intersection         | 将两个有序区间的交拷贝到第三个区间             |
| set_difference           | 将两个有序区间的差拷贝到第三个区间             |
| set_symmetric_difference | 将两个有序区间的对称差拷贝到第三个区间         |
| inplace_merge            | 将两个连续的有序区间原地合并为一个有序区间     |

#### binary_search

- 折半查找
- 要求容器已经有序且支持随机访问迭代器, 返回是否找到

原型1

```c++
template<class FwdIt, class T>
  bool binary_search(FwdIt first, FwdIt last, const T& val);
```

- 比较两个元素x, y 大小时, 看 x < y

原型2

```c++
template<class FwdIt, class T, class Pred>
bool binary_search(FwdIt first, FwdIt last, const T& val, Pred pr);
```

- 比较两个元素x, y 大小时, 若 `pr(x,y)` 为true, 则 认为x小于y

#### lower_bound

```c++
template<class FwdIt, class T>
FwdIt lower_bound(FwdIt first, FwdIt last, const T& val);
```

- 要求[first,last)是有序的 
- 查找[first,last)中的, 最大的位置 FwdIt, 使得[first,FwdIt) 中所有的元素都比 val 小

#### equal_range

```c++
template<class FwdIt, class T>
pair<FwdIt, FwdIt> equal_range(FwdIt first, FwdIt last, const T& val);
```

- 要求[first,last)是有序的
- 返回值是一个pair, 假设为 p, 则：
  -  [first,p.first) 中的元素都比 val 小
  -  [p.second,last)中的所有元素都比 val 大
  -  p.first 就是lower_bound的结果 
  -  p.last 就是 upper_bound的结果

### merge

- 把[first1,last1), [ first2,last2) 两个升序序列合并, 形成第 3 个升序序列, 第3个升序序列以 x 开头

原型1

```c++
template<class InIt1, class InIt2, class OutIt>
OutIt merge(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt x);
```

- 用 < 作比较器

原型2

```c++
template<class InIt1, class InIt2, class OutIt, class Pred>
OutIt merge(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt x, Pred pr);
```

- 用 pr 作比较器

#### includes

```c++
template<class InIt1, class InIt2> 
bool includes(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2);
```

```c++
template<class InIt1, class InIt2, class Pred> 
bool includes(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, Pred pr);
```

#### set_difference

- 求出[first1,last1)中, 不在[first2,last2)中的元素, 放到从 x 开始的地方 
- 如果 [first1,last1) 里有多个相等元素不在[first2,last2)中, 则这多个元素也都会被放入x代表的目标区间里

```c++
template<class InIt1, class InIt2, class OutIt>
OutIt set_difference(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt x);
```

```c++
template<class InIt1, class InIt2, class OutIt, class Pred> 
OutIt set_difference(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, OutIt x, Pred pr);
```

#### set_intersection

- 求出[first1,last1)和[first2,last2)中共有的元素, 放到从x开始的 地方
- 若某个元素e 在[first1,last1)里出现 n1次, 在[first2,last2)里出 现n2次, 则该元素在目标区间里出现min(n1,n2)次

#### set_union

- 求两个区间的并, 放到以 x开始的位置 
- 若某个元素e 在[first1,last1)里出现 n1次, 在[first2,last2)里 出现n2次, 则该元素在目标区间里出现max(n1,n2)次



## bitset

```c++
template<size_t N>
class bitset
{
  	...
};
```

实际使用的时候，N是个整型常数，如:

- `bitset<40> bst;`
- `bst`是一个由40位组成的对象 
- 用bitset的函数可以方便地访问任何一位

众多成员函数见PPT