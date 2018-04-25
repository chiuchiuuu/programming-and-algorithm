#include <iostream>
using namespace std;
#define LEN 10

int main()
{
	int a[LEN];
	for (int i = 0; i < 10; i++)
		cin >> a[i];

	for (int i = 0; i < LEN - 1; i++)
	{
		for (int j = 0; j < LEN - i - 1; j++)
		{
			if (a[j] % 2 == 0 && a[j + 1] % 2 == 1 || (a[j] % 2 == a[j + 1] % 2 && a[j] > a[j + 1]))
			{
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}

		}
	}

	for (int i = 0; i < LEN; i++)
		cout << a[i] << " ";
	cout << endl;
	
	return 0;
}
