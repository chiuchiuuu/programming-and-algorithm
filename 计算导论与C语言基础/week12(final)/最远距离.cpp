#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	int n = 0;
	cin >> n;
	double coordinate[100][2];

	for (int i = 0; i < n; i++)
	{
		cin >> coordinate[i][0] >> coordinate[i][1];
	}

	double maxDist = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			double dist = sqrt(pow(coordinate[i][0] - coordinate[j][0], 2) + pow(coordinate[i][1] - coordinate[j][1], 2));
			if (dist > maxDist)
			{
				maxDist = dist;
			}
		}
	}

	cout << fixed << setprecision(4) << maxDist << endl;
	return 0;
}
