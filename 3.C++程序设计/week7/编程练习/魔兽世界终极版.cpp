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
	Warrior *invader;
	string lastWinner;
	City() {}
	void init(int i, City *p, City *n)
	{
		id = i;
		flag = "None";
		LifeValue = 0;
		redWarrior = NULL;
		blueWarrior = NULL;
		invader = NULL;
		lastWinner = "None";
		next = n;
		prior = p;
	}
	int get_id() { return id; }
	string get_flag() { return flag; }
	void set_flag(string flag)
	{
		this->flag = flag;
		printTime();
		cout << flag << " flag raised in city " << id << endl;
	}
	void produceLifeValue() { LifeValue += 10; }
	Warrior* get_red() { return redWarrior; }
	Warrior* get_blue() { return blueWarrior; }
	void printMove();
	void Fight();
	virtual int get_numOfEnemy() { return 0; }
};



class Headquarter :public City
{
private:
	string alliance;
	int numOfWarrior;
	int ProduceOrder[5];
	friend Warrior;
	Warrior *warrior[1000] = { NULL };
	Warrior* enemy;
	friend ostream& operator<<(ostream &o, const Warrior *w);
public:
	int numOfEnemy;
	Headquarter(string a) :alliance(a) {}
	void init(int lv, int po[])
	{
		enemy = NULL;
		numOfWarrior = 0;
		numOfEnemy = 0;
		LifeValue = lv;
		for (int i = 0; i < 5; i++)
		{
			ProduceOrder[i] = po[i];
		}
	}
	~Headquarter()
	{
		for (int i = 0; i < numOfWarrior; i++)
		{
			if (warrior[i])
			{
				delete warrior[i];
			}
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
		cout << LifeValue << " elements in " << alliance << " headquarter" << endl;
	}
	void award(Warrior *w);
	int get_numOfEnemy() { return numOfEnemy; }
};

Headquarter red("red"), blue("blue");

class Warrior
{
protected:
	Headquarter *hq;
	City *pCity;
	int id;
	int strength;
	int attack;
	int weapon[3] = { 0 }; // sword, bomb, arrow
	string weaponName[3] = { "sword","bomb","arrow" };
	string classes;
	int classesID;

	friend ostream& operator<<(ostream &o, const Warrior *w);
	friend Headquarter;
public:
	bool win;
	Warrior() {}
	Warrior(Headquarter *hq, int id, int s, int atk, int cid) :hq(hq), id(id), strength(s), attack(atk), classesID(cid), win(false)
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
	virtual void disarm(Warrior *enemy) {}
	void getWeapon(int kind)
	{
		if (kind == 0)
		{
			weapon[0] = attack * 0.2;
		}
		else if (kind == 1)
		{
			weapon[1] = 1;
		}
		else
		{
			weapon[2] = 3;
		}
	}
	int get_attack() { return attack; }
	void set_city(City *c) { pCity = c; }
};

void Warrior::Attack(Warrior *enemy)
{
	if (enemy != NULL)
	{
		printTime();
		cout << this << " attacked " << enemy
			<< " in city " << pCity->get_id() << " with " << strength << " elements and force " << attack << endl;
		enemy->Hurt(this, attack + weapon[0]);
		weapon[0] = weapon[0] * 0.8;
		enemy->FightBack(this);
	}
}

void Warrior::FightBack(Warrior *enemy)
{
	if (strength != 0 && classes != "ninja")
	{
		printTime();
		cout << this << " fought back against " << enemy << " in city " << pCity->get_id() << endl;
		enemy->Hurt(this, attack / 2 + weapon[0]);
		weapon[0] = weapon[0] * 0.8;
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
			printTime();
			cout << this << " shot and killed " << enemy << endl;
		}
		else
		{
			printTime();
			cout << this << " shot" << endl;
		}
	}
}

void Warrior::bomb(Warrior *enemy)
{
	if (enemy && weapon[1])
	{
		if (strength == 0 || enemy->strength == 0)
		{
			return;
		}
		bool redFirst = pCity->get_flag() == "red" || (pCity->get_flag() == "None" && pCity->id % 2 == 1);
		if (redFirst && hq->alliance == "red" || !redFirst && hq->alliance == "blue")
		{
			// 我方先出击，被反杀
			if (enemy->getClasses() != "ninja" && attack + weapon[0] < enemy->strength && strength <= enemy->attack / 2 + enemy->weapon[0])
			{
				// 引爆炸弹
				strength = 0;
				enemy->strength = 0;
				pCity->redWarrior = NULL;
				pCity->blueWarrior = NULL;
				printTime();
				cout << this << " used a bomb and killed " << enemy << endl;
			}
		}
		else if (strength <= enemy->attack + enemy->weapon[0])
		{
			// 引爆炸弹
			strength = 0;
			enemy->strength = 0;
			pCity->redWarrior = NULL;
			pCity->blueWarrior = NULL;
			printTime();
			cout << this << " used a bomb and killed " << enemy << endl;
		}
	}
}

void Warrior::Hurt(Warrior *enemy, int atk)
{
	strength -= atk;
	if (strength <= 0)
	{
		strength = 0;
		if (enemy != NULL)
		{
			enemy->win = true;
			printTime();
			cout << hq->alliance << " " << classes << " " << id << " was killed in city " << pCity->get_id() << endl;
		}
	}
}

void Warrior::move()
{
	if (hq->alliance == "red")
	{
		if (pCity->id == numOfCity + 1)
		{
			pCity->redWarrior = NULL;
			pCity->invader = this;
			return;
		}
		else if (pCity->id == numOfCity)
		{
			blue.numOfEnemy++;
		}
		pCity->redWarrior = NULL;
		pCity = pCity->next;
		pCity->redWarrior = this;
	}
	else
	{
		if (pCity->id == 0)
		{
			pCity->blueWarrior = NULL;
			pCity->invader = this;
			return;
		}
		else if (pCity->id == 1)
		{
			red.numOfEnemy++;
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
		cout << "Its morale is " << fixed << setprecision(2) << morale << endl;
	}
	void yell()
	{
		bool active_attack = (hq->getAlliance() == "red" && (pCity->get_flag() == "red" || (pCity->get_flag() == "None" && pCity->get_id() % 2 == 1)))
			|| (hq->getAlliance() == "blue" && (pCity->get_flag() == "blue" || (pCity->get_flag() == "None" && pCity->get_id() % 2 == 0)));
		if (morale > 0.8 && strength > 0 && active_attack)
		{
			printTime();
			cout << this << " yelled in city " << pCity->get_id() << endl;
		}
	}
	virtual void Attack(Warrior *enemy);
};

void Dragon::Attack(Warrior *enemy)
{
	Warrior::Attack(enemy);
	enemy->getStrength() == 0 ? morale += 0.2 : morale -= 0.2;
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
};

class Iceman : public Warrior
{
private:
	int moveStep;
public:
	Iceman(Headquarter *hq, int id, int strength, int atk, int cid = 2) : Warrior(hq, id, strength, atk, cid)
	{
		getWeapon(id % 3);
		moveStep = 0;
	}
	virtual void move();
};

void Iceman::move()
{
	Warrior::move();
	moveStep++;
	if (moveStep % 2 == 0)
	{
		strength = strength - 9 > 0 ? strength - 9 : 1;
		attack += 20;
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
			printTime();
			cout << this << " ran away" << endl;
		}
	}
	virtual void Attack(Warrior *enemy);
	virtual void FightBack(Warrior *enemy);
	virtual void Hurt(Warrior *enemy, int atk);
	void loseLoyalty()
	{
		loyalty -= loyalty_loss;
		if (loyalty < 0) { loyalty = 0; }
	}
};

void Lion::Attack(Warrior *enemy)
{
	Warrior::Attack(enemy);
	if (enemy->getStrength() != 0)
	{
		loyalty -= loyalty_loss;
		loseLoyalty();
	}
}

void Lion::FightBack(Warrior *enemy)
{
	Warrior::FightBack(enemy);
	loseLoyalty();
}

void Lion::Hurt(Warrior *enemy, int atk)
{
	static int tmpStrength;
	tmpStrength = strength;
	Warrior::Hurt(enemy, atk);
	if (enemy == NULL)
	{
		return;
	}
	else if (strength == 0)
	{
		enemy->set_strength(enemy->getStrength() + tmpStrength);
	}
}

class Wolf :public Warrior
{
public:
	Wolf(Headquarter *hq, int id, int strength, int atk, int cid = 4) : Warrior(hq, id, strength, atk, cid) {}
	virtual void disarm(Warrior *enemy)
	{
		for (int i = 0; i < 3; i++)
		{
			if (!weapon[i])
			{
				weapon[i] = enemy->get_weapon(i);
			}
		}
	}
};

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
	if (alliance == "red")
	{
		redWarrior = warrior[id];
		redWarrior->set_city(this);
	}
	else
	{
		blueWarrior = warrior[id];
		blueWarrior->set_city(this);
	}
}

void City::printMove()
{
	if (id == 0 && blueWarrior)
	{
		printTime();
		cout << blueWarrior << " reached red headquarter with " << blueWarrior->getStrength() << " elements and force " << blueWarrior->get_attack() << endl;
		if (get_numOfEnemy() == 2)
		{
			printTime();
			cout << "red headquarter was taken" << endl;
			blueWin = true;
		}
	}
	else if (id == numOfCity + 1 && redWarrior)
	{
		printTime();
		cout << redWarrior << " reached blue headquarter with " << redWarrior->getStrength() << " elements and force " << redWarrior->get_attack() << endl;
		if (get_numOfEnemy() == 2)
		{
			printTime();
			cout << "blue headquarter was taken" << endl;
			redWin = true;
		}
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

void Headquarter::award(Warrior *w)
{
	if (w && (w->hq->alliance == alliance) && w->win)
	{
		w->win = false;
		if (LifeValue - 8 >= 0)
		{
			w->strength += 8;
			LifeValue -= 8;
		}
	}
}

void City::Fight()
{
	// 蓝武士被射死
	if (!redWarrior && blueWarrior && blueWarrior->getStrength() == 0)
	{
		blueWarrior = NULL;
	}
	// 红武士被射死
	if (redWarrior && !blueWarrior && redWarrior->getStrength() == 0)
	{
		redWarrior = NULL;
	}
	if (redWarrior && blueWarrior)
	{
		if (redWarrior->getStrength() == 0 && blueWarrior->getStrength() == 0)
		{
			blueWarrior = NULL;
			redWarrior = NULL;
			return;
		}
		else if (redWarrior->getStrength() == 0 && blueWarrior->getStrength() > 0)
		{
			blueWarrior->win = true;
			blueWarrior->yell();
		}
		else if (redWarrior->getStrength() > 0 && blueWarrior->getStrength() == 0)
		{
			redWarrior->win = true;
			redWarrior->yell();
		}
		else
		{
			if (flag == "red" || (flag == "None" && id % 2 == 1))
			{
				redWarrior->Attack(blueWarrior);
			}
			else
			{
				blueWarrior->Attack(redWarrior);
			}
		}
		if (redWarrior->win)
		{
			redWarrior->earn_elements();
			redWarrior->disarm(blueWarrior);
			if (lastWinner == "red" && flag != "red")
			{
				set_flag("red");
			}
			blueWarrior = NULL;
			lastWinner = "red";
		}
		else if (blueWarrior->win)
		{
			blueWarrior->earn_elements();
			blueWarrior->disarm(redWarrior);
			if (lastWinner == "blue" && flag != "blue")
			{
				set_flag("blue");
			}
			redWarrior = NULL;
			lastWinner = "blue";
		}
		else
		{
			lastWinner = "None";
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
		blueWin = false;
		redWin = false;

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

		// 总部和城市初始化

		City* city[22];
		for (int j = 1; j <= numOfCity; j++)
		{
			city[j] = new City;
		}
		city[0] = &red;
		city[numOfCity + 1] = &blue;
		for (int j = 1; j <= numOfCity; j++)
		{
			city[j]->init(j, city[j - 1], city[j + 1]);
		}
		city[0]->init(0, NULL, city[1]);
		city[numOfCity + 1]->init(numOfCity + 1, city[numOfCity], NULL);
		red.init(initialLifeValue, redOrder);
		blue.init(initialLifeValue, blueOrder);


		// 测试开始
		cout << "Case " << i << ":" << endl;
		while (true)
		{
			if (MINUTE == 0)
			{
				red.makeWarrior();
				blue.makeWarrior();
			}
			if (MINUTE == 5)
			{
				for (int j = 0; j <= numOfCity + 1; j++)
				{

					if (city[j]->get_red())
					{
						city[j]->get_red()->escape();
					}
					if (city[j]->get_blue())
					{
						city[j]->get_blue()->escape();
					}
				}
			}
			if (MINUTE == 10)
			{

				for (int j = numOfCity + 1; j >= 0; j--)
				{
					if (city[j]->get_red() != NULL)
					{
						city[j]->get_red()->move();
					}
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					if (city[j]->get_blue() != NULL)
					{
						city[j]->get_blue()->move();
					}
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					city[j]->printMove();
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
					city[j]->produceLifeValue();
				}
			}
			if (MINUTE == 30)
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					if (city[j]->get_red() && !city[j]->get_blue())
					{
						city[j]->get_red()->earn_elements();
					}
					else if (!city[j]->get_red() && city[j]->get_blue())
					{
						city[j]->get_blue()->earn_elements();
					}
				}
			}
			if (MINUTE == 35)
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					Warrior* redWarrior = city[j]->get_red();
					Warrior* blueWarrior = city[j]->get_blue();
					if (redWarrior)
					{
						redWarrior->putArrow(city[j + 1]->get_blue());
					}
					if (blueWarrior)
					{
						blueWarrior->putArrow(city[j - 1]->get_red());
					}
				}
			}
			if (MINUTE == 38)
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					if (city[j]->get_red())
					{
						city[j]->get_red()->bomb(city[j]->get_blue());
					}
					if (city[j]->get_blue())
					{
						city[j]->get_blue()->bomb(city[j]->get_red());
					}
				}
			}
			if (MINUTE == 40)
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					city[j]->Fight();
				}
				for (int j = 1; j <= numOfCity; j++)
				{
					red.award(city[j]->redWarrior);
					blue.award(city[numOfCity - j + 1]->blueWarrior);
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
					if (city[j]->get_red())
					{
						city[j]->get_red()->ReportWeapon();
					}
				}
				if (city[numOfCity + 1]->invader)
				{
					city[numOfCity + 1]->invader->ReportWeapon();
				}
				if (city[0]->invader)
				{
					city[0]->invader->ReportWeapon();
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					if (city[j]->get_blue())
					{
						city[j]->get_blue()->ReportWeapon();
					}
				}
			}
			updateTime();
			if (60 * HOUR + MINUTE > TOTALTIME)
			{
				break;
			}
		}

		for (int j = 1; j <= numOfCity; j++)
		{
			if (city[j])
			{
				delete city[j];
			}
		}
	}
	return 0;
}


