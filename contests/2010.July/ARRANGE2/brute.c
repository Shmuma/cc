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



unsigned long long stat (unsigned long long n)
{
    unsigned long long res = 0;

    while (n) {
        res += pows[n % 10];
        n /= 10;
    }

    return res;
}


int brute (unsigned long long from, unsigned long long to)
{
    int res = 0;

    while (from <= to) {
        if (stat (from) == stat (from << 1))
            res++;
        from++;
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
