#include <iostream>
#include <math.h>
using namespace std;
#define LL long long
#define MAX 310

int T, N;
int MIN;
int flag;
int number[10], son[10], ans[10], ans_num;

void Dfs(int bit, int sum, int num)
{ //bit表示当前还剩余的位数，sum当前的累积和,num是当前的深度
    if (sum > T)
        return; //无法裁剪，直接返回
    if (bit == 0)
    { //bit为0，说明裁剪完成，开始判定是否是最优解
        if (T - sum == MIN)
        {
            flag = -1;
            return; //有多个最优解，打印异常
        }
        if (T - sum > MIN)
            return; //不是最优解，剪枝返回
        for (int i = 0; i < num; i++)
            ans[i] = son[i]; //相对最优解的存储，将裁剪的每一段纸的数据存储在相对优解中
        MIN = T - sum;       //更新最优解
        ans_num = num;       //更新最游记的深度，  即裁剪的纸的份数
        flag = 1;            // flag = 1 表示存在一个解
        return;              //结束这个搜索
    }
    int temp = 0;
    for (; bit > 0; bit--)
    {                                      //搜索核心，给出剩余纸张的位数，模拟剪裁
        temp = temp * 10 + number[bit];    //用temp来模拟所有可能的裁剪方式
        son[num] = temp;                   //son数组记录了当前裁剪方法中的每一段纸的值
        Dfs(bit - 1, sum + temp, num + 1); //对剩余的知进行下一次搜索，纸张份数加1
    }
}
int main()
{
    while (cin >> T >> N)
    {
        if (T == 0 && N == 0)
            break;
        if (T == N)
        {
            cout << T << " " << N << endl;
            continue;
        }
        int num = 0;
        MIN = 1 << 30;
        flag = 0;
        while (N)
        {
            number[++num] = N % 10;
            N /= 10;
        }
        Dfs(num, 0, 0);
        if (flag == 0)
        {
            cout << "error" << endl;
        }
        else
        {
            if (flag == -1)
                cout << "rejected" << endl;
            else
            {
                cout << T - MIN << " ";
                for (int i = 0; i < ans_num - 1; i++)
                    cout << ans[i] << " ";
                cout << ans[ans_num - 1] << endl;
            }
        }
    }
    return 0;
}
//references: https://blog.csdn.net/iwts_24/article/details/79728793