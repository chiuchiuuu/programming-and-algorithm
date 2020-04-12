#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

int price[10000], needs[10000];
int s, N;
long long res;

int main()
{
    cin >> N >> s;
    for (int i = 0; i < N; i++)
        scanf("%d%d", &price[i], &needs[i]);
    int lowPrice = price[0];
    res += lowPrice * needs[0];

    for (int i = 1; i < N; i++)
    {
        lowPrice = min(lowPrice + s, price[i]);
        res += lowPrice * needs[i];
    }
    cout << res << endl;
}