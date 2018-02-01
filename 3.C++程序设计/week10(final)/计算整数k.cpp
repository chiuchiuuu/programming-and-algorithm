#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	int ncase;
	cin >> ncase;
	while (ncase--)
	{
		int n, i, j;
		cin >> n >> i >> j;
		bitset<32> bitset_n(n);
		bitset<32> bitset_k(0);
		bitset_k[i] = bitset_n[i];
		bitset_k[j] = ~bitset_n[j];
		for (int m = i + 1; m < j; m++)
		{
			bitset_k.set(m);
		}
		cout << hex << bitset_k.to_ulong() << endl;
	}
	return 0;
}