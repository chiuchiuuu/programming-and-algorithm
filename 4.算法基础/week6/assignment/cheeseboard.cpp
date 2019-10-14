#include <iostream>
#include <string.h>
using namespace std;
int n, k, total, m;
/*n: the col number 
* k: the cheese pieces number
* m: the number of the pieces that already in
*/
int book[10];   //record whether one col has been used
char a[10][10]; //record the cheeseboard

void DFS(int current)
{
    if (k == m)
    {
        // all the pieces have been put in
        total++;
        return;
    }
    if (current > n)
        return; //beyond the board
    for (int i = 0; i < n; i++)
        if (book[i] == 0 && a[current][i] == '#')
        {
            book[i] = 1;
            m++;
            DFS(current + 1);
            book[i] = 0;
            m--;
        }
    DFS(current + 1);
}
int main()
{
    int i, j;
    while (cin >> n >> k && (n != -1 && k != -1))
    {
        total = 0;
        m = 0;
        for (i = 0; i < n; i++)
        {
            //getchar();
            for (j = 0; j < n; j++)
                cin >> a[i][j];
        }
        memset(book, 0, sizeof(book));
        DFS(0);
        cout << total << endl;
    }
    return 0;
}
/*
*Sample Input:
2 1
#.
.#
4 4
...#
..#.
.#..
#...
-1 -1
* Sample Output:
2
1

*/