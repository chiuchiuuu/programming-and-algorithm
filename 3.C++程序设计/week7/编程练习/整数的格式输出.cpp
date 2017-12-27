#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int a;
	cin >> a;
	cout << hex << a << endl;
	cout << dec << setw(10) << setfill('0') << a << endl;
	return 0;
}