#include <iostream>
using namespace std;

int n[1001];
void fun() {
    for (int k=1; k<=1000; k++){
        int minarea=100000;
        for (int len=1; len<=k; len++) {
            if (k%len==0) {
                int maxwi=k/len;
                for(int wi=1; wi<=maxwi; wi++) {
                    if (maxwi%wi==0) {
                        int hi=maxwi/wi;
                        int area=(len*wi+len*hi+wi*hi)*2;
                        if (minarea>area) {
                            minarea=area;
                        }
                    }
                }
            }
        }
        n[k]=minarea;
    }
}

int main() {
    int c;
    cin >> c;
    fun();
    int i;
    while(c--) {
        cin >> i;
        cout << n[i] << endl;
    }
    return 0;
}
