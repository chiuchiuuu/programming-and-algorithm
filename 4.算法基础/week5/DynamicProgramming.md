## 最长上升子序列

![1570304544428](E:\programming-and-algorithm\4.算法基础\week5\pic\最长上升子序列1.jpg)

![1570304665807](E:\programming-and-algorithm\4.算法基础\week5\pic\最长上升子序列.jpg)

### 解题思路：

1. 找子问题：

   “求以$a_k$（k=1, 2, 3…N）为终点的最长上升子序列的长度”
   一个上升子序列中最右边的那个数，称为该子序列的“终点”。
   虽然这个子问题和原问题形式上并不完全一样，但是只要这N个子问题都解决了，那么这N个子问题的解中，最大的那个就是整个问题的解。

2. 确定状态

   子问题只和一个变量-- 数字的位置相关。因此序列中数的位置k 就是“状态”，而状态 k 对应的“值”，就是以 $a_k$ 做为“终点”的最长上升子序列的长度。状态一共有N个。

3. 状态转移方程

   maxLen (k)表示以$a_k$做为“终点”的最长上升子序列的长度那么：
   初始状态：$maxLen (1) = 1$
   $maxLen (k) = max { maxLen (i)：1<=i < k and ai < ak且 k≠1 } + 1$
   若找不到这样的i,则$maxLen(k) = 1$
   maxLen(k)的值，就是在$a_k$左边，“终点”数值小于$a_k$ ，且长度最大的那个上升子序列的长度再加1。因为ak左边任何“终点”小于ak的子序列，加上ak后就能形成一个更长的上升子序列。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1010;
int a[MAXN];
int maxLen[MAXN];
int main(){
    int N;
    cin>>N;
    for(int i=1; i<=N; i++)
    {
        cin>>a[i];
        maxLen[i]=1;
    }
    for(int i=2; i<=N; ++i)
    {//每次求以第i个数为终点的最长上升子序列的长度
        for (int j = 1; j <i; j++)
        {
            if(a[i]>a[j])
            {
                maxLen[i]=max(maxLen[i], maxLen[j]+1);

            }
        }
    }
    cout<<*max_element(maxLen+1, maxLen+N+1);
    return 0;
}
```

## 方盒游戏

![1570307694315](pic/方盒游戏1.jpg)

![1570307724114](pic/%E6%96%B9%E7%9B%92%E6%B8%B8%E6%88%8F2.png)

<img src="pic/%E6%96%B9%E7%9B%92%E6%B8%B8%E6%88%8F3.jpg" alt="1570307858134" style="zoom:50%;" />

问题可以描述为：click_box(i, j, ex_len)，表示：大块j的已经有了长度为ex_len的大块（该大块可能是在合并的过程中形成的），且j颜色和ex_len相同，在此情况下将i到j以及ex_len都消除所能得到的最高分。

问题转换为 click_box(0, n-1, 0)

在求解click_box(i, j, ex_len）时一共有两种可能，取最优者。假设j和ex_len和并后的大块为Q

1. 将Q直接消除，这种做法能得到的最高分为：

​		click_box$(i, j-1, 0)+ (len[j] + $ex_len$)^2$

2. 期待Q以后能和左边的某个同色大块合并。需要枚举可能和Q合并的大块。假设让大块K和Q合并，此时的分数为:

   click_box(i, k, len[j]+ex_len) + click_box( k+1, j-1, 0)

   分数为两部分构成，合并后的分数，以及为了合并消除K和Q之间小块的分数

```cpp
#include <iostream>
#include <cstring>
using namespace std;

struct Block
{
    int color;
    int len;
};
struct Block segment[200];
int score[200][200][200]; //store the computation result, avoid the repeated computation
int click_box(int start, int end, int extra_len)
{
    int i, result, temp;
    if (score[start][end][extra_len] > 0)
        return score[start][end][extra_len];
    result = segment[end].len + extra_len;
    result = result * result;
    if (start == end)
    {
        score[start][end][extra_len] = result;
        return score[start][end][extra_len];
    }
    result += click_box(start, end - 1, 0);
    i = end - 1;
    for (i = end - 1; i >= start; i--)
    {
        if (segment[i].color != segment[end].color)
            continue;
        temp = click_box(start, i, segment[end].len + extra_len) + click_box(i + 1, end - 1, 0);
        if (temp <= result)
            continue;
        result = temp;
    }
    score[start][end][extra_len] = result;
    return score[start][end][extra_len];
}
int main()
{
    int t, n, i, j, end, color;
    cin >> t;
    for (i = 0; i < t; i++)
    {
        cin >> n;
        end = 0;
        cin >> segment[end].color;
        segment[end].len = 1;
        for (j = 1; j < n; j++)
        {
            cin >> color;
            if (color == segment[end].color)
                segment[end].len++;
            else
            {
                end++;
                segment[end].color = color;
                segment[end].len = 1;
            }
        }
        memset(score, 0, sizeof(score));
        cout << "Case " << i + 1 << ": " << click_box(0, end, 0) << endl;
    }
    return 0;
}
```



