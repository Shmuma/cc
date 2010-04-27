#include <stdio.h>
#include <stdlib.h>


int sticks_count;
int sticks[2000];


int compare (const void *a, const void *b)
{
    const int *aa = a;
    const int *bb = b;

    return *aa - *bb;
}


/*
 * Search for index of first entry, greater or equal val. Bound are inclusive
 */
int search (int from, int to, int val)
{
    int idx = to;

    while (from < to) {
        idx = (from + to) >> 1;

        if (sticks[idx] > val)
            to = idx-1;
        else
            from = idx+1;
    }

    if (sticks[idx] >= val)
        return idx;
    else
        return idx+1;
}


int solve ()
{
    int res = 0;
    int i, j, k;
    int *p;
    
    i = sticks_count-1;

    while (i > 0) {
        j = i-1;

        while (j > 0) {
            res += search (0, j-1, sticks[i]-sticks[j]);
            j--;
        }
        i--;
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
