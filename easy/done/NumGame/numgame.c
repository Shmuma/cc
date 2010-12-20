#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_PRIMES 10000
#define CACHE_MAX 1000000

unsigned int cache[CACHE_MAX][2];
int cache_size;

int primes[MAX_PRIMES];
int primes_count;


void make_primes (int max)
{
    int val, i, max_mul, is_prime;

    primes_count = 1;
    primes[0] = 2;
    val = 3;

    while (val <= max && primes_count < MAX_PRIMES) {
        i = 0;
        max_mul = (int)sqrt (val);
        is_prime = 1;
        while (i < primes_count && primes[i] <= max_mul) {
            if ((val % primes[i]) == 0) {
                is_prime = 0;
                break;
            }
            i++;
        }

        if (is_prime)
            primes[primes_count++] = val;
        val += 2;
    }
}


int is_prime (unsigned int n)
{
    int i;

    if (n == 1)
        return 1;

    for (i = 0; i < primes_count; i++)
        if ((n % primes[i]) == 0)
            return 0;

    return 1;
}


void cache_res (unsigned int n, unsigned int res)
{
    if (cache_size < CACHE_MAX) {
        cache[cache_size][0] = n;
        cache[cache_size][1] = res;
        cache_size++;
    }
}


int check_cache (unsigned int n)
{
    int i;

    for (i = 0; i < cache_size; i++) {
        if (cache[i][0] == n)
            return cache[i][1];
    }

    return -1;
}


/* return 0 if we will lost this turn, 1 if won */
unsigned int solve (unsigned int n)
{
    int div_ofs, res;
    unsigned int nn;

    if (n == 1)
        return 0;

    res = check_cache (n);
    if (res >= 0)
        return res;

    //    printf ("solve (%u)\n", n);

    for (div_ofs = 0; div_ofs < primes_count && n > primes[div_ofs]; div_ofs++) {
        nn = n;
        while ((nn % primes[div_ofs]) == 0) {
            nn /= primes[div_ofs];
            if (nn == 1)
                goto won;
            //            if (!is_prime (nn-1))
            if (!solve (nn-1))
                goto won;
        }
        div_ofs++;
    }

    if (!solve (n - 1))
        goto won;

    cache_res (n, 0);
    return 0;

 won:
    cache_res (n, 1);
    return 1;
}


int main (int argc, char *argv[])
{
    int t;
    unsigned int n, res;

    //    make_primes (35000);

    scanf ("%d", &t);
    while (t--) {
        scanf ("%u", &n);
        /*        res = solve (n);
        if ((n % 2 && res != 0) || (n % 2 == 0 && res == 0)) {
            printf ("%6u\t", n);
            if (res)
                puts ("ALICE");
            else
                puts ("BOB");
        }
        */
        if (n % 2)
            puts ("BOB");
        else
            puts ("ALICE");
    }

    return 0;
}
