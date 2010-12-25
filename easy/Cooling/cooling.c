#include <stdio.h>
#include <stdlib.h>

int weight[40];
int limit[40];
int max;

int places[40][40];
int len[40];
int fact_len[40];


void clear ()
{
    memset (weight, 0, sizeof (weight));
    memset (limit, 0, sizeof (limit));

    memset (places, 0, sizeof (places));
    memset (len, 0, sizeof (len));
    memset (fact_len, 0, sizeof (len));
    max = 0;
}


int comp (const void* a, const void* b)
{
    const int* aa = (const int*)a;
    const int* bb = (const int*)b;

    return *aa - *bb;
}


int solve ()
{
    int i, j, min_idx, res = 0;
    int min;

    /* build places table */
    for (i = 0; i < max; i++)
        for (j = max-1; j >= 0; j--) {
            if (weight[i] > limit[j])
                break;
            places[i][len[i]++] = j;
            fact_len[i]++;
        }

    for (i = 0; i < max; i++) {
        min = 100;
        min_idx = -1;

        /* find pie with min amount of available places */
        for (j = 0; j < max; j++)
            if (min > fact_len[j] && fact_len[j] > 0) {
                min = fact_len[j];
                min_idx = j;
            }

        if (min_idx == -1)
            break;

        /* for each available place check for amount of pies we will throw out if we'll take this place */
        for (j = 0; j < len[min_idx]; j++) {
            if (places[min_idx][j] < 0)
                continue;
        }
    }

    return res;
}


int main (int argc, char *argv[])
{
    int t, n, i, skip, v;

    scanf ("%d", &t);

    while (t--) {
        clear ();
        scanf ("%d", &n);

        for (i = 0; i < n; i++) {
            scanf ("%d", &v);
            weight[i] = v;
        }
        for (i = 0; i < n; i++) {
            scanf ("%d", &v);
            limit[i] = v;
        }

        qsort (weight, n, sizeof (weight[0]), comp);
        qsort (limit, n, sizeof (limit[0]), comp);
        max = n;

        printf ("%d\n", solve ());
    }

    return 0;
}
