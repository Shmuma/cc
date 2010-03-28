#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int primes [] = {
    2,      3,      5,      7,     11,     13,     17,     19,     23,     29, 
    31,     37,     41,     43,     47,     53,     59,     61,     67,     71, 
    73,     79,     83,     89,     97,    101,    103,    107,    109,    113, 
    127,    131,    137,    139,    149,    151,    157,    163,    167,    173, 
    179,    181,    191,    193,    197,    199,    211,    223,    227,    229, 
    233,    239,    241,    251,    257,    263,    269,    271,    277,    281, 
    283,    293,    307,    311,    313,    317,    331,    337,    347,    349, 
    353,    359,    367,    373,    379,    383,    389,    397,    401,    409, 
    419,    421,    431,    433,    439,    443,    449,    457,    461,    463, 
    467,    479,    487,    491,    499,    503,    509,    521,    523,    541, 
    547,    557,    563,    569,    571,    577,    587,    593,    599,    601, 
    607,    613,    617,    619,    631,    641,    643,    647,    653,    659, 
    661,    673,    677,    683,    691,    701,    709,    719,    727,    733, 
    739,    743,    751,    757,    761,    769,    773,    787,    797,    809, 
    811,    821,    823,    827,    829,    839,    853,    857,    859,    863, 
    877,    881,    883,    887,    907,    911,    919,    929,    937,    941, 
    947,    953,    967,    971,    977,    983,    991,    997,   1009,   1013, 
};


int len;
char buf[1001];
int remainders[1001];


void build_remainders (int n)
{
    int rem_count = 0;

    remainders[rem_count++] = 1;

    while (rem_count < len)
        remainders[rem_count++] = (10*remainders[rem_count-1]) % n;
}


int is_divisible (int n)
{
    int val, i;

    build_remainders (n);

    val = 0;

    for (i = 0; i < len; i++)
        val += buf[len-i-1] * remainders[i];

    return (val % n) == 0;
}


int is_equal (int n)
{
    int i;

    for (i = len-1; i >= 0; i--) {
        if ((n % 10) != buf[i])
            return 0;

        n /= 10;
    }

    return 1;
}



int is_prime ()
{
    int i;

    for (i = 0; i < sizeof (primes) / sizeof (primes[0]); i++) {
        if (is_divisible (primes[i]))
            if (is_equal (primes[i]))
                return 1;
            else
                return 0;
    }

    return 1;
}


int main (int argc, char *argv[])
{
    int i;
    
    scanf ("%s", buf);

    len = strlen (buf);
    for (i = 0; i < len; i++)
        buf[i] -= '0';
    
    if (is_prime ())
        puts ("PRIME");
    else
        puts ("COMPOSITE");

    return 0;
}
