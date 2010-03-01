#include <stdio.h>
#include <stdlib.h>



int compare (const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}


int main(int argc, char *argv[])
{
    int n, i;
    int *data;

    scanf ("%d", &n);
    data = (int*)malloc (n * sizeof (int));

    for (i = 0; i < n; i++)
        scanf ("%d", data+i);
    qsort (data, n, sizeof (int), compare);
    for (i = 0; i < n; i++)
        printf ("%d\n", data[i]);

    return 0;
}
