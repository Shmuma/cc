#include <stdio.h>
#include <stdlib.h>


int main ()
{
    int n, c = 0;
    int d[20][3];
    int s;

    while (1) {
        scanf ("%d", &n);
        if (!n)
            break;

        s = 0;
        for (int i = 0; i < n; i++) {
            scanf ("%d %d %d", &d[i][0], &d[i][1], &d[i][2]);
            if (d[i][0] > s)
                s = d[i][0];
        }
        
        bool found = false;
        int res;

        for (int y = s; y < 10000; y++) {
            found = true;
            for (int i = 0; i < n; i++) {
                if ((y - d[i][0]) % (d[i][2] - d[i][1]) + d[i][0] != d[i][0]) {
                    found = false;
                    break;
                }
            }

            if (found) {
                res = y;
                break;
            }
        }

        printf ("Case #%d:\n", ++c);
        if (found)
            printf ("The actual year is %d.\n", res);
        else
            printf ("Unknown bugs detected.\n");
        printf ("\n");
    }

    return 0;
}
