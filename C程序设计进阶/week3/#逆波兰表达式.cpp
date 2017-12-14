#include <iostream>
using namespace std;

double notation()
{
	char str[10];
	cin >> str;
	switch (str[0])
	{
	case '+':
		return notation() + notation();
	case '-':
		return notation() - notation();
	case '*':
		return notation() * notation();
	case '/':
		return notation() / notation();
	default:
		return atof(str);
	}
}

int main()
{
	cout << notation() << endl;
	return 0;
}
