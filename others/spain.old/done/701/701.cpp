#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main ()
{
    unsigned int n;
    char buf[100];

    while (1) {
        scanf ("%u", &n);
        if (feof (stdin))
            break;

        sprintf (buf, "%u", n);

        double d1, d2, l2;

        d1 = log10 (n);
        d2 = log10 (n+1);
        l2 = log10 (2);

        unsigned int k = strlen (buf)+1;
        double t1, t2;

        while (1) {
            t1 = (d1+k) / l2;
            t2 = (d2+k) / l2;
            //            printf ("%d: %.5lf, %.5lf\n", k, t1, t2);
            if (fabs (ceil (t1)-floor (t2)) < 1e-7) {
                printf ("%u\n", (unsigned int)ceil (t1));
                break;
            }
            k++;
        }
    }

    return 0;
}
