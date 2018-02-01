# Week4

## 运算符重载

运算符重载

- 对已有的运算符赋予多重的含义

- 使同一运算符作用于不同类型的数据时有不同类型的行为

目的：

- 扩展C++中提供的运算符的适用范围, 以用于类所表示的抽象数据类型

运算符重载的实质是函数重载，参数个数为运算符目数

```c++
返回值类型 operator 运算符(形参表)
{
	…… 
}
```

例如复数相加：

```c++
Complex operator+(const Complex &a, const Complex &b)
{
	return Complex(a.real + b.real, a.imag + b.imag)
}
```

运算符重载为成员函数，参数个数为运算符目数减一

```c++
Complex operator+(const Complex &operand2);
// x = y + z
// 等价于 x = y.operator+(z)
```



## 赋值运算符重载

### 赋值运算符

赋值运算符两边的类型可以不匹配，但需要重载赋值运算符 `=` 

- 把一个 `int` 类型变量 赋值给一个 Complex对象
- 把一个 `char*` 类型的字符串赋值给一个 字符串对象

注意：赋值运算符 `=` 只能重载为成员函数！

例子：字符串赋值

```c++
class String
{
private:
	char *str;
public:
	String() :str(NULL) {}
	const char *get_str() { return str; }
	char* operator=(const char *str);
	~String();
};

char* String::operator=(const char *s)
{
	if (str)
	{
		delete[] str;
	}
	if (s)
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	else
	{
		str = NULL;
	}
	return str;
}

String::~String()
{
	if (str)
	{
		delete[] str;
	}
}
```

赋值运算符重载的目的：

- 可以使用其他类型变量或常量给对象赋值
- 解决浅拷贝的问题

### 浅复制与深复制

浅复制是一种逐字节的复制。在复制内容包含指针时会产生问题。

```c++
MyString S1, S2;
S1 = "this";
S2 = "that";
S2 = S1;
```

这样一个简单的程序会导致S1和S2的`char *` 变量指向同一块内存，会造成内存垃圾，以及重复`delete`的隐患。

利用赋值运算符重载可以实现深复制：将一个对象中指针变量指向的内容，复制到另一个对象中指针成员对象指向的地方。

```c++
String& operator=(const String &s)
{
	if (str == s.str)  // 针对自身赋值的情况
	{
		return *this;
	}
	if (str)
	{
		delete[] str;
	}
	if (s.str)
	{
		str = new char[strlen(s.str) + 1];
		strcpy(str, s.str);
	}
	else
	{
		str = NULL;
	}
	return *this;
}
```

### 返回值

赋值运算符重载时，返回值设为其所作用的对象的引用，是符合赋值运算符使用习惯的做法。

```c++
a = b = c;  // return void 会导致a赋值失败
(a = b) = c; // return string 会导致第二个赋值无意义
```



## 运算符重载为友元函数

通常将运算符重载为类的成员函数

重载为友元函数的情况：

- 成员函数不能满足使用要求
- 普通函数又不能访问类的私有成员 

```c++
class Complex 
{ 
	double real, imag; 
public:  
	Complex(double r, double i) :real(r), imag(i) { };
	Complex operator+(double r); // 能解释c+5
	friend Complex operator + (double r, const Complex & c); // 能解释 5+c
};
```



## 运算符重载示例：长度可变的整形数组

```c++
#include <iostream>
using namespace std;

class CArray
{
private:
	int size;
	int *ptr;
public:
	CArray(int s = 0);
	CArray(CArray &a);
	~CArray();
	void push_back(int n);
	CArray & operator=(const CArray &a);
	int & operator[](int i) { return ptr[i]; } // a[i] = 4
	int length() { return size; }
};

CArray::CArray(int s) :size(s)
{
	if (s == 0)
	{
		ptr = NULL;
	}
	else
	{
		ptr = new int[s];
	}
}

CArray::CArray(CArray &a)
{
	if (!a.ptr)
	{
		ptr = NULL;
		size = 0;
		return;
	}
	ptr = new int[a.size];
	size = a.size;
	memcpy(ptr, a.ptr, sizeof(int)*a.size);
}

CArray::~CArray()
{
	if (ptr)
	{
		delete[] ptr;
	}
}

CArray& CArray::operator=(const CArray &a)
{
	if (ptr == a.ptr)
	{
		return *this;
	}
	if (a.ptr == NULL)
	{
		if (ptr)
		{
			delete[] ptr;
		}
		ptr = NULL;
		size = 0;
		return *this;
	}
	if (size < a.size)  // 空间足够就没必要重新分配内存
	{
		if (ptr)
		{
			delete[] ptr;
		}
		ptr = new int[a.size];
	}
	memcpy(ptr, a.ptr, sizeof(int)*a.size);
	size = a.size;
	return *this;
}

void CArray::push_back(int v)
{
	// 简单低效
	if (ptr)
	{
		int *tmpPtr = new int[size + 1];
		memcpy(tmpPtr, ptr, sizeof(int)*size);
		delete[] ptr;
		ptr = tmpPtr;
	}
	else
	{
		ptr = new int[1];
	}
	ptr[size++] = v;
}

int main() {  //要编写可变长整型数组类，使之能如下使用：
	CArray a; //开始里的数组是空的
	for (int i = 0; i < 5; ++i)
	{
		a.push_back(i);
	}
	CArray a2, a3;
	a2 = a;
	for (int i = 0; i < a.length(); ++i)
	{
		cout << a2[i] << " ";
	}
	a2 = a3; //a2是空的    
	for (int i = 0; i < a2.length(); ++i) //a2.length()返回0
	{
		cout << a2[i] << " ";
	}
	cout << endl;
	a[3] = 100;
	CArray a4(a); 
	for (int i = 0; i < a4.length(); ++i)
	{
		cout << a4[i] << " ";
	}
	return 0;
}
```



## 流插入运算符和流提取运算符的重载

`cout` 是在 `iostream` 定义的 `ostream` 类的对象。

```c++
// 返回引用实现连续输出
ostream & ostream::operator<<(int n)
{
	...
	return *this;
}
```

定制自己的 `cout`， 只能重载成全局函数

```c++
ostream & operator<<(ostream &o, const CStudent &s)
{
	o << s.nAge;
  	return o;
}
```

示例：输入输出复数

```c++
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Complex
{
private:
	double real, imag;
public:
	Complex(double r = 0, double i = 0) :real(r), imag(i) {};
	friend ostream& operator<<(ostream &os, const Complex &c);
	friend istream& operator>>(istream &is, Complex &c);
};

ostream & operator<<(ostream &os, const Complex &c)
{
	os << c.real << "+" << c.imag << "i";
	return os;
}

istream & operator>>(istream &is, Complex &c)
{
	string s;
	is >> s;
	int pos = s.find("+", 0);
	string sTmp = s.substr(0, pos);
	c.real = atof(sTmp.c_str());
	sTmp = s.substr(pos + 1, s.length() - pos - 2);
	c.imag = atof(sTmp.c_str());
	return is;
}

int main() {
	Complex c;
	int n;
	cin >> c >> n;
	cout << c << "," << n;
	return 0;
	return 0;
}
```



## 自增/自减运算符的重载

### 前置运算符作为一元运算符重载 

- 重载为成员函数: 
  - `T & operator++();` 
  - `T & operator--();`
- 重载为全局函数： 
  - `T & operator++(T &);` 
  - `T & operator—-(T &);`
- `++obj`, `obj.operator++()`, `operator++(obj)` 都调用上述函数

### 后置运算符作为二元运算符重载 

- 多写一个参数, 无具体意义 
- 重载为成员函数：
  - `T operator++(int); `
  - `T operator--(int); `
- 重载为全局函数：
  - `T operator++(T &, int);`
  - `T operator--(T &, int); `
- `obj++`, `obj.operator++(0)`, `operator++(obj,0)` 都调用上函数

```c++
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class CDemo
{
private:
	int n;
public:
	CDemo(int i = 0) :n(i) {}
	CDemo & operator++();
	CDemo operator++(int);
	friend CDemo & operator--(CDemo &d);
	friend CDemo operator--(CDemo &d, int);
	operator int() { return n; }
};

CDemo& CDemo::operator++()
{
	n++;
	return *this;
}

CDemo CDemo::operator++(int)
{
	CDemo tmp(*this);
	n++;
	return tmp;
}

CDemo& operator--(CDemo &d)
{
	d.n--;
	return d;
}

CDemo operator--(CDemo &d, int)
{
	CDemo tmp(d);
	d.n--;
	return tmp;
}

int main() {
	CDemo d(5);
	cout << (d++) << ",";  //等价于 d.operator++(0);
	cout << d << ",";
	cout << (++d) << ",";   //等价于 d.operator++();
	cout << d << endl;
	cout << (d--) << ",";   //等价于 operator--(d,0);
	cout << d << ",";
	cout << (--d) << ",";    //等价于 operator--(d);
	cout << d << endl;
	return 0;
}
```

### 类型强制转换运算符重载

在上例中 `int` 作为一个类型强制转换运算符被重载

- `Demo s;` `(int)s;` ：等价于`s.int()`

类型强制转换运算符重载时**不能写返回值类型**，实际上其返回值类型就是类型强制转换运算符代表的类型。

### 运算符重载的注意事项

- C++不允许定义新的运算符 
- 重载后运算符的含义应该符合日常习惯 
- 运算符重载不改变运算符的优先级 
- 以下运算符不能被重载： `.`, `.*`, `::`, `?:`, `sizeof` 
- 重载运算符 `()`, `[ ]`, `->`或者赋值运算符 `=` 时, 重载函数必须声明为类的成员函数






