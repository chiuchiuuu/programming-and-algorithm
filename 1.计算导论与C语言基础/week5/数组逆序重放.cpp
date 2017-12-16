#include <iostream>
using namespace std;

int main()
{
	int n;
	int a[100];
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		int x = 0;
		cin >> x;
		a[n - i - 1] = x;
	}

	for (int i = 0; i < n; i++)
	{
		cout << a[i] << ' ';
	}
	return 0;
}
