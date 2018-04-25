#include <iostream>
using namespace std;
#define MAXLEN 10

int main()
{
	int n;
	int a[MAXLEN];
	cin >> n;

	int i = 0;
	do
	{
		a[i++] = n % 10;
	} while (n /= 10);

	for (i -= 1; i >= 0; i--)
		cout << a[i] << endl;
	return 0;
}

/* ԭ�汾
#include <iostream>
using namespace std;

int main()
{
	int n = 0;
	int a[3];
	cin >> n;

	for (int i = 2; i >= 0; i--)
	{
		a[i] = n % 10;
		n /= 10;
	}

	for (int i = 0; i < 3; i++)
	{
		cout << a[i] << endl;
	}
	return 0;
}
*/
