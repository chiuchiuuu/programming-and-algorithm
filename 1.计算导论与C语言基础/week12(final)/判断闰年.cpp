#include <iostream>
using namespace std;

int main()
{
	int a = 0;
	cin >> a;

	if (a % 400 == 0 || (a % 100 != 0 && a % 4 == 0))
	{
		cout << "Y" << endl;
	}
	else
	{
		cout << "N" << endl;
	}
	return 0;
}
