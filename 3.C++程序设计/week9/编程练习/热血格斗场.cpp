#include <iostream>
#include <map>
using namespace std;

int main()
{
	typedef map<int, int> power_id_map;
	power_id_map members;
	members[1000000000] = 1;

	int n;
	cin >> n;
	while (n--)
	{
		int id, power;
		cin >> id >> power;
		power_id_map::iterator i_less, i_geq, i_match;
		i_less = members.lower_bound(power);
		i_geq = i_less;
		if (i_less != members.begin())
		{
			i_less--;
		}
		i_match = (power - i_less->first) <= (i_geq->first - power) ? i_less : i_geq;
		cout << id << " " << i_match->second << endl;
		members[power] = id;
	}
}