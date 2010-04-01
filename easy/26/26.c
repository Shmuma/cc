#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(int argc, char *argv[])
{
    int t, p, s;
    float a1, a2;

    scanf ("%d", &t);

    while (t--) {
        scanf ("%d %d", &p, &s);

        a1 = (float)p / 12.0;
        a2 = sqrt ((float)s / 6.0);

        if (a2 < a1)
            a1 = a2;

        printf ("%.2f\n", a1*a1*a1);
    }

    return 0;
}
