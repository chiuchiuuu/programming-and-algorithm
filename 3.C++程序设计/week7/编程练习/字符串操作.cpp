#include <iostream>
#include <iomanip>
#include<sstream>
#include<string>
using namespace std;

string str[21];
int num_of_str = 0;

int string_to_int(string string1) {
	int number;
	istringstream num(string1);
	num >> number;
	return number;
}
bool is_Num(string s) {
	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}

int rfind() {
	char s;
	int n;
	cin >> s >> n;
	return str[n].rfind(s);
}
int find() {
	char s;
	int n;
	cin >> s >> n;
	return str[n].find(s);
}
int get_int() {
	string str;
	cin >> str;
	if (is_Num(str)) {
		return string_to_int(str);
	}
	else if (str == "rfind") {
		return rfind();
	}
	else if (str == "find") {
		return find();
	}
}

string add();//此处的函数用来进行占位，防止报错

string copy() {
	int n, x, l;
	n = get_int();
	x = get_int();
	l = get_int();
	return str[n].substr(x, l);
}

string get_char() {
	string str;
	cin >> str;
	if (str == "copy") {
		return copy();
	}
	else if (str == "add") {
		return add();
	}
	else {
		return str;
	}
}

string int_to_string(int d) {
	ostringstream ss;
	ss << d;
	return ss.str();
}

string add() {
	string s1 = get_char();
	string s2 = get_char();
	if (is_Num(s1) && is_Num(s2) && string_to_int(s1) >= 0 && string_to_int(s1) <= 99999 && string_to_int(s2) >= 0 && string_to_int(s2) <= 99999)
	{
		return int_to_string(string_to_int(s1) + string_to_int(s2));
	}
	else
	{
		return s1 + s2;
	}
}






void insert() {
	string S = get_char();
	int num_str = get_int();
	int num_word = get_int();
	str[num_str].insert(num_word, S);
}

void print() {
	int n;
	cin >> n;
	cout << str[n] << endl;
}

void printall() {
	for (int i = 1; i <= num_of_str; i++)
		cout << str[i] << endl;
}

void reset() {
	string s = get_char();
	int n = get_int();
	str[n].replace(str[n].begin(), str[n].end(), s);
}
int main()
{
	cin >> num_of_str;

	for (int i = 1; i <= num_of_str; i++) {
		cin >> str[i];
	}
	while (true)
	{
		string operation;
		cin >> operation;
		if (operation == "insert")
		{
			insert();
		}
		else if (operation == "reset")
		{
			reset();
		}
		else if (operation == "print")
		{
			print();
		}
		else if (operation == "printall")
		{
			printall();
		}
		else if (operation == "over")
		{
			break;
		}
	}
}