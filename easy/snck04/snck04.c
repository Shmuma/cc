#include <stdio.h>
#include <stdlib.h>


int solve (int n);



int main (int argc, char *argv[])
{
    int t, n;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        printf ("%d\n", solve (n));
    }
    return 0;
}


inline int abs (int n)
{
    return n < 0 ? -n : n;
}


int gcd (int a, int b)
{
    printf ("gcd %d, %d\n", a, b);
    while (b)
        b ^= a ^= b ^= a %= b;
    return a;
}


/* Need to check this: http://en.wikipedia.org/wiki/Coprime#Generating_all_coprime_pairs */

int solve (int n)
{
    int i, j, res = 0;
    int j_inc;

    for (i = 1; i <= n; i++) {
        j = i+1;
        j_inc = 2 - (i % 2);
        while (j <= n) {
            if (gcd (i, j) == 1)
                res++;
            j += j_inc;
        }
    }

    return res;
}
