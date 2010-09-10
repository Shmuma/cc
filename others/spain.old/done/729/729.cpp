#include <stdio.h>
#include <stdlib.h>


int buf[16];
int max_len;


int perm (int, int);


int main ()
{
    int n;
    int len, dist;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%d %d", &len, &dist);

        max_len = len;
        perm (len, dist);
        if (n)
            printf ("\n");
    }

    return 0;
}


int perm (int len, int dist)
{
    if (!len) {
        for (int i = 0; i < max_len; i++)
            printf ("%d", buf[i]);
        printf ("\n");
        return 0;
    }

    if (len > dist) {
        buf[max_len-len] = 0;
        perm (len-1, dist);
    }

    if (dist > 0) {
        buf[max_len-len] = 1;
        perm (len-1, dist-1);
    }
}
