#include <stdio.h>
#include <stdlib.h>


int check (int n, int *perm)
{
    int i;
    
    for (i = 0; i < n; i++)
        if (perm[perm[i]-1] != i+1)
            return 0;
    return 1;
}



int main(int argc, char *argv[])
{
    int n, i;
    int *perm;

    while (1) {
        scanf ("%d", &n);
        if (!n)
            break;

        perm = (int*)malloc (sizeof (int) * n);
        for (i = 0; i < n; i++)
            scanf ("%d", &perm[i]);
        if (check (n, perm))
            printf ("ambigous\n");
        else
            printf ("not ambigous\n");
    }

    return 0;
}
