#include <stdio.h>
#include <stdlib.h>


unsigned long long binom (unsigned long long n, unsigned long long m)
{
    unsigned long long res = 1, d;

    for (d = 1; d <= m; d++) {
        res *= n--;
        res /= d;
    }

    return res;
}


int main (int argc, char *argv[])
{
    int t;
    unsigned long long n, m;
    
    scanf ("%d", &t);
    while (t--) {
        scanf ("%llu %llu", &n, &m);
        if (n < m)
            printf ("0\n");
        else {
            if (m > n-m)
                printf ("%llu\n", binom (n, n-m));
            else
                printf ("%llu\n", binom (n, m));
        }
    }
    return 0;
}
