/*
编程题＃4：Tomorrow never knows？

来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述

甲壳虫的《A day in the life》和《Tomorrow never knows》脍炙人口，如果告诉你a day in the life,真的会是tomorrow never knows?相信学了计概之后这个不会是难题，现在就来实现吧。

读入一个格式为yyyy-mm-dd的日期（即年－月－日），输出这个日期下一天的日期。可以假定输入的日期不早于1600-01-01，也不晚于2999-12-30。

输入

输入仅一行，格式为yyyy-mm-dd的日期。

输出

输出也仅一行，格式为yyyy-mm-dd的日期

样例输入
2010-07-05

样例输出
1
2010-07-06
*/

#include <iostream>
#include <iomanip>
using namespace std;

bool isLeapYear(int year);
bool isEndOfMonth(int month, int day, bool isLeapYear);
bool isEndOfYear(int month, int day);

int main()
{
	int year, month, day;
	char dash;
	cin >> year >> dash >> month >> dash >> day;
	if (isEndOfMonth(month, day, isLeapYear(year)))
	{
		if (isEndOfYear(month, day))
		{
			year++;
			month = 1;
			day = 1;
		}
		else
		{
			month++;
			day = 1;
		}
	}
	else
	{
		day++;
	}
	cout << year << '-'
		<< setfill('0') << setw(2) << month << '-'
		<< setfill('0') << setw(2) << day << endl;
	return 0;
}

bool isLeapYear(int year)
{
	return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

bool isEndOfMonth(int month, int day, bool isLeapYear)
{
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (isLeapYear)
	{
		months[1] = 29;
	}

	for (int i = 0; i < 12; i++)
	{
		if (day == months[month - 1])
		{
			return true;
		}
	}
	return false;
}

bool isEndOfYear(int month, int day)
{
	return month == 12 && day == 31;
}
