#include <stdio.h>
#include <stdlib.h>


int jobs[1001];
int left_jobs[1001];

int comp (const void* a, const void* b)
{
    const int* aa = (const int*)a;
    const int* bb = (const int*)b;

    return *aa - *bb;
}


int main (int argc, char *argv[])
{
    int t, n, m, i, left_count, j;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d %d", &n, &m);
        
        for (i = 0; i < m; i++)
            scanf ("%d", &jobs[i]);

        qsort (jobs, m, sizeof (int), comp);
        left_count = 0;
        j = 1;

        for (i = 0; i < m; i++, j++) {
            while (j < jobs[i])
                left_jobs[left_count++] = j++;
        }

        while (j <= n)
            left_jobs[left_count++] = j++;

        for (i = 0; i < left_count; i += 2)
            printf ("%d ", left_jobs[i]);
        printf ("\n");
        for (i = 1; i < left_count; i += 2)
            printf ("%d ", left_jobs[i]);
        printf ("\n");
    }
    return 0;
}
