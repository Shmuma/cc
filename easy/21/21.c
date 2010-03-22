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
 * Search for index (relative to from index) of last entry
 * which is less than val.
 */
int search (int from, int to, int val)
{
    int i, o_from = from;

    do {
        i = (from+to) >> 1;
        if (sticks[i] == val)
            break;
        if (sticks[i] > val)
            to = i-1;
        else
            from = i+1;
    }
    while (from < to);

    return i+1-o_from;
}


int solve ()
{
    int res = 0;
    int i, j, k;
    int *p;
    
    i = sticks_count-1;

    while (i >= 0) {
        j = 0;

        while (j < i) {
            res += search (j+1, i-1, sticks[i]-sticks[j]);
            j++;
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
