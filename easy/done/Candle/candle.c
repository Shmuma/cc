#include <stdio.h>
#include <stdlib.h>


int find_min (int* dig, int* count)
{
    int res = 1, i;

    *count = dig[1];

    for (i = 2; i < 10; i++)
        if (*count > dig[i]) {
            *count = dig[i];
            res = i;
        }

    /* zero has special case, so check it last */
    if (*count > dig[0]) {
        *count = dig[0];
        res = 0;
    }
    return res;
}

unsigned int make_res (int base, int cnt, int dig)
{
    int i;
    unsigned int res = base;

    while (cnt--) {
        res *= 10;
        res += dig;
    }
    return res;
}

unsigned int solve (int *dig)
{
    int min, cnt;

    min = find_min (dig, &cnt);

    if (!min)
        return make_res (1, cnt+1, 0);

    if (!cnt)
        return min;
    else
        return make_res (min, cnt, min);
}


int main (int argc, char *argv[])
{
    int t, i;
    int dig[10];
    
    scanf ("%d", &t);

    while (t--) {
        for (i = 0; i < 10; i++)
            scanf ("%d", &dig[i]);

        printf ("%u\n", solve (dig));
    }
    return 0;
}
