#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DEBUG 0


int next (int stalks, int leaves)
{
    if (leaves > stalks)
        return -1;
    
    stalks -= leaves;
    return stalks << 1;
}


int getnum ()
{
    int c;
    int n = 0;

    do {
        c = getchar_unlocked ();
    }
    while (c < '0' || c > '9');

    do {
        n = (n << 3) + (n << 1) + c-'0';
        c = getchar_unlocked ();
    }
    while (c >= '0' && c <= '9');

    return n;
}


int main(int argc, char *argv[])
{
    int n, k, t;
    int res;
    int stalks;

    n = getnum ();
    
    while (n--) {
        k = getnum ();
        stalks = 1;
        res = 1;

        while (k--) {
            t = getnum ();
#if DEBUG
            printf ("%d (%d) -> ", stalks, t);
#endif
            stalks = next (stalks, t);
#if DEBUG
            printf ("%d\n", stalks);
#endif
            if (stalks < 0)
                break;
        }

        if (stalks != 0)
            res = 0;

        puts (res ? "Yes" : "No");
    }
    return 0;
}
