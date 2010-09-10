#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int field[77][77];
int w, h;
int sol[77][77];
int t_x, t_y;
int best;

int solve (int x1, int y1, int x2, int y2);
void print ();


int main ()
{
    int b = 1;

    while (1) {
        scanf ("%d %d", &w, &h);
        
        if (!w && !h)
            break;

        while (getchar () != '\n');
        
        memset (field, 0, sizeof (field));

        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                char c = getchar ();

                field[j][i] = c == 'X' ? 1 : 0;
            }

            while (getchar () != '\n');
        }
            
        int x1, y1, x2, y2;
        int p = 1, len;

        printf ("Board #%d:\n", b++);

        while (1) {
            scanf ("%d %d %d %d", &x1, &y1, &x2, &y2);

            if (!x1 && !y1 && !x2 && !y2)
                break;

            printf ("Pair %d: ", p++);

            len = solve (x1, y1, x2, y2);
            if (len > 0)
                printf ("%d segments.\n", len);
            else
                printf ("Impossible.\n");
        }
    }

    return 0;
}


int lev_add (int prev, int next)
{
    if (prev == next)
        return 0;
    else
        return 1;
}



void do_solve (int x, int y, int lev, int dir)
{
    //    printf ("%d %d\n", x, y);
    
//     if (lev > w || lev > h || lev > best)
//         return;

    //    print ();

    if (x == t_x && y == t_y)
        if (best > lev)
            best = lev;

    if (field[x][y] || sol[x][y])
        return;

    sol[x][y] = 1;

    // trying to estimate direction to target
    if (x - t_x > 0) {
        if (x > 0 && dir != 3)
            do_solve (x-1, y, lev + lev_add (dir, 1), 1);
        if (x <= w && dir != 1)
            do_solve (x+1, y, lev + lev_add (dir, 3), 3);
    }
    else {
        if (x <= w && dir != 1)
            do_solve (x+1, y, lev + lev_add (dir, 3), 3);
        if (x > 0 && dir != 3)
            do_solve (x-1, y, lev + lev_add (dir, 1), 1);
    }

    if (y - t_y > 0) {
        if (y > 0 && dir != 4)
            do_solve (x, y-1, lev + lev_add (dir, 2), 2);
        if (y <= h && dir != 2)
            do_solve (x, y+1, lev + lev_add (dir, 4), 4);
    }
    else {
        if (y <= h && dir != 2)
            do_solve (x, y+1, lev + lev_add (dir, 4), 4);
        if (y > 0 && dir != 4)
            do_solve (x, y-1, lev + lev_add (dir, 2), 2);
    }

    sol[x][y] = 0;
}



int solve (int x1, int y1, int x2, int y2)
{
    t_x = x2;
    t_y = y2;
    best = 10000000;

    if (x2-1 == x1 && y2 == y1)
        best = 1;
    if (x2 == x1 && y2-1 == y1)
        best = 1;
    if (x2+1 == x1 && y2 == y1)
        best = 1;
    if (x2 == x1 && y2+1 == y1)
        best = 1;

    memset (sol, 0, sizeof (sol));

    if (x1 > 0 && !field[x1-1][y1])
        do_solve (x1-1, y1, 1, 1);
    if (y1 > 0 && !field[x1][y1-1])
        do_solve (x1, y1-1, 1, 2);
    if (x1 <= w && !field[x1+1][y1])
        do_solve (x1+1, y1, 1, 3);
    if (y1 <= h && !field[x1][y1+1])
        do_solve (x1, y1+1, 1, 4);

    return best == 10000000 ? 0 : best;
}


void print ()
{
    printf ("\n");
    for (int i = 0; i <= h+1; i++) {
        for (int j = 0; j <= w+1; j++)
            if (field[j][i])
                printf (" ");
            else
                printf ("%d", sol[j][i]);
        printf ("\n");
    }
            
}
