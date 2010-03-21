#include <stdio.h>
#include <stdlib.h>


int next (int stalks, int leaves)
{
    if (leaves > stalks)
        return -1;
    
    stalks -= leaves;
    return stalks << 1;
}


int main(int argc, char *argv[])
{
    int n, k, t;
    int res;
    int stalks;

    scanf ("%d", &n);
    
    while (n--) {
        scanf ("%d", &k);
        stalks = 1;
        res = 1;

        while (k--) {
            scanf ("%d", &t);
            /* printf ("%lld (%d) -> ", stalks, t); */
            stalks = next (stalks, t);
            /* printf ("%lld\n", stalks); */
            if (stalks < 0)
                break;
        }

        if (stalks != 0)
            res = 0;

        puts (res ? "Yes" : "No");
    }
    return 0;
}
