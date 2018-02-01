# C++11与C++高级特性

## C++11新特性

### 统一的初始化方法

```c++
int arr[3]{1, 2, 3};
vector<int> iv{1, 2, 3};
map<int, string> mp{{1, "a"}, {2, "b"}};
string str{"Hello World"}; 
int *p = new int[20]{1,2,3};

struct A
{ 
  	int i,j; 
  	A(int m,int n):i(m),j(n) { }
};

A func(int m,int n )
{
  	return {m,n};
}

int main()
{
  	A *pa = new A{3,7};
}
```

### 成员变量默认初始值

### `auto`关键字

应用一：用于定义变量，编译器可以自动判断变量的类型

```c++
map<string, int greater<string> > mp;
for (auto i = mp.begin(); i != mp.end(); i++)
{
  	...
}
```

应用二：作为函数返回值，自动判断返回类型

```c++
template <class T1, class T2>
auto add(T1 x, T2 y)->decltype(x + y)
{
  	return x+y;
}
```

### `decltype`关键字

求表达式类型

### 智能指针`shared_ptr`

头文件 `<memory>`

通过`shared_ptr`的构造函数，可以让`shared_ptr`对象托管一个`new`运算符返回的指针，写法如下：

```c++
shared_ptr<T> ptr(new T);
```

此后`ptr`就可以像 `T*` 类型的指针一样来使用，即 `*ptr` 就是用`new`动态分配的 那个对象，而且不必操心释放内存的事.

- 多个`shared_ptr`对象可以同时托管一个指针，系统会维护一个托管计数。当 无`shared_ptr`托管该指针时，delete该指针。
- `shared_ptr`对象不能托管指向动态分配的数组的指针，否则程序运行会出错！！

使用例子

```c++
#include <memory>
#include <iostream>
using namespace std;

struct A {
	int n;
	A(int v = 0) :n(v) { }
	~A()
	{
		cout << n << " destructor" << endl;
	}
};

int main()
{
	shared_ptr<A> sp1(new A(2)); //sp1托管A(2)
	shared_ptr<A> sp2(sp1);  //sp2也托管A(2)
	cout << "1)" << sp1->n << "," << sp2->n << endl; //输出1)2,2
	shared_ptr<A> sp3;
	A *p = sp1.get();    //p 指向A(2)
	cout << "2)" << p->n << endl;
	sp3 = sp1; //sp3也托管A(2)
	cout << "3)" << (*sp3).n << endl; //输出 2 
	sp1.reset();  //sp1放弃托管A(2)
	if (!sp1)
	{
		cout << "4)sp1 is null" << endl; //会输出
	}
	A *q = new A(3);
	sp1.reset(q); // sp1托管q
	cout << "5)" << sp1->n << endl; //输出 3
	shared_ptr<A> sp4(sp1); //sp4托管A(3)
	shared_ptr<A> sp5;
	//sp5.reset(q); 不妥，会导致程序出错
	sp1.reset();   //sp1放弃托管A(3)
	cout << "before end main" << endl;
	sp4.reset();   //sp4放弃托管A(3)
	cout << "end main" << endl;
	return 0; //程序结束，会delete 掉A(2)
}
```

`sp5.reset(q)`：这个语句以普通指针做参数，运行时不会去判断`q`是否被其他`shared_ptr`所托管，所以当程序运行结束，`q`有可能被多次`delete`。

