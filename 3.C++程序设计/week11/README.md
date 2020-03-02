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

应用一：用于定义变量，编译器可以自动判断变量的类型，但需要对变量进行初始化

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

类型判别，求表达式类型

```cpp
int i;
decltype(i) x1; // x1 is int
struct A {double x;};
const A* a = new A();

decltype(a->x) x3; // x3 is double
decltype((a->x)) x4; // x4 is double& !!!注意带了括号之后是引用
```



### 智能指针`shared_ptr`

头文件 `<memory>`

通过`shared_ptr`的构造函数，可以让`shared_ptr`对象托管一个`new`运算符返回的指针，写法如下：

```c++
shared_ptr<T> ptr(new T);
```

此后`ptr`就可以像 `T*` 类型的指针一样来使用，即 `*ptr` 就是用`new`动态分配的 那个对象，而且不必操心释放内存的事，即程序结束或对象消亡时，会自动处理内存。

- 多个`shared_ptr`对象可以同时托管一个指针（new操作得到的指针，否则delete会出错），系统会维护一个托管计数。当 无`shared_ptr`托管该指针时，delete该指针。
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
    // 对一个shared_ptr管理的指针，可以用get()获得其指向的对象
	A *p = sp1.get();    //p 指向A(2)
	cout << "2)" << p->n << endl;
	sp3 = sp1; //sp3也托管A(2)
	cout << "3)" << (*sp3).n << endl; //输出 2 
	sp1.reset();  //sp1放弃托管A(2)
	if (!sp1)//判断是否有托管的指针
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
	sp4.reset();   //sp4放弃托管A(3)，此时A(3)会被自动delete掉 
    // 输出 "destructor"
	cout << "end main" << endl;
	return 0; //程序结束，会delete 掉A(2)
}
```

`sp5.reset(q)`：这个语句以普通指针做参数，运行时不会去判断`q`是否被其他`shared_ptr`所托管，所以当程序运行结束，`q`有可能被多次`delete`。

### 空指针nullptr

```cpp
#include<memory>
#include<iostream>
using namespace std;
int main()
{
    int *p1 = NULL;
    int *p2 = nullptr;
    shared_ptr<double> p3= nullptr;
    if(p1==p2);//true
    if(p3==nullptr);//true
    if(p3==p2);//error, 两者类型不同
    if(p3==NULL);//true
    bool b = nullptr; //b=false
    int i = nullptr;//error. nullptr不能自动转为整型
}
```



### 基于范围的for循环 

### 右值引用和move语义

一般来说，不能取地址的表达式，就是右值，能取地址的，就是左值。

```cpp
class A{};
A &r= A(); //error. A()是临时变量，无名变量，是右值；
A &&r= A(); //ok. r是右值引用。
```

主要目的是提高程序运行的效率，减少需要进行深拷贝的对象进行深拷贝的次数。

```cpp
class String
{
public:
    char* str;//指向动态分配的存储空间
    String(): str(new char[1]){str[0]=0;} //指向一个空串
    String(const char* s){
        str = new char[strlen(s)+1];
        strcpy(str,s);
    }
    String(const String &S) {
        cout<<"copy constructor called"<<endl;
        str = new char[strlen(s.str) +1];
        strcpy(str, s.str);
    }//复制，深拷贝
    // 复制构造函数
    String & operator= (const String &S) {
        cout<< "copy operator= called"<<endl;
        if(str!= s.str)
        {
            delete [] str;
            str = new char[strlen(s.str) + 1];
            strcpy(str, s.str);
        }
        return *this;
    }
    // move constructor
    String(String && s): str(s.str) { //让str指向s.str
        cout<<" move constructor called"<<endl;
        s.str = new char[1]; //让原有的s.str指向空串
        s.str[0] = 0;
    }
    // move assignment
    String & operator= (String &&s) {
        cout<<"move opertaor= called"<<endl;
        if(str != s.str) {
            delete [] str;
            str = s.str;
            s.str = new char[1];
            s.str[0] =0 ;
        }
        return *this;
    }
    ~String(){ delete []str;}      
};

template<class T>
void MoveSwap(T &a, T &b) {
    // move()作用：把一个左值变成右值
    T tmp(move(a));// std::move(a)为右值，这里会调用move constructor
    a=move(b); //move(b)为右值，因此会调用move assignment
    b=move(tmp); //move(tmp)为右值，因此会调用move assignment
}
    
```

使用上述算法的前提是，我们不在乎在运行过程中a,b的值的改变，因为在调用MoveSwap时，会存在某一时刻，a的内容为空串。

### 无序容器（哈希表）

#include<unordered_map>

在插入和查找时，时间复杂度近乎为常数，但需要更多的内存空间

### 正则表达式

#include<regex>

正则表达式说明了一种模式

```cpp
int main()
{
    regex reg("b.?p.*k");
    //以字符b开头，紧接一个或零个字符，其次为字符p，载接着0个或多个相同的字符，最后以k结尾
    cout<<regex_match("bopggk",reg);//输出1，匹配成功
    cout<<regex_match("boopgggk",reg);///输出0，匹配失败
    cout<<regex_match("b kg",reg);//输出1，匹配成功
    regex reg2("\\d{3}([a-zA-Z]+).(\\d{2}|N/A\\ss\1)");
    // "\\d"代表"\d"即数字0-9，{3}表示出现3次，“（）”代表一项，[a-zA-Z]代表字母，“+”表示前面的内容出现一次或者多次，综合来看，（[a-zA-Z]+）表示一个英文单词，单词长度最少为1，"."表示出现任一个字符。(\\d{2}|N/A)表示要么出现两个数字，要么出现"N/A"。"\\s"表示空格，\\1表示和第一项一致，即([a-zA-Z]+)
    string correct = "123Hello N/A Hello";
}
```

###  Lambda表达式

只调用一次的简单函数对象

形式：

```shell
[外部变量访问方式说明符](参数表) -> 返回值类型
{
	语句
}
```

- [=]以传值形式使用外部所有的变量，如果是一个对象，则会引发复制构造函数
- []不使用任何外部变量
- [&]以引用方式使用所有外部变量
- [x, &y] x以传值形式使用, y以引用方式使用
- [=, &x, &y] x,y以引用形式使用，其与变量以传值形式使用
- [&, x, y] x,y以传值形式使用，其余变量以引用形式使用

"->返回值类型"也可以没有，编译器自动进行判断

```cpp
int main()
{
    int x = 100, y=200, z=300;
    cout<<[](double a, double b){return a+b;}(1.2,2.5);
    auto ff=[=, &x, &y](int n) {
        cout<<x<<endl;
        y++;z++;
        return n*n;
    };//ff此处有点类似函数指针，此处是声明，不是调用
    cout<<ff(15)<<endl;
    cout<<y<<","<<z<<endl;
}
```

Lamda优越性的体现：

```cpp
int a[4] ={4,2,11,33};
sort(a, a+4, [](int x, int y)->bool{return x%10<y%10});
for_each(a, a+4, [](int x){cout << x<<" ";});
```

利用递归求斐波那契数列第n项：

```cpp
function<int(int)>fib = [&fib](int n)
{ return n<=2?1:fib(n-1)+fib(n-2);};
```

function<int(int)>表示返回值为int，有一个int参数的函数。此时不能写为auto，因为编译器无法通过return直接得到一个确定的类型。

##  强制类型转换 

### static_cast

用来进行比较“自然”和低风险的转换，如整数型和实数型、字符型之间的相互转换。

不能在不同类型的指针之间相互转换，也不能用于整型和指针之间的相互转换，也不能用于不同类型的引用之间的转换。

旧的类似于(int)的强制类型转换，不能识别风险大小。而且debug时，如果不用"cast"关键字，检索时很麻烦。 

```cpp
class A
{
public:
    operator int() {return 1;} //类型转换的重载，不用写返回值
    operator char *() {return NULL;}
};
int main()
{
    A a;
    int n; char *p = "New Dragon Inn";
    n = static_cast<int>(3.14); //n的值变为3
    n = static_cast<int> (a); //调用a.operator int， n的值变为1
    p = static_cast<char*>(a); //调用a.operator char *. p的值变为NULL
    n = static_cast<int> (p); //编译错误，static_cast不能将指针转换为整型
    p = static_cast<char*> (n);//编译错误，static_cast不能将整型转换为指针
    return 0;
}
```



### reinterpret_cast

不同类型的指针之间的转换、不同类型的引用之间转换、以及指针和能容纳得下指针的整数类型之间的转换。转换的时候， 执行的是逐个比特拷贝的操作。

```cpp
#include <iostream>
using namespace std;
class A
{
public:
	int i;
	int j;
	A(int n):i(n),j(n) { }
};
int main()
{
	A a(100);
	int & r = reinterpret_cast<int&>(a); //强行让 r 引用 a
	r = 200; //把 a.i 变成了 200,r的四个字节写入200。而A的内存分布为i（4个字节），j(4个字节)
	cout << a.i << "," << a.j << endl; // 输出 200,100
	int n = 300;
    A * pa = reinterpret_cast<A*> ( & n); //强行让 pa 指向 n
	pa->i = 400; // n 变成 400
	pa->j = 500; //此条语句不安全，很可能导致程序崩溃
	cout << n << endl; // 输出 400
	long long la = 0x12345678abcdLL;
	pa = reinterpret_cast<A*>(la); // la太长，只取低32位0x5678abcd拷贝给pa
	unsigned int u = reinterpret_cast<unsigned int>(pa); //pa逐个比特拷贝到u
	cout << hex << u << endl; //输出 5678abcd
	typedef void (* PF1) (int);
	typedef int (* PF2) (int,char *);
	PF1 pf1; PF2 pf2;
	pf2 = reinterpret_cast<PF2>(pf1); //两个不同类型的函数指针之间可以互相转换
}
```

### const_cast

用来进行去除const属性的转换。将const引用转换成同类型的非const引用，将const指针转换为同类型的非const指针时用它。

### dynamic_cast

- dynamic_cast专门用于将多态基类的指针或引用，强制转换为派生类的指针或引用，而且能够检查转换的 安全性。对于不安全的指针转换，转换结果返回NULL 指针。 

- dynamic_cast不能用于将非多态基类的指针或引用， 强制转换为派生类的指针或引用

```cpp
#include <iostream>
#include <string>
using namespace std;
class Base
{ //有虚函数，因此是多态基类
public:
	virtual ~Base() { }
};
class Derived:public Base { };
int main()
{
	Base b;
	Derived d;
	Derived * pd;
	pd = reinterpret_cast<Derived*> ( &b);
    if( pd == NULL) //此处pd不会为NULL。
	//reinterpret_cast不检查安全性，总是进行转换
		cout << "unsafe reinterpret_cast" << endl;
	//不会执行
	pd = dynamic_cast<Derived*> ( &b);
	if( pd == NULL)
	//结果会是NULL，因为 &b不是指向派生类对象，此转换不安全
		cout << "unsafe dynamic_cast1" << endl; //会执行
	Base * pb = & d;
	pd = dynamic_cast<Derived*> ( pb); //安全的转换
	if( pd == NULL) //此处pd 不会为NULL
	cout << "unsafe dynamic_cast2" << endl; //不会执行
	return 0;
}
```

## 异常处理

```cpp
#include <iostream>
using namespace std;
int main() {
	double m ,n;
	cin >> m >> n;
	try {
		cout << "before dividing." << endl;
		if( n == 0)
			throw -1; //抛出整型异常
		else if( m == 0 )
			throw -1.0; //抛出double型异常
		else 
            cout << m / n << endl;
		cout << "after dividing." << endl;
    }
    catch(double d) {
		cout << "catch(double) " << d << endl;
	}
	catch(...) { //捕获任何异常的catch块
        // 如果存在double异常，catch会从上到下一次匹配，进入第一个匹配成功的catch块
		cout << "catch(...) " << endl;
    }
	cout << "finished" << endl;
	return 0;
}
```

### 异常的再抛出

如果一个函数在执行的过程中，抛出的异常在本函数内就被catch块捕获并处理了，那么该异常就不会抛给这个函数的调用者(也称“上一层的函数”)；如果异常在本函数中没被处理，就会被抛给上一层的函数。

```cpp
#include <iostream>

#include <string>

using namespace std;
class CException {
    public:
        string msg;
    CException(string s): msg(s) {}
};
double Devide(double x, double y) {
    if (y == 0)
        throw CException("devided by zero");
    cout << "in Devide" << endl;
    return x / y;
}
int CountTax(int salary) {
    try {
        if (salary < 0)
            throw -1;
        cout << "counting tax" << endl;
    } catch (int) {
        cout << "salary < 0" << endl;
    }
    cout << "tax counted" << endl;
    return salary * 0.15;
}
int main() {
    double f = 1.2;
    try {
        CountTax(-1);
        f = Devide(3, 0);
        cout << "end of try block" << endl;
    } catch (CException e) {
        cout << e.msg << endl;
    }
    cout << "f=" << f << endl;
    cout << "finished" << endl;
    return 0;
}
```



### C++标准异常类

\#include<stdexcept>

1. **bad_cast** 在用 dynamic_cast进行从多态基类对象（或引用）,到派生类的引用的强制类型转换时，如果转换是不安全的，则会抛出此异常。

2. **bad_alloc** 在用new运算符进行动态内存分配时，如果没有足够的内存，则会引发此异常。

3. **out_of_range**用vector或string 的at成员函数根据下标访问元素时， 如果下标越界，就会抛出此异常。

