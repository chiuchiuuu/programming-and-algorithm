#include <iostream>
#include <cstring>
using namespace std;

int res[31];

int f(int n)
{
	if (n == 0)
	{
		return 1;
	}
	if (n == 2)
	{
		return 3;
	}
	if (res[n] != -1)
	{
		return res[n];
	}
	else
	{
		int tmp = 4 * f(n - 2) - f(n - 4);
		res[n] = tmp;
		return tmp;
	}
}

int main()
{
	memset(res, -1, sizeof(res));
	int n;
	while (cin >> n && n != -1)
	{
		cout << f(n) << endl;
	}
	return 0;
}