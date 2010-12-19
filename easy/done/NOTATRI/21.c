#include <stdio.h>
#include <stdlib.h>


int sticks_count;
int sticks[2500];


int compare (const void *a, const void *b)
{
    const int *aa = a;
    const int *bb = b;

    return *bb - *aa;
}


/*
 * Search for index of first entry, less than val. Bound are inclusive
 */
int search (int from, int to, int val)
{
    int i = to+1;

    if (sticks[from] < val)
        return from;
    if (sticks[to] >= val)
        return to+1;

    while (from < to) {
        i = (from + to) >> 1;
        if (sticks[i] >= val)
            from = i+1;
        else
            to = i;
    }

    while (sticks[i] >= val && i <= to)
        i++;

    return i;
}


int solve ()
{
    int res = 0;
    int i, j, k;
    int *p;

    for (i = 0; i < sticks_count-2; i++) {
        for (j = i+1; j < sticks_count-1; j++) {
            k = search (j+1, sticks_count-1, sticks[i] - sticks[j]);
            res += sticks_count - k;
        }
    }

    return res;
}


int main(int argc, char *argv[])
{
    int i;

    while (1) {
        scanf ("%d", &sticks_count);
        
        if (!sticks_count)
            break;

        for (i = 0; i < sticks_count; i++)
            scanf ("%d", &sticks[i]);

        qsort (sticks, sticks_count, sizeof (sticks[0]), compare);
        printf ("%d\n", solve ());
    }

    return 0;
}
