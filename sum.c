#include  <stdio.h>

int a = 8, b = -3, m = 10;

int summation(int n) {
    int sum = 0, mult, x = 0, c;
    do {
        mult = 0;
        c = 0;
        do {
            mult += x;
            c++;
        } while(c < a);
        sum += mult;
        sum += b;
        x++;
    } while(x <= n);
    return sum;
}

int main(void)
{
    for(int i = 0; i <= m; i++) {
        int sum = summation(i);
        printf("%2d  %x :   %3d  %08x\n", i, i, sum, sum);
    }
    return 0;
}