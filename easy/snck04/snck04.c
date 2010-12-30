#include <stdio.h>
#include <stdlib.h>


int max_n;


#define MAX_PRIMES 10000

int primes[MAX_PRIMES];
int primes_count;


unsigned int cache[1000][2];
unsigned int cache_size;



unsigned long isqrt(unsigned long x)  
{  
    register unsigned long op, res, one;  
  
    op = x;  
    res = 0;  
  
    /* "one" starts at the highest power of four <= than the argument. */  
    one = 1 << 30;  /* second-to-top bit set */  
    while (one > op) one >>= 2;  
  
    while (one != 0) {  
        if (op >= res + one) {  
            op -= res + one;  
            res += one << 1;  // <-- faster than 2 * one  
        }  
        res >>= 1;  
        one >>= 2;  
    }  
    return res;  
}  


void make_primes (int max)
{
    int val, i, max_mul, is_prime;

    primes_count = 1;
    primes[0] = 2;
    val = 3;

    while (val <= max && primes_count < MAX_PRIMES) {
        i = 0;
        max_mul = isqrt (val);
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




/* http://en.wikipedia.org/wiki/Totient#Computing_Euler.27s_function */
/* calculate euler's totient function */
int phi (int n)
{
    int lim = isqrt (n), i = 0, k;
    int res = 1;

    /* factorize number */
    while (primes[i] <= lim) {
        k = 0;
        while ((n % primes[i]) == 0) {
            k++;
            n /= primes[i];
        }

        if (k > 0)
            res *= (primes[i] - 1) * power (k-1, primes[i]);
        i++;
    }
    
    if (n > 1)
        return res*(n-1);
    else
        return res;
}


void lookup_cache (int n, int* idx, unsigned int* sum)
{
    int delta = 1000000;
    int i;

    *sum = *idx = 0;

    for (i = 0; i < cache_size; i++) {
        if (cache[i][0] <= n && delta > (n-cache[i][0])) {
            *idx = cache[i][0];
            *sum = cache[i][1];
            delta = n-cache[i][0];
        }
    }
}


unsigned int solve (int n)
{
    unsigned int sum = 0;
    int i;

    lookup_cache (n, &i, &sum);

    while (i < n) {
        sum += phi (i+1);
        i++;
    }

    cache[cache_size][0] = n;
    cache[cache_size][1] = sum;
    cache_size++;

    return sum;
}



int main (int argc, char *argv[])
{
    int t, n, i;
    unsigned int sum = 0;

    make_primes (2000);

    scanf ("%d", &t);

    while (t--) {
        scanf ("%d", &n);
        printf ("%u\n", solve (n));
    }

    return 0;
}

int power (int n, int p)
{
    int res = 1;

    while (n--)
        res *= p;
    return res;
}

