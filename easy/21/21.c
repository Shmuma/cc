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

    if (from == to) {
        if (sticks[from] < val)
            return 1;
        else
            return 0;
    }

    i = (from+to) >> 1;
    do {
        if (sticks[i] == val)
            break;
        if (sticks[i] > val)
            to = i-1;
        else
            from = i+1;
        i = (from+to) >> 1;
    }
    while (from < to);

    while (sticks[i] == val)
        i--;

    if (sticks[i] < val)
        return i+1-o_from;
    else
        return i-o_from;
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
/*             if (j == 0 || sticks[j] != sticks[j-1]) { */
                if (j+1 <= i-1)
                    res += search (j+1, i-1, sticks[i]-sticks[j]);
/*             } */
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