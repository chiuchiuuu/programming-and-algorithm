# 标准模板库 STL

## `pair`模板

```c++
template<class _T1, class _T2>
struct pair
{
  	typedef _T1 first_type;
  	typedef _T2 second_type;
  	_T1 first;
  	_T2 second;
  	pair():first(), second(){};
  	pair(const _T1 &__a, const _T2 &__b):first(__a), second(__b) {}
  	template<class _U1, class _U2>
    pair(const pair<_U1, _U2 &__p):first(__p.first), second(__p.second) {}
};
```





## `multiset`

- 内部元素有序排列
- 新元素插入的位置取决于它的值
- 查找速度快
- 允许有重复元素

原型

```c++
template<class Key, class Pred = less<Key>, class A = allocator<Key> >
class multiset
{
  	...
};
```

- `Pred`类型的变量决定了`multiset` 中的元素，“一个比另一个小”是怎么定义的。 `multiset`运行过程中，比较两个元素x,y的大小的做法，就是生成一个 `Pred`类型的 变量，假定为 `op`,若表达式`op(x,y)` 返回值为true,则 x比y小。 Pred的缺省类型是 `less<Key>`。

> `less`模板的定义
>
> ```c++
> template<class T>
> struct less : public binary_function<T, T, bool>
> {
> 	bool operator()(const T &x, const T &y) const
>     {
>     	return x < y;
>     }
> };
> ```

| 成员函数                                     | 作用                                       |
| ---------------------------------------- | ---------------------------------------- |
| `iterator find(const T &val)`            | 在容器中查找值为val的元素，返回其迭代器。如果找不到，返回end()。     |
| `iterator insert(const T & val);`        | 将val插入到容器中并返回其迭代器。                       |
| `void insert( iterator first,iterator last);` | 将区间[first,last)插入容器。                     |
| `iterator lower_bound(const T & val);`   | 查找一个最大的位置 it,使得[begin(),it) 中所有的元素都比 val 小。 |
| `iterator upper_bound(const T & val);`   | 查找一个最小的位置 it,使得[it,end()) 中所有的元素都比 val 大。 |
| `pair<iterator,iterator> equal_range(const T & val);` | 同时求得lower_bound和upper_bound。             |
| `iterator erase(iterator it);`           | 删除it指向的元素，返回其后面的元素的迭代器(Visual studio 2010上如此，但是在 C++标准和Dev C++中，返回值不是这样)。 |

插入元素时，multiset会将被插入元素和已有元素进行比较。由于less模板是用 < 进行 比较的，所以,这都要求对象能用 < 比 较，即适当重载了 <

应用程序

```c++
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
	bool operator()(const A &a1, const A &a2)
	{
		return (a1.n % 10) < (a2.n % 10);
	}
};

int main()
{
	const int SIZE = 6;
	A a[SIZE] = { 4,22,19,8,33,40 };
	multiset<A> m1; // 默认比较函数 less<A>
	m1.insert(a, a + SIZE);
	m1.insert(22);
	cout << "1)" << m1.count(22) << endl;
	cout << "2)";
	Print(m1.begin(), m1.end());
	multiset<A>::iterator i = m1.find(19);
	if (i != m1.end()) // true 表示找到
	{
		cout << "found" << endl;
	}
	cout << "3)" << *m1.lower_bound(22) << "," << *m1.upper_bound(22) << endl;
	i = m1.erase(m1.lower_bound(22), m1.upper_bound(22)); // 返回被删除元素的下一个元素的迭代器
	cout << "4)";
	Print(m1.begin(), m1.end());
	cout << "5)" << *i << endl;

	multiset<A, MyLess> m2;  // 自定义比较函数 MyLess
	m2.insert(a, a + SIZE);
	cout << "6)";
	Print(m2.begin(), m2.end());
	return 0;
}
```



## `set`

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
	set<int> myset(a, a + 5);
	pair<IT, bool> result;
	result = myset.insert(5);
	if (result.second)
	{
		cout << *result.first << " inserted" << endl;
	}
	if (myset.insert(5).second)
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





