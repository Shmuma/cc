#include <stdio.h>
#include <stdlib.h>


int solve (int n)
{
    int i = 0, t = n;

    while (n) {
        n >>= 1;
        i++;
    }

    return 1 << (i-1);
}


int main(int argc, char *argv[])
{
    int n, p;

    scanf ("%d", &n);
    while (n--) {
        scanf ("%d", &p);
        printf ("%d\n", solve (p));
    }

    return 0;
}
