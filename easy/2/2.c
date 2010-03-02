#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int n, p, i, res;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%d", &p);
        res = 0;
        for (i = 1; i <= p; i++)
            if (i % 10 == 0)
                res++;

        printf ("%d\n", res);
    }
    return 0;
}
