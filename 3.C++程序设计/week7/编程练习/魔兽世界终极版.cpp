#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


string warriorClasses[5] = { "dragon","ninja","iceman","lion","wolf" };
int initialStrength[5] = { 0 };
int initialAttack[5] = { 0 };
int redOrder[5] = { 2,3,4,1,0 };
int blueOrder[5] = { 3,0,1,2,4 };
int HOUR = 0;
int MINUTE = 0;
int TOTALTIME = 0;
int arrow_atk;
int loyalty_loss;
int initialLifeValue, numOfCity;
int redWin = false;
int blueWin = false;

void printTime()
{
	cout << setw(3) << setfill('0') << HOUR << ":" << setw(2) << MINUTE << " ";
}
void updateTime()
{
	MINUTE++;
	if (MINUTE == 60)
	{
		HOUR++;
		MINUTE = 0;
	}
}

class Warrior;

class City
{
protected:
	int id;
	string flag;  // 0：无旗帜，1：红旗，2：蓝旗
	int LifeValue;
	City *next;
	City *prior;
	friend Warrior;
public:
	Warrior *redWarrior;
	Warrior *blueWarrior;
	string lastWinner;
	City() {}
	void init(int id, City *p, City *n)
	{
		this->id = id;
		string flag = "None";
		LifeValue = 0;
		redWarrior = NULL;
		blueWarrior = NULL;
		lastWinner = "None";
		next = n;
		prior = p;
	}
	~City()
	{
		if (redWarrior)
		{
			delete redWarrior;
		}
		if (blueWarrior)
		{
			delete blueWarrior;
		}
	}
	int get_id() { return id; }
	string get_flag() { return flag; }
	void set_flag(string flag) { this->flag = flag; }
	void produceLifeValue() { LifeValue += 10; }
	Warrior* get_red() { return redWarrior; }
	Warrior* get_blue() { return blueWarrior; }
	void printMove();
};



class Headquarter :public City
{
private:
	string alliance;
	int numOfWarrior;
	int ProduceOrder[5];
	friend Warrior;
	Warrior *warrior[1000] = { NULL };
	bool stopMakingWarrior;
	friend ostream& operator<<(ostream &o, const Warrior *w);
public:
	int numOfInvasion;
	Headquarter(string a, int id) :alliance(a) { this->id = id; }
	void init(int lv, int po[])
	{
		redWarrior = NULL;
		blueWarrior = NULL;
		numOfWarrior = 0;
		numOfInvasion = 0;
		LifeValue = lv;
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
	string getAlliance() { return alliance; }
	int getLifeValue() { return LifeValue; }
	Warrior* get_warrior(int i) { return warrior[i]; }
	int get_numOfWarrior() { return numOfWarrior; }
	void makeWarrior();
	void reportElements()
	{
		printTime();
		cout << LifeValue << " elements in " << alliance << " headquarter";
	}
};

class Warrior
{
protected:
	Headquarter *hq;
	City *pCity;
	int id;
	int strength;
	int attack;
	int weapon[3]; // sword, bomb, arrow
	string weaponName[3] = { "sword","bomb","arrow" };
	string classes;
	int classesID;
	friend ostream& operator<<(ostream &o, const Warrior *w);
public:
	Warrior() {}
	Warrior(Headquarter *hq, int id, int s, int atk, int cid) :hq(hq), id(id), strength(s), attack(atk), classesID(cid)
	{
		classes = warriorClasses[classesID];
	}
	virtual void printBornMessage()
	{
		printTime();
		cout << this << " born" << endl;
	}
	int getStrength()
	{
		return strength;
	}
	void set_strength(int s) { strength = s; }
	string getClasses()
	{
		return classes;
	}
	int get_weapon(int i) { return weapon[i]; }
	virtual void Attack(Warrior *enemy);
	virtual void FightBack(Warrior *enemy);
	virtual void putArrow(Warrior *enemy);
	virtual void bomb(Warrior *enemy);
	virtual void Hurt(Warrior *enemy, int atk);
	virtual void earn_elements();
	virtual void ReportWeapon();
	virtual void move();
	virtual void escape() {}
	virtual void yell() {}
	virtual void disarm() {}
	void getWeapon(int kind)
	{
		if (kind == 0)
		{
			weapon[0] = attack * 0.2;
		}
		else if (kind == 1)
		{
			weapon[1] = 3;
		}
		else
		{
			weapon[2] = 1;
		}
	}
	int get_attack() { return attack; }
};

void Warrior::Attack(Warrior *enemy)
{
	if (enemy != NULL)
	{
		enemy->Hurt(this, attack + weapon[0]);
		weapon[0] = weapon[0] * 0.8;
		printTime();
		cout << this << "attacked " << enemy
			<< " in city " << pCity->get_id() << " with " << strength << " elements and force " << attack << endl;
		enemy->FightBack(this);
	}
}

void Warrior::FightBack(Warrior *enemy)
{
	if (strength != 0 && enemy->getClasses() != "ninja")
	{
		enemy->Hurt(this, attack / 2 + weapon[0]);
		weapon[0] = weapon[0] * 0.8;
		printTime();
		cout << this << " fought back against " << enemy << " in city " << pCity->get_id() << endl;
	}
}

void Warrior::putArrow(Warrior *enemy)
{
	if (weapon[2] > 0 && enemy != NULL)
	{
		if (enemy->pCity->id == 0 || enemy->pCity->id == numOfCity + 1)
		{
			return;
		}
		enemy->Hurt(NULL, arrow_atk);
		weapon[2]--;
		if (enemy->strength == 0)
		{
			cout << setw(3) << setfill('0') << HOUR << ":" << setw(2) << MINUTE << " "
				<< hq->alliance << " " << classes << " " << id << " shot and killed " << enemy->hq->alliance << " " << enemy->classes << " " << enemy->id << endl;
		}
		else
		{
			cout << setw(3) << setfill('0') << HOUR << ":" << setw(2) << MINUTE << " "
				<< hq->alliance << " " << classes << " " << id << " shot" << endl;
		}
	}
}

void Warrior::bomb(Warrior *enemy)
{
	if (enemy == NULL)
	{
		return;
	}
	if (strength - (enemy->attack / 2 + enemy->weapon[0]) <= 0 || strength - (enemy->attack + enemy->weapon[0]) <= 0)
	{
		strength = 0;
		enemy->strength = 0;
		pCity->redWarrior = NULL;
		pCity->blueWarrior = NULL;
		printTime();
		cout << this << " used a bomb and killed " << enemy << endl;
	}
}

void Warrior::Hurt(Warrior *enemy, int atk)
{
	strength -= atk;
	if (strength <= 0)
	{
		// 被杀死
		strength = 0;
		if (enemy != NULL)
		{
			printTime();
			cout << hq->alliance << " " << classes << " " << id << " was killed in city " << pCity->get_id() << endl;

			// 插旗
			if (pCity->lastWinner == enemy->hq->alliance)
			{
				pCity->set_flag(enemy->hq->alliance);
				printTime();
				cout << enemy->hq->alliance << " flag raised in city " << pCity->id << endl;
			}
			pCity->lastWinner = enemy->hq->alliance;

			// 获取生命值
			enemy->earn_elements();

			// 删除武士所在的城市的指针并设为NULL
			if (hq->alliance == "red")
			{
				pCity->redWarrior = NULL;
			}
			else
			{
				pCity->blueWarrior = NULL;
			}
		}
	}
}

void Warrior::move()
{
	if (hq->alliance == "red")
	{
		if (pCity->id == numOfCity + 1)
		{
			return;
		}
		else if (pCity->id == numOfCity)
		{
			hq->numOfInvasion++;
			if (hq->numOfInvasion == 2)
			{
				redWin = true;
			}
		}
		pCity->redWarrior = NULL;
		pCity = pCity->next;
		pCity->redWarrior = this;
	}
	else
	{
		if (pCity->id == 0)
		{
			return;
		}
		else if (pCity->id == 1)
		{
			hq->numOfInvasion++;
			if (hq->numOfInvasion == 2)
			{
				blueWin = true;
			}
		}
		pCity->blueWarrior = NULL;
		pCity = pCity->prior;
		pCity->blueWarrior = this;
	}

}

void Warrior::earn_elements()
{
	printTime();
	cout << hq->alliance << " " << classes << " " << id << " earned " << pCity->LifeValue << " elements for his headquarter" << endl;
	hq->LifeValue += pCity->LifeValue;
	pCity->LifeValue = 0;
}

void Warrior::ReportWeapon()
{
	int num_weapon = (weapon[0] != 0) + (weapon[1] != 0) + (weapon[2] != 0);
	if (num_weapon == 0)
	{
		printTime();
		cout << this << " has no weapon" << endl;
	}
	else
	{
		printTime();
		cout << this << " has ";
		if (weapon[2])
		{
			cout << "arrow(" << weapon[2] << ")";
			num_weapon--;
			if (num_weapon)
			{
				cout << ",";
			}
		}
		if (weapon[1])
		{
			cout << "bomb";
			num_weapon--;
			if (num_weapon)
			{
				cout << ",";
			}
		}
		if (weapon[0])
		{
			cout << "sword(" << weapon[0] << ")";
		}
		cout << endl;
	}
}

class Dragon : public Warrior
{
private:
	double morale; // 士气
public:
	Dragon(Headquarter *hq, int id, int strength, int atk, double m, int cid = 0) :Warrior(hq, id, strength, atk, cid), morale(m)
	{
		classes = "dragon";
		getWeapon(id % 3);
	}
	void printBornMessage()
	{
		Warrior::printBornMessage();
		cout << "It's morale is " << fixed << setprecision(2) << morale << endl;
	}
	void yell()
	{
		if (morale > 0.8)
		{
			cout << this << " yelled in city " << pCity->get_id() << endl;
		}
	}
	virtual void Attack(Warrior *enemy);
};

void Dragon::Attack(Warrior *enemy)
{
	Warrior::Attack(enemy);
	enemy->getStrength() == 0 ? morale += 2 : morale -= 2;
	yell();
}

class Ninja : public Warrior
{
public:
	Ninja(Headquarter *hq, int id, int strength, int atk, int cid = 1) : Warrior(hq, id, strength, atk, cid)
	{
		getWeapon(id % 3);
		getWeapon((id + 1) % 3);
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
		getWeapon(id % 3);
	}
	void printBornMessage()
	{
		Warrior::printBornMessage();
		cout << "It has a " << weaponName[id % 3] << endl;
	}
	virtual void move();
};

void Iceman::move()
{
	static int moveStep = 0;
	Warrior::move();
	moveStep++;
	if (moveStep % 2 == 0)
	{
		strength = strength - 9 > 0 ? strength - 9 : 1;
	}
}

class Lion : public Warrior
{
private:
	int loyalty;
public:
	Lion(Headquarter *hq, int id, int strength, int atk, int cid = 3) : Warrior(hq, id, strength, atk, cid)
	{
		loyalty = hq->getLifeValue();
	}
	void printBornMessage()
	{
		Warrior::printBornMessage();
		cout << "Its loyalty is " << loyalty << endl;
	}
	void escape()
	{
		if (loyalty <= 0)
		{
			hq->getAlliance() == "red" ? pCity->redWarrior = NULL : pCity->blueWarrior = NULL;
			cout << this << " ran away" << endl;
		}
	}
	virtual void Attack(Warrior *enemy);
	virtual void Hurt(Warrior *enemy, int atk);
};

void Lion::Attack(Warrior *enemy)
{
	Warrior::Attack(enemy);
	if (enemy->getStrength() != 0)
	{
		loyalty -= loyalty_loss;
	}
}

void Lion::Hurt(Warrior *enemy, int atk)
{
	int tmp = strength;
	Warrior::Hurt(enemy, atk);
	enemy->set_strength(enemy->getStrength() + tmp);
}

class Wolf :public Warrior
{
public:
	Wolf(Headquarter *hq, int id, int strength, int atk, int cid = 4) : Warrior(hq, id, strength, atk, cid) {}
	void disarm(Warrior *w)
	{
		for (int i = 0; i < 3; i++)
		{
			if (!weapon[i])
			{
				weapon[i] = w->get_weapon(i);
			}
		}
	}
	virtual void Attack(Warrior *enemy);
};

void Wolf::Attack(Warrior *enemy)
{
	Warrior::Attack(enemy);
	if (enemy->getStrength() == 0)
	{
		disarm(enemy);
	}
}

void Headquarter::makeWarrior()
{

	int classID = ProduceOrder[numOfWarrior % 5];
	int strength = initialStrength[classID];
	int atk = initialAttack[classID];

	if (LifeValue < strength)
	{
		return;
	}

	LifeValue -= strength;
	int id = numOfWarrior + 1;
	numOfWarrior++;
	switch (classID)
	{
	case 0:
		warrior[id] = new Dragon(this, id, strength, atk, (double)LifeValue / strength);
		break;
	case 1:
		warrior[id] = new Ninja(this, id, strength, atk);
		break;
	case 2:
		warrior[id] = new Iceman(this, id, strength, atk);
		break;
	case 3:
		warrior[id] = new Lion(this, id, strength, atk);
		break;
	case 4:
		warrior[id] = new Wolf(this, id, strength, atk);
	}
	warrior[id]->printBornMessage();
	alliance == "red" ? redWarrior = warrior[id] : blueWarrior = warrior[id];
}

void City::printMove()
{
	if (id == 0 && blueWarrior)
	{
		printTime();
		cout << redWarrior << " reached blue headquarter with " << redWarrior->getStrength() << " elements and force " << redWarrior->get_attack() << endl;
	}
	else if (id == numOfCity + 1 && redWarrior)
	{
		printTime();
		cout << blueWarrior << " reached red headquarter with " << blueWarrior->getStrength() << " elements and force " << blueWarrior->get_attack() << endl;
	}
	else
	{
		if (redWarrior)
		{
			printTime();
			cout << redWarrior << " marched to city " << id << " with " << redWarrior->getStrength() << " elements and force " << redWarrior->get_attack() << endl;
		}
		if (blueWarrior)
		{
			printTime();
			cout << blueWarrior << " marched to city " << id << " with " << blueWarrior->getStrength() << " elements and force " << blueWarrior->get_attack() << endl;
		}
	}
}

ostream& operator<<(ostream &o, const Warrior *w)
{
	o << w->hq->alliance << " " << w->classes << " " << w->id;
	return o;
}

int main()
{
	int numOfTest = 0;
	cin >> numOfTest;

	for (int i = 1; i <= numOfTest; i++)
	{
		HOUR = 0;
		MINUTE = 0;

		// 输入数据

		cin >> initialLifeValue >> numOfCity >> arrow_atk >> loyalty_loss >> TOTALTIME;
		for (int j = 0; j < 5; j++)
		{
			cin >> initialStrength[j];
		}
		for (int j = 0; j < 5; j++)
		{
			cin >> initialAttack[j];
		}

		// 总部初始化
		Headquarter red("red", 0), blue("blue", numOfCity + 1);
		red.init(initialLifeValue, redOrder);
		blue.init(initialLifeValue, blueOrder);

		// 城市初始化
		City city[22];
		city[0] = red;
		city[numOfCity + 1] = blue;
		for (int j = 1; j <= numOfCity; j++)
		{
			city[j].init(j, &city[j - 1], &city[j + 1]);
		}

		// 测试开始
		cout << "Case:" << i << endl;
		while (true)
		{
			if (MINUTE == 0)
			{
				red.makeWarrior();
				blue.makeWarrior();
			}
			if (MINUTE == 5)
			{
				for (int j = 1; j < numOfCity; j++)
				{

					if (city[j].get_red())
					{
						city[j].get_red()->escape();
					}
					if (city[j].get_blue())
					{
						city[j].get_blue()->escape();
					}
				}
			}
			if (MINUTE == 10)
			{

				for (int j = numOfCity + 1; j >= 0; j--)
				{
					City c = city[j];
					if (city[j].get_red())
					{
						city[j].get_red()->move();
					}
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					City c = city[j];
					c.get_blue();
					if (c.get_blue())
					{
						c.get_blue()->move();
					}
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					city[j].printMove();
				}
				if (redWin || blueWin)
				{
					break;
				}
			}
			if (MINUTE == 20)
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					city[j].produceLifeValue();
				}
			}
			if (MINUTE == 30)
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					if (city[j].get_red() && !city[j].get_blue())
					{
						city[j].get_red()->earn_elements();
					}
					else if (!city[j].get_red() && city[j].get_blue())
					{
						city[j].get_blue()->earn_elements();
					}
				}
			}
			if (MINUTE == 35)
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					Warrior* redWarrior = city[j].get_red();
					Warrior* blueWarrior = city[j].get_blue();
					if (redWarrior)
					{
						redWarrior->putArrow(city[j + 1].get_blue());
					}
					if (blueWarrior)
					{
						blueWarrior->putArrow(city[j - 1].get_red());
					}
				}
			}
			if (MINUTE == 38)
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					if (city[j].get_red())
					{
						city[j].get_red()->bomb(city[j].get_blue());
					}
					if (city[j].get_blue())
					{
						city[j].get_blue()->bomb(city[j].get_red());
					}
				}
			}
			if (MINUTE == 40)
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					if (city[j].get_red() && city[j].get_blue())
					{
						if (city[j].get_flag() == "red" || (city[j].get_flag() == "None" && j % 2 == 1))
						{
							city[j].get_red()->Attack(city[j].get_blue());
						}
						else
						{
							city[j].get_blue()->Attack(city[j].get_red());
						}
						city[j].get_red()->yell();
						city[j].get_blue()->yell();
					}
				}
			}
			if (MINUTE == 50)
			{
				red.reportElements();
				blue.reportElements();
			}
			if (MINUTE == 55)
			{
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					if (city[j].get_red())
					{
						city[j].get_red()->ReportWeapon();
					}
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					if (city[j].get_blue())
					{
						city[j].get_blue()->ReportWeapon();
					}
				}
			}
			updateTime();
			if (60 * HOUR + MINUTE > TOTALTIME)
			{
				return 0;
			}
		}
	}
	return 0;
}
