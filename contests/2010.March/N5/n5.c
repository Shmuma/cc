#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int size;
int data[100001][2];
int d[100001];
int dd[100001];
unsigned char flags[100001];

int solve ();
void simplify ();

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
        simplify ();
        printf ("%d\n", solve ());
    }

    return 0;
}


int find_pos (int n)
{
    int i;
    for (i = 0; i < size; i++)
        if (d[i] == n)
            return i;
}


int needs_moving (int n)
{
    int i;

    for (i = n+1; i < size; i++)
        if (d[i] < d[n])
            return 1;

    return 0;
}


int mark_to_move (int n)
{
    int i, k;

    memset (flags, 0, sizeof (unsigned char) * size);
    flags[n] = 1;

    k = d[n]+1;

    for (i = n+1; i < size; i++)
        if (d[i] == k) {
            flags[i] = 1;
            k++;
        }

    return k-d[n];
}


void move ()
{
    int i, j = 0;

    for (i = 0; i < size; i++)
        if (!flags[i])
            dd[j++] = d[i];

    for (i = 0; i < size; i++)
        if (flags[i])
            dd[j++] = d[i];
    memcpy (d, dd, sizeof (unsigned char) * size);
}


void simplify ()
{
    int i, idx;

    for (i = 0; i < size; i++)
        data[i][1] = i;

    qsort (data, size, sizeof (data[0]), compare);

    for (i = 0; i < size; i++)
        dd[data[i][1]] = i;
    idx = 1;
    data[0][0] = dd[0];
    for (i = 1; i < size; i++)
        if (dd[i] != dd[i-1]+1)
            data[idx++][0] = dd[i];
    size = idx;

    for (i = 0; i < size; i++)
        data[i][1] = i;

    qsort (data, size, sizeof (data[0]), compare);

    for (i = 0; i < size; i++)
        d[data[i][1]] = i;
}


int solve ()
{
    int i, n, inc, res = 0, idx;
    
    n = 0; 
    while (n < size) {
        idx = find_pos (n);
        if (needs_moving (idx)) {
            inc = mark_to_move (idx);
            move ();
            res++;
        }
        else
            inc = 1;

        n += inc;
    }

    return res;
}
