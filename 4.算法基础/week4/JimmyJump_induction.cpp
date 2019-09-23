#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define MAX_N 100
#define INFINITE 100000000

int t, n, x, y, maxHeight;
struct Platform
{
    int Lx, Rx, h;
    bool operator<(const Platform &p2) const{
        return h>p2.h;
    }
};
Platform platForms[MAX_N+10];
int leftMInTime[MAX_N+10]; //各板子从左走的最短时间
int rightMinTime[MAX_N+10]; //各板子从右走的最短时间

int main()
{
    cin>>t;
    while (t--)
    {
        cin>>n>>x>>y>>maxHeight;
        platForms[0].Lx=x;
        platForms[0].Rx=x;
        platForms[0].h=y;
        for(int j=1; j<=n; j++)
        {
            cin>>platForms[j].Lx>>platForms[j].Rx>>platForms[j].h;
        }
        sort(platForms, platForms+n+1);
        for(int i=n; i>=0; --i) 
        {
            int  j;
            for(j=i+1; j<=n; ++j)
            {   //找到i的左端的下面的那块板子
                if (platForms[i].Lx<=platForms[j].Rx && platForms[i].Lx >= platForms[j].Lx)
                    break;
            }
            if(j>n) 
            {   //找不到
                if(platForms[i].h > maxHeight)
                    leftMInTime[i] = INFINITE;
                else
                    leftMInTime[i] = platForms[i].h;
            }
            else
            {
                    int y = platForms[i].h - platForms[j].h;
                    if( y > maxHeight)
                        leftMInTime[i] = INFINITE;
                    else
                        leftMInTime[i] = y+min(leftMInTime[j]+platForms[i].Lx-platForms[j].Lx, 
                                 rightMinTime[j]+platForms[j].Rx-platForms[i].Lx );
            }
            for(j=i+1;j<=n; ++j){
                //找到i的右端的下面的呢块板子
                if( platForms[i].Rx <= platForms[j].Rx && platForms[i].Rx >= platForms[j].Lx)
                    break;
            }
            if( j > n ) {
                if( platForms[i].h > maxHeight )
                    rightMinTime[i] = INFINITE;
                else 
                    rightMinTime[i] = platForms[i].h;
                }
            else {
                int y = platForms[i].h - platForms[j].h;
                if( y > maxHeight) rightMinTime[i] = INFINITE;
                else
                    rightMinTime[i] = y + min(leftMInTime[j]+platForms[i].Rx-platForms[j].Lx,
                        rightMinTime[j]+platForms[j].Rx-platForms[i].Rx);
                }
        }
        printf("%d\n", min(leftMInTime[0],rightMinTime[0]));
    }
    return 0;
}