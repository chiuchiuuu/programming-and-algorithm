#include <iostream>
using namespace std;

int main()
{
	char sentence[500];
	int len = 0, maxLen = 0;
	int ptr = 0, maxPtr = 0;

	cin.getline(sentence, 500);

	int i = 0;
	while (sentence[i] != '\0')
	{
		if (!isalpha(sentence[i++]))
		{
			if (len > maxLen)
			{
				maxLen = len;
				maxPtr = ptr;
			}
			ptr = i;
			len = 0;
		}
		else
			len++;
	}

	for (int i = maxPtr; i < maxPtr + maxLen; i++)
	{
		cout << sentence[i];
	}

	cout << endl;
	return 0;
}
