#include <stdio.h>
#include <stdlib.h>


unsigned long long mod_pow (unsigned long long base, unsigned long long exp, int mod)
{
    unsigned long long res = 1;
    printf ("%llu^%llu %% %d = ", base, exp, mod);

    while (exp) {
        if (exp % 2)
            res = (res * base) % mod;
        exp >>= 1;
        base = (base*base) % mod;
    }

    printf ("%llu\n", res);
    return res;
}


int main (int argc, char *argv[])
{
    int t, p;
    unsigned long long n, k, i, res;

    scanf ("%d", &t);

    while (t--) {
        scanf ("%llu %llu %d", &n, &k, &p);
        res = 0;

        for (i = 0; i <= n; i++) {
            res += mod_pow (k, i, p) % 1000003;
            res %= 1000003;
        }
        printf ("%d\n", res);
    }

    return 0;
}
