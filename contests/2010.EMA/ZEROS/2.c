#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(int argc, char *argv[])
{
    unsigned long long n, p, i, res;

    scanf ("%llu", &n);

    while (n--) {
        scanf ("%llu", &p);
        res = 0;
        while (p > 0) {
            p /= 5;
            res += p;
        }

        printf ("%llu\n", res);
    }
    return 0;
}
