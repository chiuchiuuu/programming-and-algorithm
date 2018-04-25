#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int h = 0, r = 0;
	cin >> h >> r;
	float pi = 3.14159;
	double v = pi * r * r * h;
	int ans = ceil(20000 / v);  // 向上取整
	cout << ans << endl;
	return 0;
}

