#include <iostream>
using namespace std;

int main()
{
	int n = 0;
	cin >> n;

	for (int i = 10; i < n; i++)
	{
		int num = i;
		int sumOfDigits = 0;
		while (num > 0)
		{
			sumOfDigits += num % 10;
			num /= 10;
		}

		if (i % sumOfDigits == 0)
		{
			cout << i << endl;
		}
	}
	return 0;
}
