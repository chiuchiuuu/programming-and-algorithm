#include <iostream>
#include <set>
using namespace std;

int calculatePrimeFactors(int n)
{
	set<int> PrimeFactors;
	if (n < 2)
	{
		return 0;
	}
	int tmp = n;
	for (int i = 2; i*i <= tmp; i++)
	{
		while (tmp % i == 0)
		{
			PrimeFactors.insert(i);
			tmp /= i;
		}
	}
	if (tmp != n && tmp != 1) 
	{
		PrimeFactors.insert(n);
	}
	return PrimeFactors.size();
}

struct myLess
{
	bool operator()(const int &n1, const int &n2)
	{
		int f1 = calculatePrimeFactors(n1);
		int f2 = calculatePrimeFactors(n2);
		if (f1 == f2)
		{
			return n1 < n2;
		}
		else
		{
			return f1 < f2;
		}
	}
};

int main()
{
	set<int, myLess> mySet;
	int num;
	cin >> num;
	while (num--)
	{
		for (int i = 0; i < 10; i++)
		{
			int tmp;
			cin >> tmp;
			mySet.insert(tmp);
		}
		cout << *(mySet.rbegin()) << " " << *(mySet.begin()) << endl;
		mySet.erase(mySet.begin());
		mySet.erase(--mySet.end());
	}
}