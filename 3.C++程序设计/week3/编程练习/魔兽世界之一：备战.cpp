#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string inputOrder[5] = { "dragon","ninja","iceman","lion","wolf" };
string redWarrior[5] = { "iceman","lion","wolf","ninja","dragon" };
int redInitialStrength[5];
string blueWarrior[5] = { "lion","dragon","ninja","iceman","wolf" };
int blueInitialStrength[5];

class Warrior
{
private:
	int id;
	int strength;
	int attack;
	string classes;
public:
	Warrior() {}
	Warrior(int id, int s, int atk, string classes) :
		id(id), strength(s), attack(atk), classes(classes) {}
	int getStrength()
	{
		return strength;
	}
	string getClasses()
	{
		return classes;
	}
};

class Headquater
{
private:
	string alliance;
	static int redTotalStrength;
	static int blueTotalStrength;
	static int redWarriorCount;
	static int blueWarriorCount;
	int numOfEachClasses[5] = { 0 };
	int warriorIndex;
	Warrior warrior[1000];
public:
	Headquater(string a) :alliance(a), warriorIndex(0) {}
	static void SetToalStrength(int strength)
	{
		redTotalStrength = strength;
		blueTotalStrength = strength;
	}
	static void ResetWarriorCount()
	{
		redWarriorCount = 0;
		blueWarriorCount = 0;
	}
	int makeWarrior();
};

int Headquater::redWarriorCount = 0;
int Headquater::blueWarriorCount = 0;
int Headquater::redTotalStrength = 0;
int Headquater::blueTotalStrength = 0;

int Headquater::makeWarrior()
{
	static int notMadeCount = 0;
	if (alliance == "red")
	{
		string classes = redWarrior[warriorIndex];
		int strength = redInitialStrength[warriorIndex];
		if (redTotalStrength - strength >= 0)
		{
			notMadeCount = 0;
			redTotalStrength -= strength;
			warrior[redWarriorCount] = { redWarriorCount,strength,0,classes };
			redWarriorCount++;
			numOfEachClasses[warriorIndex]++;
			cout << "red " << classes << " " << redWarriorCount << " born with strength " << strength << "," << numOfEachClasses[warriorIndex] << " " << classes << " in red headquarter" << endl;
			++warriorIndex %= 5;
			return true;
		}
		else
		{
			notMadeCount++;
			++warriorIndex %= 5;
			if (notMadeCount > 5)
			{
				notMadeCount = 0;
				return false;
			}
			return this->makeWarrior();

		}
	}
	else if (alliance == "blue")
	{
		string classes = blueWarrior[warriorIndex];
		int strength = blueInitialStrength[warriorIndex];
		if (blueTotalStrength - strength >= 0)
		{
			notMadeCount = 0;
			blueTotalStrength -= strength;
			warrior[blueWarriorCount] = { blueWarriorCount,strength,0,classes };
			blueWarriorCount++;
			numOfEachClasses[warriorIndex]++;
			cout << "blue " << classes << " " << blueWarriorCount << " born with strength " << strength << "," << numOfEachClasses[warriorIndex] << " " << classes << " in blue headquarter" << endl;
			++warriorIndex %= 5;
		}
		else
		{
			notMadeCount++;
			++warriorIndex %= 5;
			if (notMadeCount > 5)
			{
				notMadeCount = 0;
				return false;
			}
			return this->makeWarrior();
		}
	}
}





int main()
{
	int numOfTest = 0;
	cin >> numOfTest;

	for (int i = 1; i <= numOfTest; i++)
	{
		int M = 0;
		cin >> M;
		Headquater red("red"), blue("blue");
		Headquater::SetToalStrength(M);
		Headquater::ResetWarriorCount();

		for (int j = 0; j < 5; j++)
		{
			int strength;
			cin >> strength;
			for (int k = 0; k < 5; k++)
			{
				if (inputOrder[j] == redWarrior[k])
				{
					redInitialStrength[k] = strength;
				}
			}
			for (int k = 0; k < 5; k++)
			{
				if (inputOrder[j] == blueWarrior[k])
				{
					blueInitialStrength[k] = strength;
				}
			}
		}

		cout << "Case:" << i << endl;
		bool redStop = false;
		bool blueStop = false;
		int time = 0;
		while (true)
		{
			if (!redStop)
			{
				cout << setw(3) << setfill('0') << time << " ";
				redStop = !red.makeWarrior();
				if (redStop)
				{
					cout << "red headquarter stops making warriors" << endl;
				}

			}
			if (!blueStop)
			{
				cout << setw(3) << setfill('0') << time << " ";
				blueStop = !blue.makeWarrior();
				if (blueStop)
				{
					cout << "blue headquarter stops making warriors" << endl;
				}
			}
			if (redStop && blueStop)
			{
				break;
			}
			time++;
		}
	}
	return 0;
}