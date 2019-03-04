#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

#include <string>
#include <vector>
#include <algorithm>
#define qsort(a,b,c,d) myqsort(a,b,c,d)

class MyString : public string
{
public:
	MyString() {};
	//1.0继承类继承父类所有的成员变量和成员函数，但不继承构造函数和析构函数
	//1.1继承类的无参构造函数，会隐式调用父类的无参构造函数
	MyString(const char * st) :string(st) {};
	//1.2继承类的有参构造函数，如果父类也有有参构造函数，则必须显示调用它
	//2.0这里的参数根据reference有两种选择，此处必须用const char*,"xxx"的类型是const char*
	MyString(const MyString& s):string(s){}
	//1.3继承类的复制构造函数必须要显示的调用父类的复制构造函数，不然就会默认调用父类的无参构造函数
	MyString operator +(MyString & op2)
	{
		string s1 = *this;
		string s2 = op2;
		string s = s1 + s2;
		return *new MyString(s.c_str());
	}
	MyString & operator +(const char * cs2)
	{
		string str1 = *this;
		string s = str1 + cs2;
		return *new MyString(s.c_str());
	}

	MyString & operator()(int s, int l)
	{
		string str = substr(s, l);
		return *new MyString(str.c_str());
	}
};

void print_test(MyString s)
{
	cout << s << endl;
}

int myqsort(MyString * ms,int size,int length,int (*f)(const void *,const void *))
{
	vector<MyString> vec;

	for (int i=0; i< size; i++)
		vec.push_back(ms[i]);

	sort(vec.begin(), vec.end());

	for (int i=0; i<size; i++)
		//cout << vec[i] << endl;
		ms[i]=vec[i];
	return 0;

}

MyString operator+(const char * op1, MyString & op2)
{
	string st2 = op2;
	string s = op1 + st2;
	return *new MyString(s.c_str());
}

int CompareString(const void * e1, const void * e2)
{
	MyString * s1 = (MyString *)e1;
	MyString * s2 = (MyString *)e2;
	if (*s1 < *s2) return -1;
	else if (*s1 == *s2) return 0;
	else if (*s1 > *s2) return 1;
}

int main()
{
	MyString s1("abcd-"), s2, s3("efgh-");
	MyString s4(s1);
	MyString SArray[4] = { "big","me","about","take" };
	//这里等号右边的赋值操作相当于调用了MyString的转换构造函数，其实就是单一非const classname&参数的构造函数可以直接接受参数类型的变量
	cout << "1. " << s1 << s2 << s3 << s4 << endl;
	s4 = s3;
	//3.0 operator=可以直接用string类里面的
	s3 = s1 + s3;
	s1+s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A';
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;

	qsort(SArray, 4, sizeof(MyString), CompareString);
	//myqsort(SArray, 4, sizeof(MyString), CompareString);

	for (int i = 0; i < 4; ++i)
		cout << SArray[i] << endl;
	cout << s1(0, 4) << endl;
	cout << s1(5, 10) << endl;
	return 0;
}
