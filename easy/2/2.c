#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(int argc, char *argv[])
{
    int n, p, i, res;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%d", &p);
        res = 0;
        while (p > 0) {
            p /= 5;
            res += p;
        }

        printf ("%d\n", res);
    }
    return 0;
}
