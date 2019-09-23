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
int leftMInTime[MAX_N+10], rightMinTime[MAX_N+10], L[MAX_N+10];
int MinTime(int l, bool bLeft)
{
    int y = platForms[l].h;
    int x;
    if(bLeft)
        x = platForms[l].Lx;
    else
        x = platForms[l].Rx;
    int i;
    for( i=l+1;i<=n;i++)
    {
        if (platForms[i].Lx<= x && platForms[i].Rx >=x)
            break;
        if (i<=n)
        {
            if( y-platForms[i].h > maxHeight)
                return INFINITE;
        }
        else
        {
            if (y>maxHeight)
                return INFINITE;
            else
                return y;
        }
        int nLeftTime = y - platForms[i].h + x - platForms[i].Lx;
        int nRightTime = y - platForms[i].h + platForms[i].Rx -x;
        if(leftMInTime[i] == -1)
        {
            leftMInTime[i] = MinTime(i, true);
        }
        if( L[i] == -1)
        {
            L[i] = MinTime(i, false);
        }
        nLeftTime += leftMInTime[i];
        nRightTime += L[i];
        if(nLeftTime < nRightTime)
            return nLeftTime;
        return nRightTime;
    }
}

int main() {
    cin>>t;
    for( int i = 0;i < t; i ++ ) {
        memset(leftMInTime,-1,sizeof(leftMInTime));
        memset(L,-1,sizeof(rightMinTime));
        cin>>n>>x>>y>>maxHeight;
        platForms[0].Lx = x; 
        platForms[0].Rx = x;
        platForms[0].h = y;
        for( int j = 1; j <= n; j ++ )
            cin>>platForms[j].Lx>>platForms[j].Rx>>platForms[j].h;
        sort(platForms,platForms+n+1);
        printf("%d\n", MinTime(0,true));
        }
    return 0;
}
/*
1
3 8 17 20
0 10 8
0 10 13
4 14 3 
/***/