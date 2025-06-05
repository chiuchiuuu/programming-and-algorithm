/***********************************************
魔兽世界终极版
完成时间：2017/12/31
邱世航
***********************************************/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
//#pragma warning(disable:4996)   // 文件重定向，visual studio 要用到

/***********************************************
全局变量：
红魔军司令部生产武士的顺序：{ 2,3,4,1,0 }
蓝魔军司令部生产武士的顺序：{ 3,0,1,2,4 }
TOTALTIME：总时间
arrow_atk：弓箭的攻击力
loyalty_loss：忠诚度的损失
initialLifeValue：司令部的初始生命元
numOfCity：城市数量
GameOver：游戏是否结束
***********************************************/
int redOrder[5] = { 2,3,4,1,0 };
int blueOrder[5] = { 3,0,1,2,4 };
int TOTALTIME = 0;
int arrow_atk;
int loyalty_loss;
int initialLifeValue, numOfCity;
bool GameOver = false;

/***********************************************
时间类
***********************************************/
class Time
{
public:
	int hour;
	int minute;
	Time(int h, int m) :hour(h), minute(m) {}
	void init(int h, int m)
	{
		hour = h;
		minute = m;
	}
	void updateTime()
	{
		minute++;
		if (minute == 60)
		{
			hour++;
			minute = 0;
		}
	}
	friend ostream& operator<<(ostream &o, const Time &t);
};

// 游戏时间
Time gameTime(0, 0);

class Warrior;

/***********************************************
城市类
void printMove()：输出移动信息
void Fight()：主要是处理40分时发生的事件
***********************************************/
class City
{
protected:
	int id;
	string flag;  // "None", "red", "blue"
	int LifeValue;
	City *next;
	City *prior;
	friend Warrior;
public:
	Warrior *redWarrior;
	Warrior *blueWarrior;
	string lastWinner;
	City() {}
	void init(int i, City *p, City *n)
	{
		id = i;
		flag = "None";
		LifeValue = 0;
		redWarrior = NULL;
		blueWarrior = NULL;
		lastWinner = "None";
		next = n;
		prior = p;
	}
	void produceLifeValue() { LifeValue += 10; }
	void printMove();
	void Fight();
	void set_flag(string flag)
	{
		this->flag = flag;
		cout << gameTime << " " << flag << " flag raised in city " << id << endl;
	}
	int get_id() { return id; }
	string get_flag() { return flag; }
	Warrior* get_red() { return redWarrior; }
	Warrior* get_blue() { return blueWarrior; }
	virtual int get_numOfInvader() { return 0; }  // 主要是给司令部使用
};

/***********************************************
司令部类
Warrior *invader：由于两名敌人进入司令部才算游戏结束，因此多一个变量invader来存放先进入司令部的敌人
void makeWarrior()：制造武士
void award()：奖励胜利的武士生命元
void reportElements()：报告当前生命元
***********************************************/
class Headquarter :public City
{
private:
	string alliance;   // "red", "blue"
	int numOfWarrior;
	int ProduceOrder[5];
	friend Warrior;
	Warrior *warrior[1000] = { NULL };
	friend ostream& operator<<(ostream &o, const Warrior *w);
public:
	Warrior *invader;
	int numOfInvader;
	Headquarter(string a) :alliance(a) {}
	void init(int lv, int po[])
	{
		invader = NULL;
		numOfWarrior = 0;
		numOfInvader = 0;
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
	void makeWarrior();
	void award(Warrior *w);
	void reportElements()
	{
		cout << gameTime << " " << LifeValue << " elements in " << alliance << " headquarter" << endl;
	}
	// 获取成员变量的函数
	string get_alliance() { return alliance; }
	int get_LifeValue() { return LifeValue; }
	int get_numOfWarrior() { return numOfWarrior; }
};

Headquarter red("red"), blue("blue");

/***********************************************
武士类
***********************************************/
class Warrior
{
protected:
	Headquarter *hq;
	City *pCity;
	int id;
	int strength;
	int attack;
	int weapon[3] = { 0 };
	const string weaponName[3] = { "sword","bomb","arrow" };
	string classes;   // 武士种类："dragon","ninja","iceman","lion","wolf"
	int classesID;    // 武士种类编号：0， 1， 2， 3， 4， 5
	friend Headquarter;
	friend ostream& operator<<(ostream &o, const Warrior *w);
public:
	bool win;
	static string warriorClasses[5];  // 所有武士种类
	static int initialStrength[5];    // 初始生命
	static int initialAttack[5];      // 初始攻击力
	Warrior() {}
	Warrior(Headquarter *hq, int id, int s, int atk, int cid) :hq(hq), id(id), strength(s), attack(atk), classesID(cid), win(false)
	{
		classes = warriorClasses[classesID];
	}
	virtual void printBornMessage()
	{
		cout << gameTime << " " << this << " born" << endl;
	}
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
	void setWeapon(int kind)
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
	void set_strength(int s) { strength = s; }
	int get_strength() { return strength; }
	int get_weapon(int i) { return weapon[i]; }
	int get_attack() { return attack; }
};

string Warrior::warriorClasses[5] = { "dragon","ninja","iceman","lion","wolf" };
int Warrior::initialStrength[5] = { 0 };
int Warrior::initialAttack[5] = { 0 };

void Warrior::Attack(Warrior *enemy)
{
	if (enemy != NULL)
	{
		cout << gameTime << " " << this << " attacked " << enemy
			<< " in city " << pCity->get_id() << " with " << strength << " elements and force " << attack << endl;
		enemy->Hurt(this, attack + weapon[0]);
		weapon[0] = weapon[0] * 0.8;
		enemy->FightBack(this);
	}
}

void Warrior::FightBack(Warrior *enemy)
{
	// ninja不反击
	if (strength != 0 && classes != "ninja")
	{
		cout << gameTime << " " << this << " fought back against " << enemy << " in city " << pCity->get_id() << endl;
		enemy->Hurt(this, attack / 2 + weapon[0]);
		weapon[0] = weapon[0] * 0.8;
	}
}

void Warrior::putArrow(Warrior *enemy)
{
	if (weapon[2] > 0 && enemy != NULL)
	{
		// 不能射司令部里的武士
		if (enemy->pCity->id == 0 || enemy->pCity->id == numOfCity + 1)
		{
			return;
		}
		enemy->Hurt(NULL, arrow_atk);  // 被射击无法反击，所以传递NULL指针
		weapon[2]--;
		if (enemy->strength == 0)
		{
			cout << gameTime << " " << this << " shot and killed " << enemy << endl;
		}
		else
		{
			cout << gameTime << " " << this << " shot" << endl;
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
			if (enemy->classes != "ninja" && attack + weapon[0] < enemy->strength && strength <= enemy->attack / 2 + enemy->weapon[0])
			{
				// 引爆炸弹
				strength = 0;
				enemy->strength = 0;
				pCity->redWarrior = NULL;
				pCity->blueWarrior = NULL;
				cout << gameTime << " " << this << " used a bomb and killed " << enemy << endl;
			}
		}
		else if (strength <= enemy->attack + enemy->weapon[0])
		{
			// 敌方先出击，会被杀死
			strength = 0;
			enemy->strength = 0;
			pCity->redWarrior = NULL;
			pCity->blueWarrior = NULL;
			cout << gameTime << " " << this << " used a bomb and killed " << enemy << endl;
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
			// enemy != NULL 说明是发生了战争而不是被射死
			enemy->win = true;
			cout << gameTime << " " << this << " was killed in city " << pCity->get_id() << endl;
		}
	}
}

void Warrior::move()
{
	// 红武士自西向东移动
	if (hq->alliance == "red")
	{
		if (pCity->id == numOfCity + 1)
		{
			pCity->redWarrior = NULL;
			blue.invader = this;
			return;
		}
		else if (pCity->id == numOfCity)
		{
			blue.numOfInvader++;
		}
		pCity->redWarrior = NULL;
		pCity = pCity->next;
		pCity->redWarrior = this;
	}
	else
	{
		// 蓝武士自东向西移动
		if (pCity->id == 0)
		{
			pCity->blueWarrior = NULL;
			red.invader = this;
			return;
		}
		else if (pCity->id == 1)
		{
			red.numOfInvader++;
		}
		pCity->blueWarrior = NULL;
		pCity = pCity->prior;
		pCity->blueWarrior = this;
	}

}

//获取城市生命元给总部
void Warrior::earn_elements()
{
	cout << gameTime << " " << this << " earned " << pCity->LifeValue << " elements for his headquarter" << endl;
	hq->LifeValue += pCity->LifeValue;
	pCity->LifeValue = 0;
}

// 报告武器
void Warrior::ReportWeapon()
{
	int num_weapon = (weapon[0] != 0) + (weapon[1] != 0) + (weapon[2] != 0);
	if (num_weapon == 0)
	{
		cout << gameTime << " " << this << " has no weapon" << endl;
	}
	else
	{
		cout << gameTime << " " << this << " has ";
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

/***********************************************
武士派生类：Dragon类
***********************************************/
class Dragon : public Warrior
{
private:
	double morale; // 士气
public:
	Dragon(Headquarter *hq, int id, int strength, int atk, double m, int cid = 0) :Warrior(hq, id, strength, atk, cid), morale(m)
	{
		classes = "dragon";
		setWeapon(id % 3);
	}
	void printBornMessage()
	{
		Warrior::printBornMessage();
		cout << "Its morale is " << fixed << setprecision(2) << morale << endl;
	}
	void yell()
	{
		// 判断是否主动攻击
		bool active_attack = (hq->get_alliance() == "red" && (pCity->get_flag() == "red" || (pCity->get_flag() == "None" && pCity->get_id() % 2 == 1)))
			|| (hq->get_alliance() == "blue" && (pCity->get_flag() == "blue" || (pCity->get_flag() == "None" && pCity->get_id() % 2 == 0)));
		if (morale > 0.8 && strength > 0 && active_attack)
		{
			cout << gameTime << " " << this << " yelled in city " << pCity->get_id() << endl;
		}
	}
	virtual void Attack(Warrior *enemy)
	{
		Warrior::Attack(enemy);
		enemy->get_strength() == 0 ? morale += 0.2 : morale -= 0.2;
		yell();
	}
};

/***********************************************
武士派生类：Ninja类
***********************************************/
class Ninja : public Warrior
{
public:
	Ninja(Headquarter *hq, int id, int strength, int atk, int cid = 1) : Warrior(hq, id, strength, atk, cid)
	{
		setWeapon(id % 3);
		setWeapon((id + 1) % 3);
	}
};

/***********************************************
武士派生类：Iceman类
***********************************************/
class Iceman : public Warrior
{
private:
	int moveStep;  // 移动步数
public:
	Iceman(Headquarter *hq, int id, int strength, int atk, int cid = 2) : Warrior(hq, id, strength, atk, cid)
	{
		setWeapon(id % 3);
		moveStep = 0;
	}
	virtual void move()
	{
		Warrior::move();
		moveStep++;
		if (moveStep % 2 == 0)
		{
			strength = strength - 9 > 0 ? strength - 9 : 1;
			attack += 20;
		}
	}
};

/***********************************************
武士类派生类：Lion类
特性：有忠诚度，会逃跑
***********************************************/
class Lion : public Warrior
{
private:
	int loyalty;
public:
	Lion(Headquarter *hq, int id, int strength, int atk, int cid = 3) : Warrior(hq, id, strength, atk, cid)
	{
		loyalty = hq->get_LifeValue();
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
			hq->get_alliance() == "red" ? pCity->redWarrior = NULL : pCity->blueWarrior = NULL;
			cout << gameTime << " " << this << " ran away" << endl;
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
	if (enemy->get_strength() != 0)
	{
		loseLoyalty();
	}
}

void Lion::FightBack(Warrior *enemy)
{
	Warrior::FightBack(enemy);
	if (enemy->get_strength() != 0)
	{
		loseLoyalty();
	}
}

void Lion::Hurt(Warrior *enemy, int atk)
{
	static int tmpStrength;
	tmpStrength = strength;
	Warrior::Hurt(enemy, atk);
	// 被射死不转移生命
	if (enemy == NULL)
	{
		return;
	}
	else if (strength == 0)
	{
		enemy->set_strength(enemy->get_strength() + tmpStrength);
	}
}

/***********************************************
武士类派生类：Wolf类
特点：可以缴获敌人的武器
***********************************************/
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
	// 获取当前生产武士的种类编号，力量值，攻击值
	int classID = ProduceOrder[numOfWarrior % 5];
	int strength = Warrior::initialStrength[classID];
	int atk = Warrior::initialAttack[classID];

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
		redWarrior->pCity = this;
	}
	else
	{
		blueWarrior = warrior[id];
		blueWarrior->pCity = this;
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

void City::printMove()
{
	// 蓝武士入侵红司令部
	if (id == 0 && blueWarrior)
	{
		cout << gameTime << " " << blueWarrior << " reached red headquarter with " << blueWarrior->get_strength() << " elements and force " << blueWarrior->get_attack() << endl;
		if (red.numOfInvader == 2)
		{
			cout << gameTime << " " << "red headquarter was taken" << endl;
			GameOver = true;
		}
	}
	// 红武士入侵蓝司令部
	else if (id == numOfCity + 1 && redWarrior)
	{
		cout << gameTime << " " << redWarrior << " reached blue headquarter with " << redWarrior->get_strength() << " elements and force " << redWarrior->get_attack() << endl;
		if (blue.numOfInvader == 2)
		{
			cout << gameTime << " " << "blue headquarter was taken" << endl;
			GameOver = true;
		}
	}
	else
	{
		if (redWarrior)
		{
			cout << gameTime << " " << redWarrior << " marched to city " << id << " with " << redWarrior->get_strength() << " elements and force " << redWarrior->get_attack() << endl;
		}
		if (blueWarrior)
		{
			cout << gameTime << " " << blueWarrior << " marched to city " << id << " with " << blueWarrior->get_strength() << " elements and force " << blueWarrior->get_attack() << endl;
		}
	}
}

void City::Fight()
{
	// 只有一个武士且被射死，没有发生战斗
	if (!redWarrior && blueWarrior && blueWarrior->get_strength() == 0)
	{
		blueWarrior = NULL;
	}
	if (redWarrior && !blueWarrior && redWarrior->get_strength() == 0)
	{
		redWarrior = NULL;
	}
	// 红蓝武士都在，视为发生了一场战斗
	if (redWarrior && blueWarrior)
	{
		// 都被射死
		if (redWarrior->get_strength() == 0 && blueWarrior->get_strength() == 0)
		{
			blueWarrior = NULL;
			redWarrior = NULL;
			return;
		}
		// 一方被射死
		else if (redWarrior->get_strength() == 0 && blueWarrior->get_strength() > 0)
		{
			blueWarrior->win = true;
			blueWarrior->yell();
		}
		else if (redWarrior->get_strength() > 0 && blueWarrior->get_strength() == 0)
		{
			redWarrior->win = true;
			redWarrior->yell();
		}
		// 判断主动攻击方，发生战斗
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
			redWarrior->disarm(blueWarrior);  // Wolf缴械
			if (lastWinner == "red" && flag != "red")  // 连胜两次
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

/***********************************************
输出运算符重载
输出武士信息和时间
***********************************************/
ostream& operator<<(ostream &o, const Warrior *w)
{
	o << w->hq->alliance << " " << w->classes << " " << w->id;
	return o;
}

ostream& operator<<(ostream &o, const Time &t)
{
	o << setw(3) << setfill('0') << t.hour << ":" << setw(2) << t.minute;
	return o;
}

/***********************************************
主函数！！！
***********************************************/
int main()
{
	// 文件重定向
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int numOfTest = 0;
	cin >> numOfTest;

	for (int i = 1; i <= numOfTest; i++)
	{
		// 重置全局变量
		gameTime.init(0, 0);
		GameOver = false;

		// 输入数据
		cin >> initialLifeValue >> numOfCity >> arrow_atk >> loyalty_loss >> TOTALTIME;
		for (int j = 0; j < 5; j++)
		{
			cin >> Warrior::initialStrength[j];
		}
		for (int j = 0; j < 5; j++)
		{
			cin >> Warrior::initialAttack[j];
		}

		// 总部和城市初始化
		City* city[22];   // 为了让城市数组包含总部，声明为指针
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
		// 一定要先调用City的init在调用Headquarter的init
		red.init(initialLifeValue, redOrder);
		blue.init(initialLifeValue, blueOrder);

		// 测试开始
		cout << "Case " << i << ":" << endl;
		while (true)
		{
			if (gameTime.minute == 0)
			{
				red.makeWarrior();
				blue.makeWarrior();
			}
			if (gameTime.minute == 5)  // 狮子逃跑
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
			if (gameTime.minute == 10)  // 武士移动
			{
				// 为了防止移动造成下一个城市信息损失，和移动方向相反调用move()
				for (int j = numOfCity + 1; j >= 0; j--)
				{
					if (city[j]->get_red())
					{
						city[j]->get_red()->move();
					}
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					if (city[j]->get_blue())
					{
						city[j]->get_blue()->move();
					}
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					city[j]->printMove();
				}
				if (GameOver)
				{
					break;
				}
			}
			if (gameTime.minute == 20)  // 城市产生生命元
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					city[j]->produceLifeValue();
				}
			}
			if (gameTime.minute == 30)  // 只有一个武士时直接取走生命元
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
			if (gameTime.minute == 35)  // 放箭
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
			if (gameTime.minute == 38)  // 放炸弹
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
			if (gameTime.minute == 40)  // 战斗
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					city[j]->Fight();
				}
				for (int j = 1; j <= numOfCity; j++)  // 优先奖励距离近的
				{
					red.award(city[j]->redWarrior);
					blue.award(city[numOfCity - j + 1]->blueWarrior);
				}
			}
			if (gameTime.minute == 50)  // 司令部报告生命值
			{
				red.reportElements();
				blue.reportElements();
			}
			if (gameTime.minute == 55)  // 武士报告武器
			{
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					if (city[j]->get_red())
					{
						city[j]->get_red()->ReportWeapon();
					}
				}
				if (blue.invader)   // 入侵到总部的武士也要报告
				{
					blue.invader->ReportWeapon();
				}
				if (red.invader)
				{
					red.invader->ReportWeapon();
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					if (city[j]->get_blue())
					{
						city[j]->get_blue()->ReportWeapon();
					}
				}
			}

			gameTime.updateTime();
			if (60 * gameTime.hour + gameTime.minute > TOTALTIME)
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