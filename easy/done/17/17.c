#include <stdio.h>
#include <stdlib.h>


int count;
int perm[1001];
int c_count;
int cycles[1001][1001];


int next ()
{
    int i;

    for (i = 0; i < count; i++)
        if (perm[i] >= 0)
            return i;
    return -1;
}


void find_cycles ()
{
    int t, size, k;

    while ((t = next ()) >= 0) {
        size = 0;
        while (perm[t] >= 0) {
            cycles[c_count][size++] = t;
            k = perm[t];
            perm[t] = -1;
            t = k;
        }
        cycles[c_count][size] = -1;
        c_count++;
    }
}


int main(int argc, char *argv[])
{
    int i, j;

    scanf ("%d", &count);

    for (i = 0; i < count; i++) {
        scanf ("%d", perm+i);
        perm[i]--;
    }

    find_cycles ();

    printf ("%d\n", c_count);
    for (i = 0; i < c_count; i++) {
        j = 0;
        while (cycles[i][j] >= 0)
            printf ("%d ", cycles[i][j++]+1);
        printf ("%d\n", cycles[i][0]+1);
    }

    return 0;
}
