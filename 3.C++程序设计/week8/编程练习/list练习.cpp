#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;

int main()
{
	vector<list<int>> MyList(10000);
	int n;
	cin >> n;
	while (n--)
	{
		string str;
		cin >> str;
		if (str == "new")
		{
			int id;
			cin >> id;
		}
		else if (str == "add")
		{
			int id, num;
			cin >> id >> num;
			MyList[id].push_back(num);
		}
		else if (str == "merge")
		{
			int id1, id2;
			cin >> id1 >> id2;
			//MyList[id1].merge(MyList[id2]);
			MyList[id1].splice(MyList[id1].end(), MyList[id2]);
		}
		else if (str == "unique")
		{
			int id;
			cin >> id;
			MyList[id].sort();
			MyList[id].unique();
		}
		else if (str == "out")
		{
			int id;
			cin >> id;
			MyList[id].sort();
			list<int>::iterator i;
			for (i = MyList[id].begin(); i != MyList[id].end(); i++)
			{
				cout << *i << " ";
			}
			cout << endl;
		}
	}
	return 0;
}
