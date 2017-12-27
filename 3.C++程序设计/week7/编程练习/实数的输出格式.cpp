#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double real;
	cin >> real;

	cout << fixed << setprecision(5) << real << endl;
	cout << scientific << setprecision(7) << real << endl;
	return 0;
}