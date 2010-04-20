#include <stdio.h>
#include <stdlib.h>

unsigned long long dat[100][100][100];
unsigned long long res[100][100][100];


int main(int argc, char *argv[])
{
    int t;
    int x, y, z;
    int i, j, k;
    int a, b, c;

    scanf ("%d", &t);

    while (t--) {
        scanf ("%d %d %d", &x, &y, &z);
        for (i = 0; i < x; i++) {
            for (j = 0; j < y; j++) {
                for (k = 0; k < z; k++) {
                    scanf ("%llu", &dat[i][j][k]);
                }
            }
        }

        /* solve */
        for (i = 0; i < x; i++) {
            for (j = 0; j < y; j++) {
                for (k = 0; k < z; k++) {
                    a = dat[i][j][k];
                    if (k > 0)
                        a -= dat[i][j][k-1];

                    c = 0;
                    if (i > 0 && j > 0) {
                        c = dat[i-1][j-1][k];
                        if (k > 0)
                            c -= dat[i-1][j-1][k-1];
                    }
                    a -= c;

                    b = 0;
                    if (i > 0) {
                        b = dat[i-1][j][k];
                        if (k > 0)
                            b -= dat[i-1][j][k-1];
                        b -= c;
                    }
                    a -= b;

                    b = 0;
                    if (j > 0) {
                        b = dat[i][j-1][k];
                        if (k > 0)
                            b -= dat[i][j-1][k-1];
                        b -= c;
                    }
                    a -= b;
                    res[i][j][k] = a;
                }
            }
        }

        /* output */
        for (i = 0; i < x; i++) {
            for (j = 0; j < y; j++) {
                for (k = 0; k < z; k++) {
                    if (k != 0)
                        putchar (' ');
                    printf ("%llu", res[i][j][k]);
                }
                putchar ('\n');
            }
        }
    }

    return 0;
}
