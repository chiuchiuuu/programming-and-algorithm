#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string warriorClasses[5] = { "dragon","ninja","iceman","lion","wolf" };
int initialStrength[5] = { 0 };
int redOrder[5] = { 2,3,4,1,0 };
int blueOrder[5] = { 3,0,1,2,4 };
int TIME = 0;

class Warrior;
class Headquarter
{
private:
	string alliance;
	int TotalStrength;
	int numOfWarrior;
	int numOfEachClasses[5] = { 0 };
	int ProduceOrder[5];
	int ProduceIndex;
	friend Warrior;
	Warrior *warrior[1000] = { NULL };
	bool stopMakingWarrior;
public:
	Headquarter(string a) :alliance(a) {}
	void init(int ts, int po[])
	{
		numOfWarrior = 0;
		ProduceIndex = 0;
		TotalStrength = ts;
		stopMakingWarrior = false;
		for (int i = 0; i < 5; i++)
		{
			ProduceOrder[i] = po[i];
		}
	}
	~Headquarter()
	{
		for (int i = 0; i < numOfWarrior; i++)
		{
			delete warrior[i];
		}
	}
	int getTotalStrength() { return TotalStrength; }
	bool makeWarrior();
};



class Warrior
{
protected:
	Headquarter *hq;
	int id;
	int strength;
	int attack;
	int weapon[3]; // sword, bomb, arrow
	string weaponName[3] = { "sword","bomb","arrow" };
	string classes;
	int classesID;
public:
	Warrior() {}
	Warrior(Headquarter *hq, int id, int s, int atk, int cid) :hq(hq), id(id), strength(s), attack(atk), classesID(cid)
	{
		classes = warriorClasses[classesID];
	}
	virtual void printBornMessage()
	{
		cout << setw(3) << setfill('0') << TIME << " ";
		cout << hq->alliance << " " << classes << " " << id << " born with strength " << strength << "," << hq->numOfEachClasses[classesID] << " " << classes << " in " << hq->alliance << " headquarter" << endl;
	}
	int getStrength()
	{
		return strength;
	}
	string getClasses()
	{
		return classes;
	}
};

class Dragon : public Warrior
{
private:
	double morale; // Ê¿Æø
public:
	Dragon(Headquarter *hq, int id, int strength, int atk, double m, int cid = 0) :Warrior(hq, id, strength, atk, cid), morale(m)
	{ 
		classes = "dragon"; 
		weapon[id % 3] = 1;
	}
	void printBornMessage()
	{
		Warrior::printBornMessage();
		cout << "It has a " << weaponName[id % 3] << ",and it's morale is " << fixed << setprecision(2) << morale << endl;
	}
};

class Ninja : public Warrior
{
public:
	Ninja(Headquarter *hq, int id, int strength, int atk, int cid = 1) : Warrior(hq, id, strength, atk, cid)
	{
		weapon[id % 3] = 1;
		weapon[(id + 1) % 3] = 1;
	}
	void printBornMessage()
	{
		Warrior::printBornMessage();
		cout << "It has a " << weaponName[id % 3] << " and a " << weaponName[(id + 1) % 3] << endl;
	}
};

class Iceman : public Warrior
{
public:
	Iceman(Headquarter *hq, int id, int strength, int atk, int cid = 2) : Warrior(hq, id, strength, atk, cid)
	{
		weapon[id % 3] = 1;
	}
	void printBornMessage()
	{
		Warrior::printBornMessage();
		cout << "It has a " << weaponName[id % 3] << endl;
	}
};

class Lion : public Warrior
{
private:
	int loyalty;
public:
	Lion(Headquarter *hq, int id, int strength, int atk, int cid = 3) : Warrior(hq, id, strength, atk, cid)
	{
		loyalty = hq->getTotalStrength();
	}
	void printBornMessage()
	{
		Warrior::printBornMessage();
		cout << "It's loyalty is " << loyalty << endl;
	}
};

class Wolf :public Warrior
{
public:
	Wolf(Headquarter *hq, int id, int strength, int atk, int cid = 4) : Warrior(hq, id, strength, atk, cid) {}
};

bool Headquarter::makeWarrior()
{
	if (stopMakingWarrior)
	{
		return false;
	}

	int notMadeCount = 0;
	int classID = alliance == "red" ? redOrder[ProduceIndex % 5] : blueOrder[ProduceIndex % 5];
	int strength = initialStrength[classID];
	while (strength > TotalStrength && notMadeCount < 5)
	{
		notMadeCount++;
		ProduceIndex++;
		classID = alliance == "red" ? redOrder[ProduceIndex % 5] : blueOrder[ProduceIndex % 5];
		strength = initialStrength[classID];
	}
	if (TotalStrength < strength)
	{
		stopMakingWarrior = true;
		cout << setw(3) << setfill('0') << TIME << " " << alliance << " headquarter stops making warriors" << endl;
		return false;
	}

	TotalStrength -= strength;
	int id = numOfWarrior + 1;
	numOfWarrior++;
	numOfEachClasses[classID]++;
	switch (classID)
	{
	case 0:
		warrior[id] = new Dragon(this, id, strength, 0, (double)TotalStrength / strength);
		break;
	case 1:
		warrior[id] = new Ninja(this, id, strength, 0);
		break;
	case 2:
		warrior[id] = new Iceman(this, id, strength, 0);
		break;
	case 3:
		warrior[id] = new Lion(this, id, strength, 0);
		break;
	case 4:
		warrior[id] = new Wolf(this, id, strength, 0);
	}
	warrior[id]->printBornMessage();
	ProduceIndex++;
	return true;
}

int main()
{
	int numOfTest = 0;
	cin >> numOfTest;

	for (int i = 1; i <= numOfTest; i++)
	{
		TIME = 0;
		int M = 0;
		cin >> M;
		Headquarter red("red"), blue("blue");
		red.init(M, redOrder);
		blue.init(M, blueOrder);

		for (int j = 0; j < 5; j++)
		{
			cin >> initialStrength[j];
		}

		cout << "Case:" << i << endl;
		while (true)
		{
			bool redStop = !red.makeWarrior();
			bool blueStop = !blue.makeWarrior();
			if (redStop && blueStop)
			{
				break;
			}
			TIME++;
		}
	}
	return 0;
}