#include <stdio.h>
#include <stdlib.h>


unsigned long long solve2 (int n, int c)
{
    printf ("solve2 (%d, %d)\n", n, c);

    if (n > c)
        return c+1;
    else
        return n+1;
}


#define MIN(a, b) ((a < b) ? (a) : (b))


unsigned long long solve3 (int n, int b, int c)
{
    int i;

    unsigned long long res = 0;

    //    printf ("solve3 (%d, %d, %d)\n", n, b, c);

    for (i = 0; i <= b && i <= n; i++) {
        res += MIN (n-i, c)+1;
    }

    return res;
}


unsigned long long solve4 (int n, int a, int b, int c)
{
    int i;
    unsigned long long res = 0;

    //    printf ("solve4 (%d, %d, %d, %d)\n", n, a, b, c);

    for (i = 0; i <= a && i <= n; i++)
        res += solve3 (n-i, b, c);

    return res;
}


int main (int argc, char *argv[])
{
    int t, n, a, b, c;

    scanf ("%d", &t);

    while (t--) {
        scanf ("%d %d %d %d", &n, &a, &b, &c);
        printf ("%llu\n", solve4 (n, a, b, c));
    }

    return 0;
}
