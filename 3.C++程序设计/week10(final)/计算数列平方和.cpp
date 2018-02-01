#include <iostream>
using namespace std;

// 在此处补充你的代码
int sum(const int *array, int num, int(*func)(int n))
{
	int sum = 0;
	for (int i = 0; i < num; i++)
	{
		sum += func(array[i]);
	}
	return sum;
}

int sqr(int n)
{
	return n * n;
}

int main() {
	int t, n, a[0x100];
	cin >> t;
	for (int c = 0; c < t; ++c) {
		cin >> n;
		for (int i = 0; i < n; ++i) cin >> a[i];
		cout << sum(a, n, sqr) << endl;
	}
	return 0;
}