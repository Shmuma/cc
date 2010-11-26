#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    unsigned long long v, i;

    for (i = 0; ; i++) {
        v = i*i;
        if (v > 99999999999999ULL)
            break;
        printf ("%llu\n", v);
    }

    return 0;
}
