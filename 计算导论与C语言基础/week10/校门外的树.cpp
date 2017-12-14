#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int L = 0, M = 0;
	cin >> L >> M;
	bool remove[10001] = { 0 };
	for (int i = 0; i < M; i++)
	{
		int start, end;
		cin >> start >> end;
		for (int j = start; j <= end; j++)
		{
			remove[j] = true;
		}
	}

	int left = 0;
	for (int i = 0; i <= L; i++)
	{
		if (!remove[i])
		{
			left++;
		}
	}
	cout << left;
	return 0;
}
