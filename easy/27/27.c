#include <stdio.h>
#include <stdlib.h>

unsigned long long dat[100][100][100];
unsigned long long res[100][100][100];


int main(int argc, char *argv[])
{
    int t;
    int x, y, z;
    int i, j, k;
    int a, b;

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
                    unsigned long long v = dat[i][j][k];

                    if (k > 0)
                        v -= dat[i][j][k-1];
                    for (a = 0; a <= i; a++)
                        for (b = 0; b <= j; b++)
                            if (a != i || b != j)
                                v -= res[a][b][k];
                    res[i][j][k] = v;
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
