#include<iostream>
#include<cstring>

using namespace std;
char sz1[1000];
char sz2[1000];
int maxLen[1000][1000];
int main()
{
    while (cin>>sz1>>sz2)
    {
        int length1 = strlen(sz1);
        int length2 = strlen(sz2);
        cout<<length2<<endl;
        int nTemp;
        int i,j;
        for(i=0;i<=length1;i++)
            maxLen[i][0]=0;
        for (j=0; j<=length2;j++)
            maxLen[0][j]=0;
        for(i=1; i<=length1; i++)
            for(j=1; j<=length2; j++) 
            {
                if(sz1[i-1]==sz2[j-1])
                    maxLen[i][j] = maxLen[i-1][j-1] +1;
                else
                {
                    maxLen[i][j] = max(maxLen[i][j-1], maxLen[i-1][j]);
                }
            }
            cout<<maxLen[length1][length2]<<endl;
        
    }
    return 0;
}