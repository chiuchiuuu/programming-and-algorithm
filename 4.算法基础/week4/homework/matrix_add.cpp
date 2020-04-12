#include<iostream>
using namespace std;
int main()
{
    int n, s, A[10000], B[10000], aNum, bNum, num;
    cin >> n;
    while(n--)
    {
        num = 0;
        cin >> s >> aNum;
        for(int i = 0; i < aNum; i++)
            cin >> A[i];
        cin >> bNum;
        for(int i = 0; i < bNum; i++)
            cin >> B[i];
        for(int i = 0; i < aNum; i++)
        {
            for(int j = 0; j < bNum; j++)
            {
                if(A[i] + B[j] == s)
                    num++;
            }
        }
        cout << num << endl;
    }
    //system("pause");
    return 0;
}