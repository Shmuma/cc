#include <stdio.h>
#include <stdlib.h>

/* 
In[3]:= P[n_] := Sum[Binomial[n - 1, i], {i, 0, n - 1}]

In[9]:= F[n_] := P[n]*(n + 1)*n/2

In[11]:= R[n_] := Sum[F[i], {i, 1, n}]

In[15]:= Map[R, {1, 2, 3}]

Out[15]= {1, 7, 31}

2^n (n (n - 1)/2 + 1) - 1

 */

unsigned int table[] = {
    1, 7, 31, 111, 351, 1023, 2815, 7423, 18943, 47103, 114687, 274431,
    647167, 1507327, 3473407, 7929855, 1179647, 6815743, 6291455,
    7340031, 6291455, 8388607
};


int main (int argc, char *argv[])
{
    int t;
    unsigned long long n;

    scanf ("%d", &t);

    while (t--) {
        scanf ("%llu", &n);

        if (sizeof (table) / sizeof (table[0]) <= n)
            puts ("8388607");
        else
            printf ("%d\n", table[n-1]);
    }
    return 0;
}
