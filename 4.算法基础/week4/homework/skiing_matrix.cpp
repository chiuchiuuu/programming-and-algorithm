#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

#define Max 100
int map[Max][Max], length[Max][Max];
int n=0, m=0;
int max_length=0;
int search(int a, int b);

int main() 
{
    while(cin>>n>>m)
    {
        max_length = 0;
        for(int i=0;i<n;i++)
            for(int j=0; j<m; j++)
                cin>>map[i][j];
        memset(length, 0, sizeof(length));
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                search(i,j);
        cout<<max_length<<endl;
    }
    return 0;
}

int search(int a, int b)
{
    if(length[a][b]!=0)
        return length[a][b];
    int max=0;
    if(a-1>=0 && map[a][b]> map[a-1][b])
    {
        if(max<search(a-1,b))
            max=search(a-1,b);
    }
    if(b-1>=0 && map[a][b-1] < map[a][b])
        if(max < search(a,b-1))
            max = search(a, b-1);
    if(b+1<m && map[a][b+1]< map[a][b])
        if(max < search(a, b+1))
            max = search(a, b+1);
    if(a+1<n && map[a][b] > map[a+1][b])
        if(max < search(a+1,b)) 
            max = search(a+1,b);
    length[a][b] = max + 1;
    if(max_length<length[a][b])
        max_length = length[a][b];
    return length[a][b];
}