/*
编程题 ＃2
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
下面程序的输出是：
10

请补足Sample类的成员函数。不能增加成员变量。
#include <iostream>
using namespace std;
class Sample{
public:
    int v;
    Sample(int n):v(n) { }
// 在此处补充你的代码
};
int main() {
    Sample a(5);
    Sample b = a;
    cout << b.v;
    return 0;
}

样例输入
无

样例输出
1
10
*/

#include <iostream>
using namespace std;

class Sample
{
public:
	int v;
	Sample(int n) :v(n) {};
	Sample(const Sample &s)
	{
		v = s.v + 5;
	}
};

int main()
{
	Sample a(5);
	Sample b = a;
	cout << b.v;
	return 0;
}