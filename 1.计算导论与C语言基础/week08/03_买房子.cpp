#include <iostream>
using namespace std;

int main()
{
	int N = 0, K = 0;
	while (cin >> N >> K)
	{
		int money = N;
		float price = 200;
		bool canBuy = false;
		for (int i = 1; i <= 20; i++)
		{
			if (money >= price)
			{
				cout << i << endl;
				canBuy = true;
				break;
			}
			money += N;
			price *= (1 + K / 100.0);
		}
		if (!canBuy)
		{
			cout << "Impossible" << endl;
		}
	}
	return 0;
}
