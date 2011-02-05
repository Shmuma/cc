#include <stdio.h>
#include <stdlib.h>

int stones[10000][2];


int solve (int n);

int main (int argc, char *argv[])
{
    int t, n, i;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        for (i = 0; i < n; i++)
            scanf ("%d %d", &stones[i][0], &stones[i][1]);

        printf ("%d\n", solve (n));
    }
    return 0;
}

int eq (double a, double b)
{
    double d = a - b;
    if (d < 0)
        d = -d;
    return d < 1e-5;
}


int comp (const void* a, const void* b)
{
    const double* aa = (const double*)a;
    const double* bb = (const double*)b;

    if (eq (*aa, *bb))
        return 0;
    if (*aa < *bb)
        return -1;
    else
        return 1;
}


int solve (int n)
{
    static double alpha[10000];
    int i, j;
    int max_cnt = 0, cnt;
    

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j)
                alpha[j] = 100500*200;
            else
                if (stones[i][0] == stones[j][0])
                    alpha[j] = 100500;
                else
                    alpha[j] = ((double)(stones[j][1] - stones[i][1])) / (double)(stones[j][0] - stones[i][0]);
        }

        qsort (alpha, n, sizeof (alpha[0]), comp);

        cnt = 1;
        for (j = 1; j < n; j++) {
            if (eq (alpha[j-1], alpha[j]))
                cnt++;
            else {
                if (cnt > max_cnt)
                    max_cnt = cnt;
                cnt = 1;
            }
        }
    }

    return max_cnt+1;
}
