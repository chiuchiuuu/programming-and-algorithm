#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	int a = 0, b = 0;
	char operation;

	cin >> a >> b >> operation;

	int result = 0;

	switch (operation)
	{
	case '+':
		result = a + b;
		break;
	case '-':
		result = a - b;
		break;
	case '*':
		result = a * b;
		break;
	case '/':
		if (b == 0)
		{
			cout << "Divided by zero!" << endl;
			return 0;
		}
		else
		{
			result = a / b;
		}
		break;
	default:
		cout << "Invalid operator!" << endl;
		return 0;
	}

	cout << result << endl;
	return 0;
}
