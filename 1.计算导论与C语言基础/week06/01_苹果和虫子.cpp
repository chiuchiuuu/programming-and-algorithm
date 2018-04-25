#include <iostream>
using namespace std;

int main()
{
	int n = 0;
	double x = 0, y = 0;
	cin >> n >> x >> y;
	int ans = n - y / x;    // 注意这里n被强制类型转化为double！
	ans = ans < 0 ? 0 : ans;  // 剩余苹果个数最小为0
	cout << ans << endl;
	return 0;
}
