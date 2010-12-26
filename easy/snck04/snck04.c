#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[])
{
    int t, n;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        printf ("%d\n", solve (n));
    }
    return 0;
}
