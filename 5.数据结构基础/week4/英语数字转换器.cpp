#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

string str[32] = { "negative", "zero", "one", "two", "three", "four","five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred", "thousand", "million" };
int num[32] = { -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50, 60, 70, 80, 90, 100, 1000, 1000000 };
map<string, int> num_str;
vector<string> words;

int main()
{
	for (int i = 0; i < 32; i++)
		num_str[str[i]] = num[i];

	string line;
	while (getline(cin, line) && line != "")
	{
		line += ' ';  // 行末加空格方便切割
		int pos;
		int sign = 1;
		int val = 0;
		while ((pos = line.find(' ')) != string::npos)
		{
			string word = line.substr(0, pos);
			words.push_back(word);
			line.erase(0, pos + 1);
		}
		vector<string>::iterator it = words.begin();

		if (*it == "negative")
		{
			sign = -1;
			it++;
		}

		int tmp = 0;
		while (it != words.end())
		{
			if (*it == "hundred")
			{
				tmp *= num_str[*it];
			}
			else if (*it == "thousand" || *it == "million")
			{
				tmp *= num_str[*it];
				val += tmp;
				tmp = 0;
			}
			else
			{
				tmp += num_str[*it];
			}
			it++;
		}
		val += tmp;
		cout << sign * val << endl;
		words.clear();
	}

}