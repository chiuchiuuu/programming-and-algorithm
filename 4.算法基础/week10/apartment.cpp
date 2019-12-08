#include <stdio.h>

/*  dir:u,d,l,r
 *  face:ABDC,BFHD,FEGH,EACG,EFBA,GHDC
 *  next[face][dir]
 */

#define TEST
#undef TEST

const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const int next[6][4] = {{4, 5, 3, 1}, {4, 5, 0, 2}, {4, 5, 1, 3},
                        {4, 5, 2, 0}, {2, 0, 3, 1}, {2, 0, 3, 1}};
int map[6][20][20];
int num, max, cases, n, area;

int bfs(int face, int i, int j) {
  int sum = 1;
  int I, J, F;
  map[face][i][j] = 1;
  for (int d = 0; d < 4; d++) {
    I = i + dir[d][0];
    J = j + dir[d][1];
    F = face;
    if ((face - 4) * (face - 5)) {
      if (J < 0)
        F = next[face][2], J = n - 1;
      if (J >= n)
        F = next[face][3], J = 0;
    }
    if ((face - 1) * (face - 3)) {
      if ((I < 0 || I >= n) && face == 2)
        J = n - 1 - J;
      if (I < 0)
        F = next[face][0], (face == 2 || face == 4) ? I = 0 : I = n - 1;
      if (I >= n)
        F = next[face][1], (face == 0 || face == 5) ? I = n - 1 : I = 0;
      if (F != face && F == 2)
        J = n - 1 - J;
    }
    if (face * (face - 2)) {
      switch (face) {
      case 4:
        if (J < 0)
          F = next[face][2], J = I, I = 0;
        if (J >= n)
          F = next[face][3], J = n - 1 - I, I = 0;
        break;
      case 5:
        if (J < 0)
          F = next[face][2], J = I, I = n - 1;
        if (J >= n)
          F = next[face][3], J = n - 1 - I, I = n - 1;
        break;
      case 1:
        if (I < 0)
          F = next[face][0], I = n - 1 - J, J = n - 1;
        if (I >= n)
          F = next[face][1], I = n - 1 - J, J = n - 1;
        break;
      case 3:
        if (I < 0)
          F = next[face][0], I = J, J = 0;
        if (I >= n)
          F = next[face][1], I = J, J = 0;
        break;
      }
    }
    if (!map[F][I][J]) {
#ifdef TEST
      printf("%d:%d %d %d ", d, face, i, j);
      printf("-> %d %d %d\n", F, I, J);
#endif
      sum += bfs(F, I, J);
    }
  }
  return sum;
}
void test() {
  for (int face = 0; face < 6; face++) {
    printf("face:%d\n", face);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        printf("%d%c", map[face][i][j], (j == n - 1) ? '\n' : ' ');
  }
  printf("\n\n");
  return;
}

int main() {
#ifdef TEST
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  scanf("%d", &cases);
  while (cases--) {
    scanf("%d", &n);
    num = 0;
    max = 0;
    for (int face = 0; face < 6; face++)
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          scanf("%d", &map[face][i][j]);
    for (int face = 0; face < 6; face++)
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          if (!map[face][i][j]) {
#ifdef TEST
            printf("%d %d %d\n\n", face, i, j);
            test();
#endif
            num++;
            area = bfs(face, i, j);
            if (area > max)
              max = area;
#ifdef TEST
            printf("num=%d,nowArea=%d,max=%d\n", num, area, max);
#endif
          }
    printf("%d %d\n", num, max);
  }
  return 0;
}
