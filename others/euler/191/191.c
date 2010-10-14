/* Answer: 1918080160 */

#include <stdio.h>
#include <stdlib.h>


unsigned long long cache[30][3][2];

unsigned long long generate (int n, int abs, int late);


unsigned long long lookup (int n, int abs, int late)
{
    unsigned long long t;

    if (cache[n][abs][late])
        t = cache[n][abs][late];
    else {
        t = generate (n, abs, late);
        printf ("G (n = %d, abs = %d, late = %d) => %llu\n", n, abs, late, t);
        cache[n][abs][late] = t;
    }
    return t;
}


unsigned long long generate (int n, int abs, int late)
{
    unsigned long long res = 0, t;

    if (n == 0)
        return 0;

    if (n == 1)
        if (!late)
            if (abs < 2)
                return 3;
            else
                return 2;
        else
            if (abs < 2)
                return 2;
            else
                return 1;

    /* amount of variants if we are on time this day */
    res += lookup (n-1, 0, late);

    if (abs < 2)
        res += lookup (n-1, abs+1, late);

    if (!late)
        res += lookup (n-1, 0, 1);

    return res;
}


#define REL 1

int main(int argc, char *argv[])
{
    int n = atoi (argv[1]);
    unsigned long long count;
    
    printf ("N = %d\n", n);
#if REL
    count = generate (n, 0, 0);
    printf ("G (n = %d, abs = 0, late = 0) => %llu (Final)\n", n, count);
#else
    count = generate (2, 1, 0);
    printf ("G (n = 2, abs = 1, late = 0) => %llu (Final)\n", count);
#endif
    printf ("Strings = %llu\n", count);
    return 0;
}
