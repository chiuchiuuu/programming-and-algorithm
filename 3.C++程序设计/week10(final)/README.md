# 编程作业: 期末考试—编程试题

## 编程题＃1：输出200

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 1000ms 内存限制: 1024kB**

### 描述

使以下代码输出结果为200.

```c++
1#include<iostream>
using namespace std;

class Number {
public:
    int num;
    Number(int n=0): num(n) {}
// 在此处补充你的代码
};

int main() {
    Number n1(10), n2(20);
    Number n3;n3 = n1*n2;
    cout << int(n3) << endl;
    return 0;
}
```

### 输入

不需要输入。

### 输出

输出结果为200。

### 样例输入

```
不需要输入。
```

### 样例输出

```
200
```

### 解题思路

重载运算符，尤其注意强制类型转换符重载不需要返回类型。



## 编程题＃2：输出指定结果一

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 1000ms 内存限制: 1024kB**

### 描述

填写代码，使输出结果为

2

2

8

10

```c++
#include <iostream>
using namespace std;
class Number {
public:
    int num;
    Number(int n): num(n) {
    }
// 在此处补充你的代码
};
int main() {
    Number a(2);
    Number b = a;
    cout << a.value() << endl;
    cout << b.value() << endl;
    a.value() = 8;
    cout << a.value() << endl;
    a+b;
    cout << a.value() << endl;
    return 0;
}
```

### 样例输入

```
不需要输入。
```

### 样例输出

```
2
2
8
10
```

### 解题思路

注意`+`的重载



## 编程题＃3：计算数列平方和

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 1000ms 内存限制: 1024kB**

### 描述

请写出sum函数，使其可以计算输入数列的平方和。

```c++
#include <iostream>
using namespace std;
// 在此处补充你的代码
int sqr(int n) {
    return n * n;
}
int main() {
    int t, n, a[0x100];
    cin >> t;
    for (int c = 0; c < t; ++c) {
        cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    cout << sum(a, n, sqr) << endl;
    }
    return 0;
}
```

### 输入

第一行是一个整数 t (t <= 10)，表示数据组数；

每组输入数据包含两行，第一行是一个整数 n (n <= 100)，

第二行是 n 个用空格分隔开的整数

### 输出

对每组输入数据，输出该组数据中 n 个整数的平方和

### 样例输入

```
2
2
4 3
3
0 1 2
```

### 样例输出

```
25
5
```

### 解题思路

函数指针



## 编程题＃4：计算整数平方和

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 1000ms 内存限制: 1024kB**

### 描述

下列程序每次读入一个整数N，若N为0则退出，否则输出N和N的平方。

```c++
#include <iostream>
using namespace std;
// 在此处补充你的代码
int main(int argc, char* argv[]) {
        CType obj;
        int n;
        cin>>n;
        while ( n ) {
                obj.setvalue(n);
                cout<<obj++<<" "<<obj<<endl;
                cin>>n;
        }
        return 0;
}
```

### 输入

K个整数。除最后一个数据外，其他数据均不为0。

### 输出

K-1行。第I行输出第I个输入数和它的平方。

### 样例输入

```
1 5 8 9 0
```

### 样例输出

```
1 1
5 25
8 64
9 81
```

### 解题思路

这道题有点奇葩，观察题目，平方是在`obj++`里实现的，同时返回的是平方前的`obj`，本质上还是运算符重载

这里遇到一个之间没遇过的知识点，起初我的重载是这样的

```c++
CType operator++(int)
{
	CType tmp = *this;
	value *= value;
	return tmp;
}
ostream& operator<<(ostream &os, CType &t)
{
	os << t.value;
	return os;
}
```

这里返回的是一个临时对象，然后被引用作为`cout`的参数输出，但这时候编译不通过，报错`no match for operator<<`。了解后发现临时对象被某函数引用做参数就会出现问题，因为这时函数对临时对象做的修改都会被抛弃，相当于什么都没做，是无意义的，所以编译器不允许这种行为。[详细解释](https://www.cnblogs.com/BensonLaur/p/5234555.html)

两个办法修正：

- 改为值传递：`ostream& operator<<(ostream &os, CType t)`
- 改为常引用：`ostream& operator<<(ostream &os, const CType &t)`



## 编程题＃5：计算数组的低3位之和

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 1000ms 内存限制: 1024kB**

### 描述

输入一个正整数构成的数组a[0], a[1], a[2], ... , a[n-1], 计算它们的二进制低3位之和。

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
int main(int argc, char* argv[]) {
        int v, my_sum=0;
        vector<int> vec;
        cin>>v;
        while ( v ) {
                vec.push_back(v);
                cin>>v;
        }
        for_each(vec.begin(), vec.end(), CMy_add(my_sum));
        cout<<my_sum<<endl;
        return 0;
}
```

### 输入

数组a,以0表示输入结束。

### 输出

一个整数 , 所输入数组各元素的二进制低3位之和。

### 样例输入

```
1 3 9 7 3 6 20 15 18 17 4 8 18 0
```

### 样例输出

```
41
```

### 解题思路

- 二进制低三位之和立马想到与运算`val&7`
- `for_each`里的`CMy_add(my_sum)`想到要编写函数对象
  - 注意到我们要对初始化参数`my_sum`直接修改，所以`CMy_add(my_sum)`的成员变量应该是`my_sum`的引用





## 编程题＃6：MyString

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 1000ms 内存限制: 1024kB**

### 描述

请写出 MyString类，使得下面程序的输出结果符合下面的要求。

```c++
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;
// 在此处补充你的代码
int CompareString( const void * e1, const void * e2)
{
        MyString * s1 = (MyString * ) e1;
        MyString * s2 = (MyString * ) e2;
        if( * s1 < *s2 )
                 return -1;
        else if( *s1 == *s2)
                 return 0;
        else if( *s1 > *s2 )
                 return 1;
}
int main()
{
        MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
        MyString SArray[4] = {"big","me","about","take"};
        cout << "1. " << s1 << s2 << s3<< s4<< endl;
        s4 = s3;
        s3 = s1 + s3;
        cout << "2. " << s1 << endl;
        cout << "3. " << s2 << endl;
        cout << "4. " << s3 << endl;
        cout << "5. " << s4 << endl;
        cout << "6. " << s1[2] << endl;
        s2 = s1;
        s1 = "ijkl-";
        s1[2] = 'A' ;
        cout << "7. " << s2 << endl;
        cout << "8. " << s1 << endl;
        s1 += "mnop";
        cout << "9. " << s1 << endl;
        s4 = "qrst-" + s2;
        cout << "10. " << s4 << endl;
        s1 = s2 + s4 + " uvw " + "xyz";
        cout << "11. " << s1 << endl;
        qsort(SArray,4,sizeof(MyString),CompareString);
        for( int i = 0;i < 4;i ++ )
        cout << SArray[i] << endl;
        //s1的从下标0开始长度为4的子串
        cout << s1(0,4) << endl;
        //s1的从下标5开始长度为10的子串
        cout << s1(5,10) << endl;
        return 0;
}
```

### 样例输入

```
无
```

### 样例输出

```
1. abcd-efgh-abcd-
2. abcd-
3.
4. abcd-efgh-
5. efgh-
6. c
7. abcd-
8. ijAl-
9. ijAl-mnop
10. qrst-abcd-
11. abcd-qrst-abcd- uvw xyz
about
big
me
take
abcd
qrst-abcd-
```

### 解题思路

这题不难。一开是我直接自己编写整个`MyString`类，后来发现直接继承`string`再补充其他成员函数就好了。



## 编程题＃7：字符串排序

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 1000ms 内存限制: 1024kB**

### 描述

请按照要求对输入的字符串进行排序。

```c++
#include <iostream>
#include <string>
#include <list>
using namespace std;

class A{
private:
        string name;
public:
        A(string n) :name(n){}
        friend bool operator < (const class A& a1, const class A &a2);
        friend bool operator == (const class A &a1, const class A &a2){
                if (a1.name.size() == a2.name.size())
                        return true;
                else
                        return false;
        }
        friend ostream & operator << (ostream &o, const A &a){
                o << a.name;
                return o;
        }
        string get_name() const{
                return name;
        }
        int get_size() const{
                return name.size();
        }
};
// 在此处补充你的代码
int main(int argc, char* argv[])
{
        list<A> lst;
        int ncase, n, i = 1;
        string s;
        cin >> ncase;
        while (ncase--){
                cout << "Case: "<<i++ << endl;
                cin >> n;
                for (int i = 0; i < n; i++){
                         cin >> s;
                         lst.push_back(A(s));
                }
                lst.sort();
                Show(lst.begin(), lst.end(), Print());

                cout << endl;
                lst.sort(MyLarge<A>());
                Show(lst.begin(), lst.end(), Print());
                cout << endl;
                lst.clear();
        }
        return 0;
}
```

### 输入

第一行是正整数T，表示测试数据的组数

每组测试数据输入共两行，

第一行是正整数N，表示字符串个数

第二行是N个字符串, 字符串间用空格分离

### 输出

对于每组测试数据，先输出一行：

Case: n

如对第一组数据就输出Case: 1

第二行按照字符串长度从小到大排序之后输出N个字符串，字符串之间以空格间隔（不会出现字符串长度相同的情况）

第三行按照字符串首字符ASCII码序从小到大排序之后输出N个字符串，字符串之间以空格间隔（不会出现字符串首字母相同的情况）

### 样例输入

```
2
4
a bnss ds tsdfasg
5
aaa bbbb ccccd sa q
```

### 样例输出

```
Case: 1
a ds bnss tsdfasg
a bnss ds tsdfasg
Case: 2
q sa aaa bbbb ccccd
aaa bbbb ccccd q sa
```

### 解题思路

- 按长度排序：`bool operator<(const A &a1, const A &a2)`

- 实现`Show(lst.begin(), lst.end(), Print());`

  - 拆成对象函数`struct Print`和`Show()`

  - `template<class InIt, class Func> `

    `void Show(InIt first, InIt last, Func func)`

- 自定义比较器`struct MyLarge`



## 编程题＃8：计算整数k

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 1000ms 内存限制: 1024kB**

### 描述

输入整数 n ( 0 <=n<= 2^30) , 以及整数i,j(0 <= i,j <31,i < j-1), 输出整数k(按十六进制输出结果 )，k的第i位和n相同，第j位和n不同，i,j之间的位是1, 其他位都是0。这里提到的所有的位，指的都是二进制位，最右边算第0位。

### 输入

第一行是整数 t，表示数据组数。

每组输入数据是一行，三个整数 n,i和j。

### 输出

对每组输入数据，按十六进制输出结果。

### 样例输入

```
2
23 3 5
7 0 2
```

### 样例输出

```
30
3
```

### 解题思路

利用数据结构`bitset`



## 编程题＃9：人群的排序和分类

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 1000ms 内存限制: 1024kB**

### 描述

对人群按照输入的信息进行排序和分类。

```c++
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
int main()
{
        int t;
        cin >> t;
        set<A*,Comp> ct;
        while( t -- ) {
                int n;
                cin >> n;
                ct.clear();
                for( int i = 0;i < n; ++i)  {
                        char c; int k;
                        cin >> c >> k;
                        if( c == 'A')
                                ct.insert(new A(k));
                        else
                                ct.insert(new B(k));
                }
                for_each(ct.begin(),ct.end(),Print);
                cout << "****" << endl;
        }
}
```

### 输入

第一行是整数t,表明一共t组数据. t < 20

对每组数据：

第一行是整数n,表示下面一共有n行。 0 < n < 100

下面的每行代表一个人。每行以一个字母开头，代表该人所属的类别，然后跟着一个整数，代表年龄。字母只会是 'A‘或‘B' 。整数范围0到100。数据保证年龄都不相同。

### 输出

对每组输入数据，将这些人按年龄从小到大输出。每个人先输出类别，再输出年龄。每组数据的末尾加一行 "****"

### 样例输入

```
2
4
A 3
B 4
A 5
B 6
3
A 4
A 3
A 2
```

### 样例输出

```
A 3
B 4
A 5
B 6
****
A 2
A 3
A 4
****
```

### 解题思路

```c++
set<A*,Comp> ct;
ct.insert(new B(k));
```

- 由这两句判断，A类指针可以指向B，B应该是A的子类。



## 编程题＃10：输出指定结果二

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 1000ms 内存限制: 1024kB**

### 描述

通过填空使得程序输出的结果符合下面的要求。

```c++
#include <iostream>
#include <map>
using namespace std;
// 在此处补充你的代码
int A::count = 0;
void func(B b) { }
int main()
{
        A a1(5),a2;
        cout << A::count << endl;
        B b1(4);
        cout << A::count << endl;
        func(b1);
        cout << A::count << endl;
        A * pa = new B(4);
        cout << A::count << endl;
        delete pa;
        cout << A::count << endl;
        return 0;
}
```

### 样例输入

```
不需要输入。
```

### 样例输出

```
2
3
B::destructor
A::destructor
3
4
B::destructor
A::destructor
3
B::destructor
A::destructor
A::destructor
A::destructor
```

### 提示

int A::count = 0; 这个变量是用来记录一共有多少个类A及类A的派生类的对象的。

### 解题思路

两个要点：

- A，B构造函数，析构函数的调用顺序
- `func(b1);`值传递会调用复制构造函数



## 编程题＃11：数据库内的学生信息

**来源: 北京大学在线程序评测系统POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)**

**总时间限制: 3000ms 内存限制: 20480kB**

## 描述

程序填空，使得下面的程序,先输出

(Tom,80),(Tom,70),(Jone,90),(Jack,70),(Alice,100),

(Tom,78),(Tom,78),(Jone,90),(Jack,70),(Alice,100),

(70,Jack),(70,Tom),(80,Tom),(90,Jone),(100,Alice),

(70,Error),(70,Error),(80,Tom),(90,Jone),(100,Alice),

******

然后，再根据输入数据按要求产生输出数据

```c++
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
struct Student
{
        string name;
        int score;
};
template <class T>
void Print(T first,T last) {
        for(;first!= last; ++ first)
                cout << * first << ",";
        cout << endl;
}
int main()
{

        Student s[] = { {"Tom",80},{"Jack",70},
                                        {"Jone",90},{"Tom",70},{"Alice",100} };
        MyMultimap<string,int> mp;
        for(int i = 0; i<5; ++ i)
                mp.insert(make_pair(s[i].name,s[i].score));
        Print(mp.begin(),mp.end()); //按姓名从大到小输出

        mp.Set("Tom",78); //把所有名为"Tom"的学生的成绩都设置为78
        Print(mp.begin(),mp.end());


        MyMultimap<int,string,less<int> > mp2;
        for(int i = 0; i<5; ++ i)
                mp2.insert(make_pair(s[i].score,s[i].name));

        Print(mp2.begin(),mp2.end()); //按成绩从小到大输出
        mp2.Set(70,"Error");          //把所有成绩为70的学生，名字都改为"Error"
        Print(mp2.begin(),mp2.end());
        cout << "******" << endl;

        mp.clear();
        
        string name;
        string cmd;
        int score;
        while(cin >> cmd ) {
                if( cmd == "A") {
                        cin >> name >> score;
                        if(mp.find(name) != mp.end() ) {
                                cout << "erroe" << endl;
                        }
                        mp.insert(make_pair(name,score));
                }
                else if(cmd == "Q") {
                        cin >> name;
                        MyMultimap<string,int>::iterator p = mp.find(name);
                        if( p!= mp.end()) {
                                cout << p->second << endl;
                        }
                        else {
                                cout << "Not Found" << endl;
                        }
                }
        }
        return 0;
}
```

### 输入

输入数据的每一行，格式为以下之一：

A name score

Q name score

name是个不带个空格的字符串，长度小于 20

score是个整数，能用int表示

A name score 表示往数据库中新增一个姓名为name的学生，其分数为score。开始时数据库中一个学生也没有。

Q name 表示在数据库中查询姓名为name的学生的分数

数据保证学生不重名。

输入数据少于200,000行。

### 输出

对于每个查询，输出学生的分数。如果查不到，则输出 "Not Found"

### 样例输入

```
A Tom1 30
A Tom2 40
Q Tom3
A Tom4 89
Q Tom1
Q Tom2
```

### 样例输出

```
(Tom,80),(Tom,70),(Jone,90),(Jack,70),(Alice,100),
(Tom,78),(Tom,78),(Jone,90),(Jack,70),(Alice,100),
(70,Jack),(70,Tom),(80,Tom),(90,Jone),(100,Alice),
(70,Error),(70,Error),(80,Tom),(90,Jone),(100,Alice),
******
Not Found
30
40
```

### 提示

1) 编写模板的时候，连续的两个 “>”最好要用空格分开，以免被编译器看作是 ">>"运算符。VS可能无此问题，但是Dev C++和服务器上的编译环境会有这个问题。

比如 vector<vector<int>> 有可能出错，要改成 vector<vector<int> >

2) 在模板中写迭代器时，最好在前面加上 typename关键字，否则可能会编译错。VS可能无此问题，但是Dev C++和服务器上的编译环境会有这个问题。

### 解题思路

多利用已有代码

- 编写`MyMultimap`，直接继承`multimap`。
- 从大到小用`<functional>`的`greater`

找到所有与`key`相等的项可以直接用`equal_range(key)`