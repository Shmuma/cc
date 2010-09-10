#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int w, h, t;

// time, x, y
char hist[102][102][102];


void solve ();

void dump ()
{
    int i, x, y;

    for (i = 0; i < t; i++) {
        printf ("Time %d:\n", i);

        for (x = 1; x <= w; x++) {
            for (y = 1; y <= h; y++)
                printf ("%d", hist[i][x][y]);
            printf ("\n");
        }

        printf ("\n");
   }
}



int main ()
{
    int n, count = 1;

    while (1) {
        scanf ("%d %d %d", &w, &h, &t);

        if (!w)
            break;

        memset (&hist, 0, sizeof (hist));

        int tt, l, top, r, b;
        
        scanf ("%d", &n);

        while (n--) {
            scanf ("%d %d %d %d %d", &tt, &l, &top, &r, &b);
            for (int i = l; i <= r; i++)
                for (int j = top; j <= b; j++)
                    hist[tt-1][i][j] = 1; // 1 means empty
        }

        printf ("Robbery #%d:\n", count++);
        solve ();

        printf ("\n");
    }

    return 0;
}



void solve ()
{
    int i, x, y;

    //    dump ();

    for (i = t-1; i >= 0; i--) {
        for (x = 1; x <= w; x++)
            for (y = 1; y <= h; y++) {
                if (!hist[i][x][y]) {
                    if (i == t-1)
                        hist[i][x][y] = 2; // 2 means there may have been robber
                    else {
                        if (hist[i+1][x][y]     == 2 || 
                            hist[i+1][x+1][y]   == 2 || hist[i+1][x][y+1]   == 2   || 
                            //                            hist[i+1][x+1][y+1] == 2 || hist[i+1][x-1][y-1] == 2 || 
                            hist[i+1][x-1][y]   == 2 || hist[i+1][x][y-1]   == 2 )
                            //                            hist[i+1][x+1][y-1] == 2 || hist[i+1][x-1][y+1] == 2) 
                            hist[i][x][y] = 2;
                    }
                }
            }
    }

    //    dump ();

    for (i = 0; i < t; i++) {
        for (x = 1; x <= w; x++)
            for (y = 1; y <= h; y++) {
                if (hist[i][x][y] == 2) {
                    if (i == 0)
                        hist[i][x][y] = 3; // 3 means there have beed robber
                    else {
                        if (hist[i-1][x][y]     == 3 || 
                            hist[i-1][x+1][y]   == 3 || hist[i-1][x][y+1]   == 3   || 
                            //                            hist[i-1][x+1][y+1] == 3 || hist[i-1][x-1][y-1] == 3 || 
                            hist[i-1][x-1][y]   == 3 || hist[i-1][x][y-1]   == 3 )
                            //                            hist[i-1][x+1][y-1] == 3 || hist[i-1][x-1][y+1] == 3) 
                            hist[i][x][y] = 3;
                    }
                }
            }
    }

    //    dump ();

    // check for escape
    bool pres, sing;
    int xx, yy;

    for (i = 0; i < t; i++) {
        pres = false;

        for (x = 1; x <= w; x++)
            for (y = 1; y <= h; y++)
                pres |= hist[i][x][y] == 3;

        if (!pres) {
            printf ("The robber has escaped.\n");
            return;
        }
    }

    pres = false;

    for (i = 0; i < t; i++) {
        sing = true;
        xx = -1;

        for (x = 1; x <= w && sing; x++)
            for (y = 1; y <= h && sing; y++) {
                if (hist[i][x][y] == 3) {
                    //                    printf ("%d,%d,%d == 3\n", i, x, y);
                    if (xx < 0) {
                        xx = x;
                        yy = y;
                    }
                    else
                        sing = false;
                }
            }

        if (sing) {
            printf ("Time step %d: The robber has been at %d,%d.\n", i+1, xx, yy);
            pres = true;
        }
    }

    if (!pres) 
        printf ("Nothing known.\n");
}
