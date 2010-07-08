#include <stdio.h>
#include <stdlib.h>

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


int brute (unsigned long long from, unsigned long long to)
{
    int res = 0;
    int max_digit, digits, a, b;

    while (from <= to) {
        if (stat (from, &max_digit, &digits) == stat (from << 1, &a, &b))
            res++;
        from++;
        if (max_digit >= 5)
            from = pows[digits];
    }

    return res;
}


int main(int argc, char *argv[])
{
    int t;
    unsigned long long v1, v2;

    scanf ("%d", &t);

    while (t--) {
        scanf ("%llu %llu", &v1, &v2);
        printf ("%d\n", brute (v1, v2));
    }
    
    return 0;
}
