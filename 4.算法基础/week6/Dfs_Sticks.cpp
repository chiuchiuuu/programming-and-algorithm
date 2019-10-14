/*
Description

George took sticks of the same length and cut them randomly until all parts became at most 50 units long. Now he wants to return sticks to the original state, but he forgot how many sticks he had originally and how long they were originally. Please help him and design a program which computes the smallest possible original length of those sticks. All lengths expressed in units are integers greater than zero.
Input

The input contains blocks of 2 lines. The first line contains the number of sticks parts after cutting, there are at most 64 sticks. The second line contains the lengths of those parts separated by the space. The last line of the file contains zero.
Output

The output should contains the smallest possible length of original sticks, one per line.
Sample Input

9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0
Sample Output

6
5*/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
vector<int> len(65);
int used[65]; //Marker whether is used
int L;        //proposal of the length of the stick
int n;        //proposal of the number of the stick

/*when rest stick parts left, and current stick still need needLen to achieve the goal length*/
// in such case, whether the search has a result
bool dfs(int rest, int needLen, int lastIndex)
{
    if (rest == 0 && needLen == 0)
        return true;
    if (needLen == 0)
        // one stick is completed
        needLen = L;
    //Pruning 4: multi sticks part to construct one complete strick, and do it in an order (long to short)
    // No need to search the case that the current stick part is langer than the former,
    //since if that case could work, it just means a different order
    int startIndex = needLen == L ? 0 : lastIndex + 1;
    for (int i = startIndex; i < n; i++)
    {
        //Pruning 1: we do not try the same length at the same case
        if (i > 0 && !used[i - 1] && len[i - 1] == len[i])
            continue;
        if (!used[i] && len[i] <= needLen)
        {
            used[i] = 1;
            if (dfs(rest - 1, needLen - len[i], i))
                return true;
            else
            {
                // this trial failed, and switch to next part
                used[i] = 0;
                // Pruning 2:when i as the first part and cannot work, then this part
                //could never be used, thus the length proposal is dropped.
                if (needLen == L ||
                    //Pruning 3: if len[i] is the last part,
                    needLen == len[i])
                    return false;
            }
        }
    }
    return false;
}
int main()
{
    while (cin>>n && n>0)
    {
        len.clear();
        int minLen = 0;
        int totalLen = 0;
        int tempLen;
        for(int i = 0;i<n; i++) {
            cin >> tempLen;
            len.push_back(tempLen);
            totalLen += tempLen;
        }
        // sort the stick parts
        sort(len.begin(), len.end(), greater<int>());
        for( L =len[0]; L<= totalLen/2; L++)
        {
            if(totalLen%L)
                continue;
            memset(used, 0, sizeof(used));
            if(dfs(n,L,-1))
            {
                minLen = L;
                break;
            }
        }
        if(L>totalLen/2)
        {
            minLen = totalLen;
        }
        cout<<minLen<<endl;
    }
    return 0;
}