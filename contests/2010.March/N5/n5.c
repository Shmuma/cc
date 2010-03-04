#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* http://www.jerrydallal.com/random/random_permutation.htm */


int size;
int data[100001][2];
int d[100001];
int dd[100001];
int *p = d;
unsigned char flags[100001];

int solve ();
int simplify ();

int compare (const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}


int main(int argc, char *argv[])
{
    int n, i;

    scanf ("%d", &n);
    while (n--) {
        scanf ("%d", &size);
        
        for (i = 0; i < size; i++)
            scanf ("%d", &data[i][0]);
        printf ("%d\n", solve ());
    }

    return 0;
}


int find_pos (int n)
{
    int i;
    for (i = 0; i < size; i++)
        if (p[i] == n)
            return i;
}


int needs_moving (int n)
{
    int i;

    for (i = n+1; i < size; i++)
        if (p[i] < p[n])
            return 1;

    return 0;
}


int mark_to_move (int n, int *flagged)
{
    int i, k;

    *flagged = 1;
    memset (flags, 0, sizeof (unsigned char) * size);
    flags[n] = 1;

    k = p[n]+1;

    for (i = n+1; i < size; i++)
        if (p[i] == k) {
            flags[i] = 1;
            (*flagged)++;
            k++;
        }

    return k - p[n];
}


void move (int flagged)
{
    int i, j = 0, f = size - flagged;
    int *pp;

    if (p == d)
        pp = dd;
    else
        pp = d;

    for (i = 0; i < size; i++)
        if (!flags[i])
            pp[j++] = p[i];
        else
            pp[f++] = p[i];           

    p = pp;
}


/* Input is in data array, output is in d array */
void order ()
{
    int i;

    for (i = 0; i < size; i++)
        data[i][1] = i;

    qsort (data, size, sizeof (data[0]), compare);

    for (i = 0; i < size; i++)
        d[data[i][1]] = i;
}


int simplify ()
{
    int i, idx, inc = 0;

    order ();

    /* pack inceasing elements */
    idx = 1;
    data[0][0] = d[0];
    for (i = 1; i < size; i++)
        if (d[i] != d[i-1]+1)
            data[idx++][0] = d[i];
    size = idx;

    order ();

    /* pack decreasing elements */
    idx = 1;
    inc = 0;
    data[0][0] = d[0];
    for (i = 1; i < size; i++)
        if (d[i] != d[i-1]-1)
            data[idx++][0] = d[i];
        else
            inc++;
    size = idx;

    return inc;
}


int solve ()
{
    int i, n, inc, res = 0, idx, flagged;

    res += simplify ();
    order ();
    
    n = 0; 
    while (n < size) {
        idx = find_pos (n);
        if (needs_moving (idx)) {
            inc = mark_to_move (idx, &flagged);
            move (flagged);
            res++;
        }
        else
            inc = 1;

        n += inc;
    }

    return res;
}
