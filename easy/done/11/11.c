#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int points_count;
int points[100001][2];


int compare (const void *a, const void *b)
{
    const int *aa = (const int *)a;
    const int *bb = (const int *)b;
    
    if (aa[0] == bb[0])
        return bb[1] - aa[1];
    else
        return aa[0] - bb[0];
}


int main(int argc, char *argv[])
{
    int n, i, v1, v2;
    double res;

    scanf ("%d", &n);
    while (n--) {
        scanf ("%d", &points_count);
        for (i = 0; i < points_count; i++)
            scanf ("%d %d", &points[i][0], &points[i][1]);
        qsort (points, points_count, sizeof (points[0]), compare);

        res = 0;

        for (i = 0; i < points_count-1; i++) {
            v1 = points[i+1][0] - points[i][0];
            v2 = points[i+1][1] - points[i][1];
            res += sqrt (v1*v1 + v2*v2);
        }

        printf ("%.2lf\n", res);
    }
    
    return 0;
}
