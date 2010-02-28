#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int n, k, res = 0, val;

    scanf ("%d %d", &n, &k);

    while (n--) {
        scanf ("%d", &val);
        if (val % k == 0)
            res++;
    }

    printf ("%d\n", res);

    return 0;
}
