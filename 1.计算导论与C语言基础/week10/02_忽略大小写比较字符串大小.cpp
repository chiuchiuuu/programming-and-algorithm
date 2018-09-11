#include <iostream>
using namespace std;

int main() {
	char str1[80], str2[80];

	cin.getline(str1, 80);
	cin.getline(str2, 80);

	for (int i = 0; str1[i] != '\0'; i++)
		str1[i] = tolower(str1[i]);
	for (int i = 0; str2[i] != '\0'; i++)
		str2[i] = tolower(str2[i]);


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
