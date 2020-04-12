#include<iostream>
#include<string>
#include<queue>
#include<sstream>
#include <stdlib.h>

using namespace std;

string str[20];
string command;
int N;

inline	string Copy();
inline	string Add();
inline	int Find();
inline	int Rfind();
inline void Insert();
inline	void Reset();
inline string GetString();
inline void PrintAll();
inline void Print();
inline int GetInt();
inline bool strProcess();

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> str[i];
	}
	while (cin >> command) {
		if (command == "over")
			break;
		switch (command.at(1))
		{
		case 'n':Insert(); break;
		case 'e':	Reset(); break;
		case 'r':	
			if (command == "print")
				Print();
			else
				PrintAll();
			break;
		default:
			break;
		}
	}
}


string GetString() {
	string temp_command;
	cin >> temp_command;
	if (temp_command == "copy")
		return Copy();
	else if (temp_command == "add")
	{
		return Add();
	}
	else
	{
		return temp_command;
	}
}
int MyAtoi(string s) {
	int m = 0;
	for (int i = 0; i < s.length(); i++) {
		if ((s.at(i) >= '0') && (s.at(i) <= '9')) {
			m = m * 10 + s.at(i) - '0';
		}
	}
	return m;
}
int GetInt() {
	string temp_command;
	cin >> temp_command;
	if (temp_command == "find") {
		return Find();
	}
	else if (temp_command == "rfind")
		return Rfind();
	else
	{
		return MyAtoi(temp_command);
	}
}
void Insert() //insert S N X: 在第N个字符串的第X个位置插入S字符串
{
	string s;
	int n, x;
	s = GetString();
	n = GetInt();
	x = GetInt();
	str[n].insert(x, s);
}
void Reset() { //Reset s n; 将第N个字符串变为S
	string s;
	int n;
	s = GetString();
	n = GetInt();
	str[n].assign(s);
}
int Rfind() {//rfing S N 在第N个字符串从右向左寻找S字符串，返回其第一次出现的位置，若没有找到
	//返回字符串长度
	string s;
	int n, idex;
	s = GetString();
	n = GetInt();
	idex = str[n].rfind(s);
	if (idex == string::npos) {
		return str[n].length();
	}
	else
	{
		return idex;
	}
}
int Find() {//第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度
	string s;
	int n, idex;
	s = GetString();
	n = GetInt();
	idex = str[n].find(s);
	if (idex == string::npos) {
		return str[n].length();
	}
	else
	{
		return idex;
	}
}

string Copy() {
	int n, x, l;
	n = GetInt();
	x = GetInt();
	l = GetInt();
	return str[n].substr(x, l);
}

int GetString_Judge(string s) {
	int i,m=0;
	for ( i=0; i < s.length(); i++) {
		if ((s.at(i) >= '0') && (s.at(i) <= '9')) {
			m = m * 10 + s.at(i) - '0';
		}
		else
		{
			break;
		}
	}
	if (i != s.length() || m > 9999) {
		m = -1;
	}
	return m;
}

string Add() {//add S1 S2：判断S1，S2是否为0-99999之间的整数，若是则将其转化为整数做加法，
	//若不是，则作字符串加法，返回的值为一字符串。
	string s1, s2;
	int m1, m2;
	s1 = GetString();
	s2 = GetString();
	m1 = GetString_Judge(s1);
	m2 = GetString_Judge(s2);
	if (m1 == -1 || m2 == -1) {
		return (s1 + s2);
	}
	else
	{
		m1 += m2;
		string s1;
		stringstream out;
		out << m1;
		s1 = out.str();
		return s1;
	}

}
void Print() {
	int n;
	n = GetInt();
	cout << str[n] << endl;
}

void PrintAll() {
	for (int i = 1; i <= N; i++) {
		cout << str[i] << endl;
	}
}