#include <stdio.h>
#include <stdlib.h>


#define MIN(a, b) ((a < b) ? (a) : (b))


unsigned int solve3 (int n, int b, int c)
{
    int i;

    unsigned int res = 0;

    //    printf ("solve3 (%d, %d, %d)\n", n, b, c);

    for (i = 0; i <= b && i <= n; i++) {
        res += MIN (n-i, c)+1;
    }

    return res;
}


unsigned int solve4 (int n, int a, int b, int c)
{
    int i;
    unsigned int res = 0;

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
        printf ("%u\n", solve4 (n, a, b, c));
    }

    return 0;
}
