#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Complex
{
private:
	double r, i;
public:
	void Print()
	{
		cout << r << "+" << i << "i" << endl;
	}
	Complex& operator=(char *s)
	{
	    char *tmpstr = new char[strlen(s)];
	    strcpy(tmpstr, s);
		char*temp = strtok(tmpstr, "+");
		r = atof(temp);
		temp = strtok(NULL, "i");
		i = atof(temp);
		return *this;
	}
};

int main()
{
	Complex a;
	a = "3+4i";
	a.Print();
	a = "5+6i";
	a.Print();
	return 0;
}