#include <iostream>
using namespace std;

// 在此处补充你的代码
class CType
{
public:
	int value;
	void setvalue(int n)
	{
		value = n;
	}
	CType operator++(int)
	{
		CType tmp = *this;
		value *= value;
		return tmp;
	}
	friend ostream& operator<<(ostream &os, const CType &t);
};

ostream& operator<<(ostream &os, const CType &t)
{
	os << t.value;
	return os;
}

int main(int argc, char* argv[])
{
	CType obj;
	int n;
	cin >> n;
	while (n) {
		obj.setvalue(n);
		cout << obj++ << " " << obj << endl;
		cin >> n;
	}
	return 0;
}
