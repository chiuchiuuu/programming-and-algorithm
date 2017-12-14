#include <iostream>
using namespace std;

int main() {
	char str1[80], str2[80];

	cin.getline(str1, 80);
	cin.getline(str2, 80);

	// 把字母全转换为大写，'a'对应97，大小写间隔32
	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] >= 97)
		{
			str1[i] -= 32;
		}
	}
	for (int i = 0; str2[i] != '\0'; i++)
	{
		if (str2[i] >= 97)
		{
			str2[i] -= 32;
		}
	}

	int i = 0;
	char result;
	while (str1[i] != '\0' && str1[i] == str2[i])
	{
		i++;
	}
	if (str1[i] > str2[i])
	{
		result = '>';
	}
	else if (str1[i] < str2[i])
	{
		result = '<';
	}
	else
	{
		result = '=';
	}

	cout << result << endl;

	return 0;
}
