#include <iostream>
using namespace std;

int main()
{
	int n = 0;
	cin >> n;


	while (n--)
	{
		float dist = 0;
		cin >> dist;
		if ((dist / 3 + 50) < (dist / 1.2f))
		{
			cout << "Bike" << endl;
		}
		else if (((dist / 3 + 50) > (dist / 1.2f)))
		{
			cout << "Walk" << endl;
		}
		else
		{
			cout << "All" << endl;
		}
	}
	return 0;
}
