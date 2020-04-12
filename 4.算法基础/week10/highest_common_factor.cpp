#include<stdio.h>
int main() {
    int a,b;
    while (scanf("%d%d", &a,&b) != EOF) {
        while ( b != 0) {
            int temp = a % b;
            a=b; b = temp;
        }
        printf("%d\n", a);
    }
    return 0;
}
