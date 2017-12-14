/*
描述

某医院想统计一下某项疾病的获得与否与年龄是否有关，需要对以前的诊断记录进行整理。

输入

共2行，第一行为过往病人的数目n（0 < n <= 100)，第二行为每个病人患病时的年龄。

输出

每个年龄段（分四段：18以下，19-35，36-60，大于60注意看样例输出的格式）的患病人数占总患病人数的比例，以百分比的形式输出，精确到小数点后两位（double）。关于c++的格式化的输入输出，请参考：http://www.cplusplus.com/reference/iomanip。也可以在网上搜索一下，资料很多的。
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	float total = 0;
	int n[4] = { 0 };
	cin >> total;

	for (int i = 0; i < total; i++)
	{
		int age = 0;
		cin >> age;
		age <= 18 ? n[0]++ :
			age <= 35 ? n[1]++ :
				age <= 60 ? n[2]++ : n[3]++;
	}

	cout << "1-18: " << fixed << setprecision(2) << n[0] / total * 100 << "%" << endl;
	cout << "19-35: " << fixed << setprecision(2) << n[1] / total * 100 << "%" << endl;
	cout << "36-60: " << fixed << setprecision(2) << n[2] / total * 100 << "%" << endl;
	cout << "60-: " << fixed << setprecision(2) << n[3] / total * 100 << "%" << endl;
	return 0;
}
