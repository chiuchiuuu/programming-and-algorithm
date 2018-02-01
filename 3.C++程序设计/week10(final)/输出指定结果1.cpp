#include <iostream>
using namespace std;
class Number {
public:
	int num;
	Number(int n) : num(n) { }
	// 在此处补充你的代码
	int& value()
	{
		return num;
	}
	void operator+(Number &n)
	{
		num += n.num;
	}
};
int main() {
	Number a(2);
	Number b = a;
	cout << a.value() << endl;
	cout << b.value() << endl;
	a.value() = 8;
	cout << a.value() << endl;
	a + b;
	cout << a.value() << endl;
	return 0;
}