#include <iostream>
#include <string>
using namespace std;

// 在此处补充你的代码
template<class T>
class  CMyistream_iterator : public iterator<input_iterator_tag, T> {
private:
	T n;
	istream & os;
public:
	CMyistream_iterator(istream &os) : os(os) {
		os >> n;
	}
	T operator*() {
		return n;
	}
	void operator++(int) {
		os >> n;
	}
	//构造函数执行过程中就会要求输入，然后每次执行++，则读取输入流中的下一个项目，执行 * 则返回上次从输入流中读取的项目

};
int main()
{
	CMyistream_iterator<int> inputInt(cin);
	int n1, n2, n3;
	n1 = *inputInt; //读入 n1
	int tmp = *inputInt;
	cout << tmp << endl;
	inputInt++;
	n2 = *inputInt; //读入 n2
	inputInt++;
	n3 = *inputInt; //读入 n3
	cout << n1 << "," << n2 << "," << n3 << endl;
	CMyistream_iterator<string> inputStr(cin);
	string s1, s2;
	s1 = *inputStr;
	inputStr++;
	s2 = *inputStr;
	cout << s1 << "," << s2 << endl;
	return 0;
}