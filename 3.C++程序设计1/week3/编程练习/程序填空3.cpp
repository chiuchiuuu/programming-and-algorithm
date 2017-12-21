/*
编程题 ＃3
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
下面程序的输出结果是：
5,5
5,5

请填空：
#include <iostream>
using namespace std;
class Base {
public:
    int k;
    Base(int n):k(n) { }
};
class Big {
public:
    int v; Base b;
// 在此处补充你的代码
};
int main() {
    Big a1(5); Big a2 = a1;
    cout << a1.v << "," << a1.b.k << endl;
    cout << a2.v << "," << a2.b.k << endl;
    return 0;
}

样例输入
无

样例输出
5,5
5,5

提示
所缺代码具有如下形式：
Big ________________{ }
Big ________________{ }

*/
#include <iostream>
using namespace std;

class Base
{
public:
	int k;
	Base(int n) :k(n) {}
};

class Big
{
public:
	int v;
	Base b;
	Big(int n) :v(n), b(n) {}
	Big(const Big &big) :v(big.v), b(big.v) {}
};

int main()
{
	Big a1(5);
	Big a2 = a1;
	cout << a1.v << "," << a1.b.k << endl;
	cout << a2.v << "," << a2.b.k << endl;
	return 0;
}