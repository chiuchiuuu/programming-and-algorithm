#include <iostream>
#include <set>

using namespace std;

int calculPrimeFactors(int n) {
	set<int>PrimeFactors;
	if (n < 2) {
		return 0;
	}
	int temp = n;
	for (int i = 2; i*i <= temp; i++) {
		while (temp%i == 0) {
			PrimeFactors.insert(i);
			temp = temp / i;
		}
	}
	if (temp != n && temp != 1) {
		PrimeFactors.insert(n);
	}
	return PrimeFactors.size();
}
struct MyLess
{
	bool operator()(const int &n1, const int &n2) {
		int f1 = calculPrimeFactors(n1);
		int f2 = calculPrimeFactors(n2);
		if (f1 == f2) {
			return n1 < n2;
		}
		else {
			return f1 < f2;
		}
	}

};
int main() 
{
	set<int, MyLess>my_set;
	int num;
	cin >> num;
	while (num--) {
		for (int i = 0; i < 10; i++) {
			int tmp;
			cin >> tmp;
			my_set.insert(tmp);
		}
		cout << *(--my_set.end()) << " " << *(my_set.begin()) << endl;
		//Returns an iterator referring to the past-the-end element in the set container.
		//故而需要--，否则会出现越界
		my_set.erase(my_set.begin());
		my_set.erase(--my_set.end());
	}
	return 0;
}