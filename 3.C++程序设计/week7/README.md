# Week7：文件操作和模板

## 文件操作

顺序文件：一个有限字符构成的顺序字符流 

文件流类：用于文件操作

- `ifstream`
- `ofsteam`
- `fstream`

使用用/创建文件的基本流程

- 打开文件
  - 通过制定文件名，建立文件和文件流对象的关联
  - 指明文件的使用方式
- 读写文件
  - 利用读写指针进行相应位置的操作
- 关闭文件

### 打开文件

- 初始化对象时打开
- 初始化后用`open`函数打开

```c++
#include <fstream>
ofstream outFile("clients.dat", ios::out | ios::binary)；

ofstream fout;
fout.open("test.out", ios::out | ios::binary);
```

打开选项

- `ios::out` ：输出到文件，删除原有内容 
- `ios::app`：输出到文件，保留原有内容，总是在尾部添加 
- `ios::binary`：以二进制文件格式打开文件

文件名：

- 绝对路径
- 相对路径

判断打开是否成功

```c++
if (!fout)
{
  	cerr << "File open error!!" << endl;
}
```

### 文件的读写指针

- 对于输入文件，有一个读指针
- 对于输出文件，有一个写指针
- 对于输入输出文件，有一个读写指针 

读/写指针用于标识文件操作的当前位置,   该指针在哪里，读写操作就在哪里进行 。

相关函数：

- `tellp()`, `seekp()`
- `tellg()`, `seekg()`

```c++
ofstream fout("a1.out", ios::app);
long location = fout.tellp();    //取得写指针的位置 
location = 10L;                  // 可为负值
fout.seekp(location);            // 将写指针移动到第10个字节处
fout.seekp(location, ios::beg);  // 从头数location 
fout.seekp(location, ios::cur);  // 从当前位置数location
fout.seekp(location, ios::end);  // 从尾部数location
```

```c++
ifstream  fin(“a1.in”,ios::in);
long location = fin.tellg();      //取得读指针的位置
location = 10L; 
fin.seekg(location);              //将读指针移动到第10个字  
fin.seekg(location, ios::beg);    //从头数location
fin.seekg(location, ios::cur);    //从当前位置数location 
fin.seekg(location, ios::end);    //从尾部数location 
```

### 二进制文件读写

二进制文件读写是直接读写二进制数据

```c++
int x=10;
fout.seekp(20, ios::beg);
fout.write((const char *)(&x), sizeof(int)); 
 
fin.seekg(0, ios::beg);
fin.read((char *)(&x), sizeof(int)); 
```

### 例子

学生信息读写

见PPT吧



文件拷贝

```c++
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cerr << "File name missing!" << endl;
		return 1;
	}
	ifstream inFile(argv[1], ios::binary | ios::in);
	if (!inFile)
	{
		cerr << "inFile open error!" << endl;
		return 2;
	}

	ofstream outFile(argv[2], ios::binary | ios::out);
	if (!outFile)
	{
		cerr << "outFile open error!" << endl;
		return 3;
	}

	char c;
	while (inFile.get(c))
	{
		outFile.put(c);
	}
	outFile.close();
	inFile.close();
	return 0;
}
```



## 函数模板

### 泛型程序设计

算法实现时不指定具体要操作的数据的类型，适用于多种数据结构 

大量编写模板，使用模板的程序设计

优势：减少重复代码的编写

### 函数模板

- 定义

```c++
template<class 类型参数1, class 类型参数2, ...>
返回值类型 模板名(形参表)
{
  	函数体
}
```

例：交换函数

```c++
template <class T>
void swap(T &a, T &y)
{
	T tmp = a;
  	a = b;
  	b = tmp;
}
// 编译器会自动生成相应的函数
```

- 函数模板中可以有不止一个类型参数
- 函数模板可以重载，只要形参表不同即可

## 编译器匹配函数的顺序

- Step 1: 先找参数完全匹配的普通函数(非由模板实例化而得的函数)
- Step 2: 再找参数完全匹配的模板函数
- Step 3: 再找实参经过自动类型转换后能够匹配的普通函数 
- Step 4: 上面的都找不到, 则报错 

注意赋值兼容原则引起函数模板中类型参数的二义性

```c++
template<class T>
T myFunction(T arg1, T arg2) 
{
  	cout<<arg1<<“   ”<<arg2<<“\n”;
  	return arg1; }
…
myFunction(5, 7);        //ok: replace T with int
myFunction(5.8, 8.4);    //ok: replace T with double
myFunction(5, 8.4);      //error: replace T with int or double? 二义性 
```

可以在函数模板中使用多个类型参数, 可以避免二义性



## 类模板

在调用类模板时，指定参数，由编译系统根据参数提供的数据类型自动产生相应的模板类

### 类模板的定义

```c++
template <class 类型参数1, class 类型参数2, ...>
class 类模板名
{
  	成员函数和成员变量;
};
```

- 定义成员函数

```c++
template <类型参数表>
返回值类型 类模板名<类型参数名列表>::成员函数名(参数表)
{
  	...
}
```

- 定义对象

```c++
类模板名 <真实类型参数表>  对象名(构造函数实际参数表); 
```

### 声明对象

- 编译器由类模板生成类的过程叫类模板的实例化，编译器自动用具体的数据类型替换类模板中的类型参数，生成模板类的代码
- 由类模板实例化得到的类叫模板类，为类型参数指定的数据类型不同, 得到的模板类不同
- 同一个类模板的两个模板类是不兼容的


### 函数模板作为类模板成员

```c++
#include <iostream>
using namespace std;

template <class T>
class A
{
public:
  	template<class T2>  // 不能和类的参数相同！
    void Func(T2 t)  
    {
      	cout << t;
    } 	//成员函数模板
};

int main()
{
  	A<int> a;
  	a.Func('K'); //成员函数模板 Func被实例化
  	return 0;
}
```

### 类模板与非类型参数

类模板的 `<类型参数表>`中可以出现非类型参数: 

```c++
template <class T, int size>
class CArray
{
	T  array[size];
public:
  	void Print()
    {
      	for(int i = 0; i < size; ++i)
          	cout << array[i] << endl;
    }
}; 
```

### 类模板与继承

- 类模板派生出类模板

```c++
template <class T1, class T2>
class A
{
  	T1 v1;
  	T2 v2;
};

template <class T1, class T2>
class B : public A<T2, T1>
{
	T1 v3;
	T2 v4;
};

template <class T>
class C : public B<T, T>
{
  	T v5;
};
```

- 模板类派生出类模板

```c++
template <class T1, class T2>
class A
{
	T1 v1;
  	T2 v2;
};

class B : public A<int, double>
{
	T v;
};
```

- 普通类派生出类模板

```c++
class A
{
	int v1;
};

template <class T>
class B : public A
{
	T v;
};
```

- 模板类派生出普通类

```c++
template <class T>
class A
{
	T v1;
  	int n;
};

class B :public A<int>
{
	double v;
};
```



## string类

string类 是一个模板类，它的定义如下：

```c++
typedef basic_string<char> string;
```

使用string类要包含头文件 `<string>`

 string对象的初始化: 

- ` string s1("Hello");    // 一个参数的构造函数 `
- `string s2(8, ‘x’);       // 两个参数的构造函数`
- ` string month = “March”; `
- 不提供以字符和整数为参数的构造函数 

构造的string太长而无法表达会抛出`length_error`异常 

string 对象的长度用成员函数 `length()` 读取；

string 支持流读取运算符

string 支持 `getline` 函数：`getline(cin, str);`

### 赋值与复制

- `=`
- `assign(str, begin, size)`

部分复制

```c++
string s1("catpig"), s3;
s3.assign(s1, 1, 3);   //从s1 中下标为1的字符开始复制3个字符给s3 
```

### 访问

- `[]`：不检查下标
- `at()`：检查下标

### 连接

- `+`
- `append(str, begin, size)`

```c++
s2.append(s1, 3, s1.size()); 
//下标为3开始, s1.size()个字符
//如果字符串内没有足够字符, 则复制到字符串最后一个字符 
```

### 比较

- 关系运算符
- `compare()`

```c++
string s1("hello"), s2("hello"), s3("hell");
int f1 = s1.compare(s2);
int f2 = s1.compare(s3);
int f3 = s3.compare(s1);
int f4 = s1.compare(1, 2, s3, 0, 3);         //s1 1-2; s3 0-3
int f5 = s1.compare(0, s1.size(), s3);      //s1 0-end
cout << f1 << endl << f2 << endl << f3 << endl;
cout << f4 << endl << f5 << endl; 

输出
0    // hello == hello
1    // hello > hell
-1   // hell < hello
-1   // el < hell
1    // hello > hell 
```

### 子串

`substr(begin, size)`

### 交换

`swap()`

### 寻找字符

- `find(str, begin)`：从`begin`开始，从前往后找
- `rfind()`：从后往前找

找到则返回下标，否则返回 `string::npos`

- `find_first_of()`
- `find_last_of()`
- `find_first_not_of()`
- `find_last_not_of()`

### 替换

- `erase(index)` 去掉下标`index`以及之后的字符
- `replace(begin, size, str)`：从`begin`开始的`size`个字符替换为`str`

### 插入

- `insert(index, str, begin, size)`：从`str`从`begin`开始的`size`个字符插入到`index`

### 转换char*

- `c_str()`
- `data()`：`const char *p = str.data()`
- `copy()`

```c++

```

### 其他特性

- 成员函数 `capacity()` ：返回无需增加内存即可存放的字符数
- 成员函数 `maximum_size()` ：返回string对象可存放的最大字符数
- 成员函数 `length()` 和 `size()`：相同返回字符串的大小/长度
- 成员函数 `empty()` ：返回string对象是否为空
- 成员函数 `resize()` ：改变string对象的长度



## 输入和输出

### 与输入输出流操作相关的类

- `istream`是用于输入的流类，`cin`就是该类的对象。 
- `ostream`是用于输出的流类，`cout`就是该类的对象。 
- `ifstream`是用于从文件读取数据的类。 
- `ofstream`是用于向文件写入数据的类。 
- `iostream`是既能用于输入，又能用于输出的类。 
- `fstream `是既能从文件读取数据，又能向文件写入数据的类。 

### 标准流对象

 输入流对象: 

- `cin`与标准输入设备相连

输出流对象：

- `cout`与标准输出设备相连
- `cerr`与标准错误输出设备相连
- `clog`与标准错误输出设备相连 

`cin`对应于标准输入流，用于从键盘读取数据，也可以被**重定向** 为从文件中读取数据。

`cout` 对应于标准输出流，用于向屏幕输出数据，也可以被**重定向**为向文件写入数据。

`cerr` 对应于标准错误输出流，用于向屏幕输出出错信息

`clog` 对应于标准错误输出流，用于向屏幕输出出错信息

> `cerr`和`clog`的区别在于`cerr`不使用缓冲区,直接向显示器输出信 息；而输出到`clog`中的信息先会被存放在缓冲区,缓冲区满或者 刷新时才输出到屏幕。 

### 重定向

输出重定向

```c++
freopen("out.txt", "w", stdout);
```

输入重定向

```c++
freopen("in.txt", "r", stdin);
```

### 判断输入流结束

```c++
while (cin >> x)
{
	...
}

if (!cin.getline())
```

`cin` 作为条件判断语句其实时做了一个强制类型转换！没有读到输入时返回`false`

### `istream`类的成员函数

```c++
istream & getline(char * buf, int bufSize); 
```

从输入流中读取 `bufSize-1` 个字符到缓冲区 `buf`，或读到碰到 `\n` 为止（哪个先到算哪个）。

```c++
istream & getline(char * buf, int bufSize,char delim);
```

从输入流中读取 `bufSize-1` 个字符到缓冲区 `buf`，或读到碰到 `delim` 字符为止（哪个先到算哪个）。 

两个函数都会自动在 `buf` 中读入数据的结尾添加 `\0`。`\n` 或 `delim` 都不会被读入 `buf`，但**会被从输入流中取走**。如果输入流中 `\n` 或 `delim` 之前的字符个数达到或超过了 `bufSize` 个，就导致读入出错，其结果就是：虽然本次读入已经完成，但是之后的读入就都会失败了。 

- `bool eof()`：判断输入流是否结束 
- `int peek()`：返回下一个字符,但不从流中去掉. 
- `istream& putback(char c);`：将字符 `ch` 放回输入流
- `istream& ignore(int nCount = 1, int delim = EOF);`：从流中删掉最多 `nCount` 个字符，遇到 `EOF` 时结束。 

