#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int t, n, i, p, val;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        
        val = 0;
        for (i = 1; i <= n; i++) {
            scanf ("%d", &p);
            val += p / i;
        }

        if (val % 2)
            puts ("ALICE");
        else
            puts ("BOB");
    }

    return 0;
}
