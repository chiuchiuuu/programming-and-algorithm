#include <iostream>
#include <set>
#include <string>
using namespace std;

multiset<int> int_multiset;
set<int> mySet;

void add(int x)
{
	int_multiset.insert(x);
	mySet.insert(x);
	cout << int_multiset.count(x) << endl;
}

void del(int x)
{
	int tmp = int_multiset.count(x);
	int_multiset.erase(x);
	cout << tmp << endl;
}

void ask(int x)
{
	set<int>::iterator i = mySet.find(x);
	cout << (int)(i != mySet.end()) << " " << int_multiset.count(x) << endl;
}

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		string op;
		int x;
		cin >> op >> x;
		if (op == "add")
		{
			add(x);
		}
		else if (op == "del")
		{
			del(x);
		}
		else if (op == "ask")
		{
			ask(x);
		}
	}
	return 0;
}