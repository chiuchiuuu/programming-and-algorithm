#include <iostream>
#include <string>
#include <set>
#include<stdio.h>
using namespace std;
#pragma warning(disable: 4996)

bool stop = false;
int i =1;
bool top_output = true;

void printItem(int hierachy, string item) {
    if(hierachy == 0 && top_output) {
        cout<<"DATA SET "<< i << endl;
        i++;
        top_output = false;
    }

    for (int i = 0; i < hierachy; i++) {

		cout << "|        ";
	}
	cout << item << endl;
}

void presentFile(int hierachy, string curDir) {
    set<string> Files;
    string item;
    while (cin>>item)
    {
        if(item == "]" || item == "*") {
            set<string>::iterator i;
            for(i=Files.begin(); i != Files.end(); i++) {
                printItem(hierachy, *i);
            }
            if(item == "*") {
                top_output=true;
                cout<<endl;
                }
            return;
        }
        if(item == "#") {
            stop = true;
            break;
            return;
        }
        if(item[0] == 'f') {
            Files.insert(item);
            //cout<<"get one file"<<endl;
        }
        else if( item[0] == 'd') {
            presentFile(hierachy + 1, item);
            printItem(hierachy, curDir);
            //cout<<"get one fir"<<endl;
        }
        
    }
}
int main() {
    while(!stop) {
        presentFile(0, "ROOT");
    }
    return 0;
}
