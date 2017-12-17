/*
编程题＃2：字符串中次数第2多的字母
来源: POJ (Coursera声明：在POJ上完成的习题将不会计入Coursera的最后成绩。)

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
输入一串长度不超过500个符号的字符串，输出在串中出现第2多的英语字母(大小写字母认为相同)和次数（如果串中有其它符号，则忽略不考虑）。如果有多个字母的次数都是第2多，则按串中字母出现的顺序输出第1个。

例 ab&dcAab&c9defgb

这里，a 和 b都出现3次，c和d都出现2次，e、f 和 g 各出现1次，其中的符号&和9均忽略不考虑。因此，出现第2多的应该是 c 和 d，但是 d 开始出现的位置在 c 的前面，因此，输出为

D+d:2

(假定在字符串中，次数第2多的字母总存在)

输入
一个字符串

输出
大写字母+小写字母:个数
*/

#include <iostream>
#include <cctype>
using namespace std;

struct Alphabet
{
	char letter;  // 字母，不区分大小写
	int fisrtShowIndex;  // 第一次出现的index
	int count;  // 字母出现的次数
	bool show; // 字母是否出现
};

int main()
{
	char str[500];
	cin.getline(str, 500);

	// 字母表初始化
	Alphabet alphabet[26];
	for (int i = 0; i < 26; i++)
	{
		//alphabet[i].letter = char(97 + i);
		//alphabet[i].fisrtShowIndex = -1;
		//alphabet[i].count = 0;
		alphabet[i] = { char(97 + i),0,0,false };
	}

	// 处理字符串
	for (int i = 0; str[i] != '\0'; i++)
	{
		str[i] = tolower(str[i]);
		if (isalpha(str[i]))
		{
			int index = str[i] - 'a';
			alphabet[index].count++;
			if (!alphabet[index].show)
			{
				alphabet[index].fisrtShowIndex = i;
				alphabet[index].show = true;
			}
		}
	}

	// 找出第二大且最先出现的字母
	Alphabet max = { 0,0,0 }, second = { 0,501,0 };
	for (int i = 0; i < 26; i++)
	{
		if (alphabet[i].count > max.count)
		{
			max = alphabet[i];
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (alphabet[i].show && alphabet[i].count < max.count)
		{
			if (alphabet[i].count > second.count)
			{
				second = alphabet[i];
			}
			else if (alphabet[i].count == second.count && alphabet[i].fisrtShowIndex < second.fisrtShowIndex)
			{
				second = alphabet[i];
			}
		}
	}
	cout << (char)toupper(second.letter) << '+' << second.letter << ':' << second.count << endl;
	return 0;
}
