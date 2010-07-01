#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;

char dat[1002][1002];

unsigned int buf[8][1002][1002];

void scan (int index,
           int min_i, int max_i, int step_i,
           int min_j, int max_j, int step_j,
           int delta_i, int delta_j)
{
    int i, j;

    i = min_i;

    while (i != max_i+step_i) {
        j = min_j;

        while (j != max_j+step_j) {
            if (!dat[i][j])
                buf[index][i][j] = 0;
            else
                buf[index][i][j] = 1 + buf[index][i + delta_i][j + delta_j];

            j += step_j;
        }

        i += step_i;
    }
}


int get_max (int i, int j)
{
    int t, res = buf[0][i][j];

    for (t = 1; t < 8; t++)
        if (res < buf[t][i][j])
            res = buf[t][i][j];

    return res;
}


int main (int argc, char *argv[])
{
    int i, j;

    scanf ("%d", &n);
    getchar ();

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            dat[i][j] = getchar () == 'X' ? 1 : 0;
        getchar ();
    }

    memset (buf, 0, sizeof (buf));

    scan (0, 1, n,  1, 1, n,  1, -1,  0);
    scan (1, n, 1, -1, 1, n,  1,  1,  0);
    scan (2, 1, n,  1, 1, n,  1,  0, -1);
    scan (3, 1, n,  1, n, 1, -1,  0,  1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (j > 1)
                putchar (' ');
            printf ("%d", get_max (i, j));
        }
        putchar ('\n');
    }

    return 0;
}
