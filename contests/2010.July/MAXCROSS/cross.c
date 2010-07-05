#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;

char dat[1001][1001];

unsigned int buf[4][1001][1001];


int get_max (int i, int j)
{
    int t, res = buf[0][i][j];

    for (t = 1; t < 4; t++)
        if (res < buf[t][i][j])
            res = buf[t][i][j];

    return res;
}


void scan (int index, int i, int j, int di, int dj)
{
    int x = i, y = j, t = 0;

    while (x < n && y < n && dat[x][y]) {
        x += di;
        y += dj;
        t++;
    }

    x = i;
    y = j;
    
    while (x < n && y < n && dat[x][y]) {
        buf[index][x][y] = t;
        x += di;
        y += dj;
    }
}


void scan_neg (int index, int i, int j, int di, int dj)
{
    int x = i, y = j, t = 0;

    while (x >= 0 && y < n && dat[x][y]) {
        x += di;
        y += dj;
        t++;
    }

    x = i;
    y = j;
    
    while (x >= 0 && y < n && dat[x][y]) {
        buf[index][x][y] = t;
        x += di;
        y += dj;
    }
}



int main (int argc, char *argv[])
{
    int i, j, k;
    static char tmp[2000];
    int deltas[3][2] = {
        {0, 1},
        {1, 0},
        {1, 1}
    };

    scanf ("%d", &n);
    getchar ();

    for (i = 0; i < n; i++) {
        scanf ("%s", tmp);
        for (j = 0; j < n; j++)
            dat[i][j] = tmp[j] == 'X' ? 1 : 0;
        getchar ();
    }

    memset (buf, 0, sizeof (buf));

    /* three pases are positive */
    for (k = 0; k < 3; k++) {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (dat[i][j] && !buf[k][i][j])
                    scan (k, i, j, deltas[k][0], deltas[k][1]);
    }
    /* and one is negative */
    for (i = n-1; i >= 0; i--)
        for (j = 0; j < n; j++)
            if (dat[i][j] && !buf[3][i][j])
                scan_neg (3, i, j, -1, 1);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf ("%d", get_max (i, j));
            putchar (' ');
        }
        putchar ('\n');
    }

    return 0;
}
