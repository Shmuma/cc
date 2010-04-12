#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double solve (double p, double s)
{
    double a1, a2;
    double b1, b2;
    double v1, v2;

    a1 = (p - sqrt (p*p - 24 * s)) / 12.0;
    a2 = (sqrt (p*p-24*s) + p) / 12.0;

    b1 = (p-8*a1)/4;
    b2 = (p-8*a2)/4;
    
    v1 = a1*a1*b1;
    v2 = a2*a2*b2;

    if (v1 > v2)
        return v1;
    else
        return v2;
}



int main(int argc, char *argv[])
{
    int t, p, s;
    double vol;

    scanf ("%d", &t);

    while (t--) {
        scanf ("%d %d", &p, &s);

        vol = solve (p, s);
        printf ("%.2f\n", vol);
    }

    return 0;
}
