#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int divs[500001];
int perfects[500001];


void mult_table ()
{
    int i, j;

    for (i = 1; i <= 500000; i++)
        for (j = 1; i*j <= 500000; j++) {
            divs[i*j]++;
            if (i == j)
                perfects[i*j] = 1;
        }
}


int calc_power (int n, int p, int *overflow)
{
    int i, res = 1, tmp, perfect;

    if (!p) {
        *overflow = 0;
        return 1;
    }

    *overflow = n >= 10000;
    n %= 10000;

    for (i = 0; i < p; i++) {
        res *= n;
        if (!*overflow)
            *overflow = res >= 10000;
        res %= 10000;
    }

    return res;
}


int main(int argc, char *argv[])
{
    int n, t, orig, mults, res, overflow, perfect;

    mult_table ();
    scanf ("%d", &n);

    while (n--) {
        scanf ("%d", &t);
        orig = t;
        mults = divs[t];
        perfect = perfects[t];
/*         printf ("%d has %d multiplicators (perfect = %d)\n", t, mults, perfect); */
        mults -= 2;

        if (perfect) {
            t = (int)sqrt (t);
            res = calc_power (t, mults, &overflow);
        }
        else {
            mults >>= 1;
            res = calc_power (t, mults, &overflow);
        }

/*         if (overflow) */
/*             printf ("%d^%d = %04d\n", t, mults, res); */
/*         else */
/*             printf ("%d^%d = %d\n", t, mults, res); */
/*         if (overflow) */
/*             printf ("%d: %04d\n", orig, res); */
/*         else */
/*             printf ("%d: %d\n", orig, res); */
        if (overflow)
            printf ("%04d\n", res);
        else
            printf ("%d\n", res);
    }

    return 0;
}
