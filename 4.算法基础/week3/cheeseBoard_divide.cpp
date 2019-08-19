int s[9][9]; // the score in every grid
int sum[9][9]; // the sum of the rectangel with (1,1) to (i,j)
int res[15][9][9][9][9]; // table for fun f

int calSum(int x1, int y1, int x2, int y2) { 
    //the sum of scores from (x1, y1) to (x2, y2)
    return sum[x1][y2] - sum[x2][y1-1] - sum[x1-1][y2] + sum[x1-1][y1-1];
}

int fun(int n, int x1, int y1, int x2, int y2) {
    int t, a, b, c, e, MIN = 1000000;
    if (res[n][x1][y1][x2][y2] != -1)
    {
        return res[n][x1][y1][x2][y2];
    }
    if (n==1) //if only one piece needs to be divided
    {
        t = calSum(x1,y1, x2,y2);
        res[n][x1][y1][x2][y2] = t * t;
        return t * t;
    }
    
    


}