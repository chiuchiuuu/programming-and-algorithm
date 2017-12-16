/*
编程题＃1：分配病房
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
某个科室的病房分为重症和普通，只有当病人的疾病严重程度超过了入住重症病房的最低严重值，才可以安排入住重症病房。

现在要求设计一个程序，给病人安排好病房。疾病的严重程度用0到10来表示，0表示小毛病，10表示非常严重。

输入
第一行输入病人的个数m(m < 50)，以及安排住入重症病房的最低严重值a

紧接着m行，每行表示病人编号（三个位，用0补齐）及其疾病的严重程度（浮点数，1位小数）。

每个病人的疾病严重程度都不一样。

输出
要求按照病人的严重程度输出住在重症病房里的病人的编号

注意：

如果当前所有病人的严重程度并不满足住在重症病房里，则输出“None.”（不包括引号）
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int m = 0;
	float a = 0;
	cin >> m >> a;

	int id[50];
	float acuity[50];
	int num = 0; //重症病人个数
	for (int i = 0; i < m; i++)
	{
		int tmpId;
		float tmpAcuity;
		cin >> tmpId >> tmpAcuity;
		if (tmpAcuity > a)
		{
			id[num] = tmpId;
			acuity[num] = tmpAcuity;
			num++;
		}
	}
	if (num == 0)
	{
		cout << "None." << endl;
		return 0;
	}
	else
	{
		for (int i = 0; i < num; i++)
		{
			for (int j = 1; j < num; j++)
			{
				if (acuity[j] > acuity[j - 1])
				{
					float tmp1 = acuity[j];
					acuity[j] = acuity[j - 1];
					acuity[j - 1] = tmp1;
					int tmp2 = id[j];
					id[j] = id[j - 1];
					id[j - 1] = tmp2;
				}
			}
		}
	}

	for (int i = 0; i < num; i++)
	{
		cout << setw(3) << setfill('0') << id[i] << ' ';
		cout << fixed << setprecision(1) << acuity[i] << endl;
	}
	return 0;
}
