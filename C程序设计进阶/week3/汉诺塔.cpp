#include <iostream>
using namespace std;

void move(int n, char a, char b, char c)
{
	// move n plate from a pass b to c
	if (n == 1)
	{
		cout << a << "->" << c << endl;
	}
	else
	{
		move(n - 1, a, c, b);
		move(1, a, b, c);
		move(n - 1, b, a, c);
	}
}

int main()
{
	int n = 0;
	cin >> n;

	move(n, 'A', 'B', 'C');

	return 0;
}
