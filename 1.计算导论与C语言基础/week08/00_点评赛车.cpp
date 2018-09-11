#include <iostream>
using namespace std;

int main()
{
	for (int best = 1; best <= 4; best++)
	{
		bool a = (best == 2);
		bool b = (best == 4);
		bool c = (best != 3);
		bool d = !b;
		// 只有一个专家说对
		if (a + b + c + d == 1)
		{
			cout << best << endl;
			if (a)
				cout << "A" << endl;
			else if (b)
				cout << "B" << endl;
			else if (c)
				cout << "C" << endl;
			else if (d)
				cout << "D" << endl;
		}
	}
	return 0;
}
