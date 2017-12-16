#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int N = 0;
	int num[15000];
	while (cin >> N, N)
	{
		for (int i = 0; i < N; i++)
		{
			cin >> num[i];
		}
		sort(num, num + N);
		if (N % 2 == 1)
		{
			cout << num[N / 2] << endl;
		}
		else
		{
			cout << (num[N / 2 - 1] + num[N / 2]) / 2 << endl;
		}
	}
	return 0;
}
