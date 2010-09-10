#include <stdio.h>
#include <stdlib.h>


unsigned long long t[] = {
1,1,2,7,18,60,196,704,2500,9189,33896,126759,
 476270,1802312,6849777,26152418,100203194,
 385221143ULL,1485200848ULL,5741256764ULL,22245940545ULL,
 86383382827ULL,336093325058ULL,1309998125640ULL
};



int main ()
{
    int n;

    while (scanf ("%d", &n) == 1) {
        if (n > 24)
            printf ("0\n");
        else
            printf ("%llu\n", t[n-1]);
    }        

    return 0;
}
