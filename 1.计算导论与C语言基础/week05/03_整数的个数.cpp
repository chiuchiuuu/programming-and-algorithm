#include <iostream>
using namespace std;

int main()
{
	int k;
	cin >> k;
	int n1 = 0, n5 = 0, n10 = 0;
	for (int i = 0; i < k; i++)
	{
		int n;
		cin >> n;
		switch (n)
		{
			case 1:
				n1++;
				break;
			case 5:
				n5++;
				break;
			case 10:
				n10++;
				break;
		}
	}
	cout << n1 << endl;
	cout << n5 << endl;
	cout << n10 << endl;
	return 0;
}

