#include <stdio.h>
#include <stdlib.h>


inline int abs (int n)
{
    return n > 0 ? n : -n;
}


int main(int argc, char *argv[])
{
    int n, max_lead, flag = 1, winner;
    int a, b, aa, bb;

    scanf ("%d", &n);
    aa = bb = 0;
    while (n--) {
        scanf ("%d %d", &a, &b);
        aa += a;
        bb += b;
        if (flag || abs (aa-bb) > max_lead) {
            winner = aa > bb ? 1 : 2;
            max_lead = aa > bb ? aa-bb : bb-aa;
        }
        flag = 0;
    }

    printf ("%d %d\n", winner, max_lead);

    return 0;
}
