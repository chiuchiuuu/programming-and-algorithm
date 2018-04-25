#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	float total = 0;
	int n[4] = { 0 };
	cin >> total;

	for (int i = 0; i < total; i++)
	{
		int age = 0;
		cin >> age;
		if (age <= 18)
			n[0]++;
		else if (age <= 35)
			n[1]++;
		else if (age <= 60)
			n[2]++;
		else
			n[3]++;
	}

	cout << "1-18: " << fixed << setprecision(2) << n[0] / total * 100 << "%" << endl;
	cout << "19-35: " << fixed << setprecision(2) << n[1] / total * 100 << "%" << endl;
	cout << "36-60: " << fixed << setprecision(2) << n[2] / total * 100 << "%" << endl;
	cout << "60-: " << fixed << setprecision(2) << n[3] / total * 100 << "%" << endl;
	return 0;
}
