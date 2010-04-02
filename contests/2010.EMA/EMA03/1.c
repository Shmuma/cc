#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int n;
    unsigned long long v, res;

    while (1) {
        if (scanf ("%d", &n) <= 0)
            break;

        res = 0;
        v = n;
        res += v * 6;
        res += v * 4;
        res += v * 3;
        printf ("%d\n", (int)res / 12);
    }
    return 0;
}
