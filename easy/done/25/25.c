#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int a, n, k, i;

    scanf ("%d %d %d", &a, &n, &k);
    n++;

    for (i = 0; i < k; i++) {
        if (i != 0)
            putchar (' ');
        printf ("%d", a % n);
        a /= n;
    }
    putchar ('\n');

    return 0;
}
