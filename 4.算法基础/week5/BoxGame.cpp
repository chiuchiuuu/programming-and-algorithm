#include <iostream>
#include <cstring>
using namespace std;

struct Block
{
    int color;
    int len;
};
struct Block segment[200];
int score[200][200][200]; //store the computation result, avoid the repeated computation
int click_box(int start, int end, int extra_len)
{
    int i, result, temp;
    if (score[start][end][extra_len] > 0)
        return score[start][end][extra_len];
    result = segment[end].len + extra_len;
    result = result * result;
    if (start == end)
    {
        score[start][end][extra_len] = result;
        return score[start][end][extra_len];
    }
    result += click_box(start, end - 1, 0);
    i = end - 1;
    for (i = end - 1; i >= start; i--)
    {
        if (segment[i].color != segment[end].color)
            continue;
        temp = click_box(start, i, segment[end].len + extra_len) + click_box(i + 1, end - 1, 0);
        if (temp <= result)
            continue;
        result = temp;
    }
    score[start][end][extra_len] = result;
    return score[start][end][extra_len];
}
int main()
{
    int t, n, i, j, end, color;
    cin >> t;
    for (i = 0; i < t; i++)
    {
        cin >> n;
        end = 0;
        cin >> segment[end].color;
        segment[end].len = 1;
        for (j = 1; j < n; j++)
        {
            cin >> color;
            if (color == segment[end].color)
                segment[end].len++;
            else
            {
                end++;
                segment[end].color = color;
                segment[end].len = 1;
            }
        }
        memset(score, 0, sizeof(score));
        cout << "Case " << i + 1 << ": " << click_box(0, end, 0) << endl;
    }
    return 0;
}