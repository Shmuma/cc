#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


unsigned long long pows[] = {
    1ULL,
    10ULL,
    100ULL,
    1000ULL,
    10000ULL,
    100000ULL,
    1000000ULL, 
    10000000ULL,
    100000000ULL,
    1000000000ULL,
    10000000000ULL,
    100000000000ULL,
};



unsigned long long stat (unsigned long long n, int* max_dig, int* digits)
{
    unsigned long long res = 0;

    *max_dig = 0;
    *digits = 0;

    while (n) {
        *max_dig = n % 10;
        res += pows[*max_dig];
        n /= 10;
        *digits += 1;
    }

    return res;
}


int main(int argc, char *argv[])
{
    int t;
    unsigned long long v1, v2;
    int max_dig, digits;
    int a, b;

/*     scanf ("%d", &t); */
/*     while (t--) { */
/*         scanf ("%llu %llu", &v1, &v2); */
/*     } */

    v1 = 0;

    while (v1 <= 10000000000ULL) {
        if (stat (v1, &max_dig, &digits) == stat (v1 << 1, &a, &b))
            printf ("%llu\n", v1);
        v1++;
        if (max_dig >= 5)
            v1 = pows[digits];
    }

    return 0;
}
