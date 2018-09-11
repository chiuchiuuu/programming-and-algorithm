#include <iostream>
using namespace std;

int main()
{
	int money = 0;
	cin >> money;
	// 用数组存储找零面额及对应的数量
	int a[6] = { 100, 50, 20, 10, 5, 1 };
	int n[6];

	for (int i = 0; i < 6; i++)
	{
		n[i] = money / a[i];
		money %= a[i];
	}

	for (int i = 0; i < 6; i++)
	{
		cout << n[i] << endl;
	}
	return 0;
}
