#include <stdio.h>
#include <stdlib.h>

int weight[40];
int limit[40];
int max;


int comp (const void* a, const void* b)
{
    const int* aa = (const int*)a;
    const int* bb = (const int*)b;

    return *aa - *bb;
}


int solve (int w_ofs, int l_ofs)
{
    int res = 0, val;
    if (w_ofs == max || l_ofs == max)
        return 0;

    if (weight[w_ofs] <= limit[l_ofs])
        res = 1+solve (w_ofs+1, l_ofs+1);

    val = solve (w_ofs, l_ofs+1);
    if (val > res)
        res = val;
    /* val = solve (w_ofs+1, l_ofs); */
    /* if (val > res) */
    /*     res = val; */
    /* val = solve (w_ofs+1, l_ofs+1); */
    /* if (val > res) */
    /*     res = val; */
    return res;
}


int main (int argc, char *argv[])
{
    int t, n, i, skip;

    scanf ("%d", &t);

    while (t--) {
        scanf ("%d", &n);

        for (i = 0; i < n; i++)
            scanf ("%d", &weight[i]);
        for (i = 0; i < n; i++)
            scanf ("%d", &limit[i]);

        qsort (weight, n, sizeof (int), comp);
        qsort (limit, n, sizeof (int), comp);
        max = n;

        printf ("%d\n", solve (0, 0));
    }

    return 0;
}
