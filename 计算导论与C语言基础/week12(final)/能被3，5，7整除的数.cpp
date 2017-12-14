#include <iostream>
using namespace std;

int main()
{
	int n = 0;

	while (cin >> n)
	{
		bool flag = false;
		if (n % 3 == 0)
		{
			cout << "3" << ' ';
			flag = true;
		}
		if (n % 5 == 0)
		{
			cout << "5" << ' ';
			flag = true;
		}
		if (n % 7 == 0)
		{
			cout << "7";
			flag = true;
		}
		if (!flag)
		{
			cout << 'n';
		}
		cout << endl;
	}
	return 0;
}
