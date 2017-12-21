#include <iostream>
#include <string>
using namespace std;

// dragon 、ninja、iceman、lion、wolf
int initialStrength[5] = { 0 };

class Headquater
{
private:
	string alliance;
	static int redWarriorCount;
	static int blueWarriorCount;
	string redOrder[5] = ["iceman", "lion", "wolf", "ninja", "dragon"];
public:
	Headquater(string a) :alliance(a) {}
};

class Warrior
{
private:
	int id;
	int strength;
	int attack;
	string classes;
public:
	Warrior(int id, int s, int atk, string classes) :
		id(id), strength(s), attack(atk), classes(classes) {}
	int getStrength()
	{
		return strength;
	}
	string getClasses
	{
		return classes;
	}
};



int main()
{
	int numOfTest = 0;
	cin >> numOfTest;

	for (int i = 0; i < numOfTest; i++)
	{
		int M = 0;
		cin >> M;
		for (int j = 0; j < 5; j++)
		{
			cin >> initialHP[i];
		}

		cout << "Case:" << i << endl;


	}
	return 0;
}