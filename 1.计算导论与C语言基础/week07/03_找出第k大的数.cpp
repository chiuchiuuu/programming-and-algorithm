#include <iostream>
using namespace std;

int main()
{
	int n = 0, k = 0;
	cin >> n >> k;
	// 没有给n的范围，所以动态创建数组
	int *a = new int[n];

	for (int i = 0; i < n; i++)
		cin >> a[i];

	for (int i = 0; i < n; i++)
	{
		// 找到比a[i]大的个数，若为k-1则a[i]是第k大的数
		int bigger = 0;
		for (int j = 0; j < n; j++)
		{
			if (a[j] > a[i])
			{
				bigger++;
			}
		}
		if (bigger == k - 1)
		{
			cout << a[i] << endl;
			break;
		}
	}
	delete[] a;
	return 0;
}
