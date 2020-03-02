#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int ans[30][30], f[30], d[30], t[30];
int main()
{
    int h, n;
    cin >> n;
    while (true)
    {
        if (n == 0)
            break;

        cin >> h;
        h *= 12;
        memset(ans, 0, sizeof(ans));
        memset(f, 0, sizeof(f));
        memset(t, 0, sizeof(t));
        memset(d, 0, sizeof(d));

        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &f[i]);
        }
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &d[i]);
        }
        for (int i = 1; i < n; ++i)
        {
            scanf("%d", &t[i]);
        }

        int ht, ft[30];
        for (int ed = 1; ed <= n; ++ed) //枚举最远会走到哪个湖
        {
            memset(ft, 0, sizeof(ft));
            for (int i = 1; i <= ed; ++i)
            {
                ft[i] = f[i];
            }       //ft作为f的临时记录
            ht = h; //记录剩余时间
            for (int i = 1; i < ed; ++i)
            {
                ht -= t[i]; //减去路上的时间花费
            }
            //接下来开始模拟钓鱼过程
            int k, emp = 1;             //emp标记连续的已经空了的湖
            while (ht > 0 && emp <= ed) //时间用完或湖空为止
            {
                k = 1;
                for (int j = emp; j <= ed; ++j)
                {
                    if (ft[j] > ft[k])
                    {
                        k = j;
                    }
                } //找出最优的湖

                ans[ed][0] += ft[k]; //此次收获+ft[k]
                ++ans[ed][k];        //记录在k湖花费了1单位时间
                --ht;                //时间消耗1单位
                ft[k] -= d[k];
                ft[k] = ft[k] > 0 ? ft[k] : 0;
                for (int j = emp; j <= ed; ++j)
                {
                    if (ft[j] == 0)
                        ++emp;
                    else
                        break;
                } //检查是否ed前的湖都已空
            }
            if (ht > 0)
                ans[ed][1] += ht; //若时间有剩余
        }

        int a = 1;
        for (int i = 2; i <= n; ++i)
        {
            if (ans[i][0] > ans[a][0])
                a = i;
        } //找出收益最大的方案

        for (int i = 1; i <= n; ++i)
        {
            cout << ans[a][i] * 5;
            if (i != n)
                cout << ", ";
        }
        cout << endl;
        cout << "Number of fish expected: " << ans[a][0] << endl;

        cin >> n;
        if (n != 0)
            cout << endl;
    }
    return 0;
}
// Sick this week, no more time to do code.
// Thanks to this website 47.91.197.53/acm/post/6268a