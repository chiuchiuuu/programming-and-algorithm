#include<iostream>
#include<map>
using namespace std;

typedef multimap<int, int>power_id_map;

int main() {
	int n;
	cin >> n;
	power_id_map members;
	members.insert(make_pair(1000000000, 1));
	while (n--)
	{
		int id, power;
		cin >> id >> power;
		power_id_map::iterator i = members.lower_bound(power);
		power_id_map::iterator i_upper = i;
		if (i != members.begin())
			i--;
		members.insert(make_pair(power, id));
		i = (power - i->first) <= (i_upper->first - power) ? i : i_upper;
		cout << id << " " << i->second << endl;

	}
}