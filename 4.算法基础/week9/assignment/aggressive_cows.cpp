#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, c;
long long cows[100007];
bool check(long long mid)
{
    int cnt = 1;
    int cow = cows[0];
    for (int i = 1; i < n; i++)
    {
        if (cows[i] - cow >= mid)
        {
            cnt++;
            cow = cows[i];
        }
        if (cnt >= c)
            return true;
    }
    return false;
}
int main()
{
    cin >> n >> c;
    for (int i = 0; i < n; i++)
        scanf("%lld", &cows[i]);
    sort(cows, cows + n);
    long long left = cows[0], right = cows[n - 1];
    while (right - left > 1)
    {
        long long mid = (left + right) / 2;
        if (check(mid))
            left = mid;
        else
        {
            right = mid;
        }
    }
    cout << left << endl;
    return 0;
}