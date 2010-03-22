int primes_count;
int primes[50000];


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


void find_primes (int max)
{
    int i, j, flag, lim;

    primes_count = 0;
    primes[primes_count++] = 2;
    
    for (i = 3; i <= max; i += 2) {
        /* check for prime */
        flag = 1;
        lim = isqrt (i);
        for (j = 0; j < primes_count && primes[j] <= lim && flag; j++)
            if (i % primes[j] == 0)
                flag = 0;
        if (flag)
            primes[primes_count++] = i;
    }
}
