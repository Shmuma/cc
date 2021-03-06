#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int primes[150000];
int primes_count;

/* Integer square root by Halleck's method, with Legalize's speedup */
unsigned long long isqrt (x) unsigned long long x;{
  unsigned long long   squaredbit, remainder, root;

   if (x<1) return 0;
  
   /* Load the binary constant 01 00 00 ... 00, where the number
    * of zero bits to the right of the single one bit
    * is even, and the one bit is as far left as is consistant
    * with that condition.)
    */
   squaredbit  = (long) ((((unsigned long) ~0L) >> 1) & 
                        ~(((unsigned long) ~0L) >> 2));
   /* This portable load replaces the loop that used to be 
    * here, and was donated by  legalize@xmission.com 
    */

   /* Form bits of the answer. */
   remainder = x;  root = 0;
   while (squaredbit > 0) {
     if (remainder >= (squaredbit | root)) {
         remainder -= (squaredbit | root);
         root >>= 1; root |= squaredbit;
     } else {
         root >>= 1;
     }
     squaredbit >>= 2; 
   }

   return root;
}


void primes_table ()
{
    int n = 5, i, prime;
    div_t q;
    
    primes[0] = 2;
    primes[1] = 3;
    primes_count = 2;

    while (primes_count < sizeof (primes) / sizeof (primes[0])) {
        prime = 1;

        for (i = 1; i < primes_count; i++) {
            q = div (n, primes[i]);
            if (!q.rem) {
                prime = 0;
                break;
            }

            if (q.quot < primes[i])
                break;
        }

        if (prime)
            primes[primes_count++] = n;
        n += 2;
    }
}


int is_prime (unsigned long long n)
{
    int i;
    ldiv_t q;

    if (n == 2)
        return 1;

    if (n % 2 == 0 || n == 1)
        return 0;

    for (i = 0; i < primes_count; i++) {
        q = ldiv (n, primes[i]);
        if (q.quot < primes[i])
            return 1;
        if (!q.rem)
            return 0;
    }

    return 1;
}


inline int abs (int n)
{
    return (n > 0) ? n : -n;
}


inline int max (int a, int b)
{
    return (a > b) ? a : b;
}


inline int num2cycle (unsigned long long n)
{
    return (isqrt (n) + 1) >> 1;
}


unsigned long long coord2num (int x, int y)
{
    unsigned long long res = 0;
    int cycle = max (abs (x), abs (y));

    if (!cycle)
        return 0;

    res = cycle*2-1;
    res *= res;

    if (x == cycle && y != -cycle)
        return res + (y + cycle - 1);
    res += cycle * 2 - 1;
    if (y == cycle)
        return res + (cycle - x);
    res += cycle * 2;
    if (x == -cycle)
        return res + (cycle - y);
    res += cycle * 2;
    return res + (x + cycle);
}


void num2coord (unsigned long long n, int *x, int *y)
{
    int cycle = num2cycle (n);
    unsigned long long base, delta;

    base = cycle*2-1;
    base *= base;
    
    delta = n - base;

    if (delta <= cycle*2 - 1) {
        *x = cycle;
        *y = -cycle + delta + 1;
        return;
    }

    base += cycle*2 - 1;
    delta = n - base;

    if (delta <= cycle*2) {
        *x = cycle - delta;
        *y = cycle;
        return;
    }

    base += cycle*2;
    delta = n - base;

    if (delta <= cycle*2) {
        *x = -cycle;
        *y = cycle - delta;
        return;
    }

    base += cycle*2;
    delta = n - base;
    *x = -cycle + delta;
    *y = -cycle;
}



int check_distance (unsigned long n, int dist)
{
    int x, y, t;
    unsigned long long p;
    int *deltas;

    num2coord (n, &x, &y);

    for (t = 0; t < dist; t++) {
        p = coord2num (x - dist + t, y - t);
        if (is_prime (p))
            return 1;
        p = coord2num (x - dist + t, y + t);
        if (is_prime (p))
            return 1;
        p = coord2num (x + dist - t, y - t);
        if (is_prime (p))
            return 1;
        p = coord2num (x + dist - t, y + t);
        if (is_prime (p))
            return 1;
    }

    return 0;
}


int prime_distance (unsigned long long n)
{
    int i;

    /* the only even prime: 2 */
    if (n == 1)
        return 1;

    if ((n % 2) == 0)
        i = 1;
    else
        i = 2;

    while (1) {
        if (check_distance (n, i))
            return i;
        i += 2;
    }

    return 0;
}


int main(int argc, char *argv[])
{
    int t;
    int x, y;
    unsigned long long n;
    int xx, yy, i, m = 0, v;

    primes_table ();

#if 0
    for (i = 0; i < 10000000; i++) {
        v = prime_distance (i);
        if (v > m) {
            m = v;
            printf ("%d -> %d distance\n", i, m);
        }
    }
    return 0;
#endif

    scanf ("%d", &t);

    while (t--) {
        scanf ("%d %d", &x, &y);
        n = coord2num (x, y);

        //        printf ("%llu\n", n);

        if (is_prime (n))
            printf ("0\n");
        else
            printf ("%d\n", prime_distance (n));
    }

    return 0;
}
