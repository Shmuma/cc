#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <deque>

using namespace std;


int field[177][177];
int w, h;
int sol[177][177];

int solve (int x1, int y1, int x2, int y2);
void print (int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1);


struct try_t {
    int x, y;
    int parts;
    int dir;
};


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
                printf ("impossible.\n");
        }
        printf ("\n");
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


try_t make_try (int x, int y, int parts, int dir)
{
    try_t t;

    t.x = x;
    t.y = y;
    t.parts = parts;
    t.dir = dir;

    return t;
}




int solve (int x1, int y1, int x2, int y2)
{
    deque<try_t> queue;
    int best = -1;

    memset (sol, 0, sizeof (sol));

    queue.push_back (make_try (x1-1, y1, 1, 1));
    queue.push_back (make_try (x1+1, y1, 1, 2));
    queue.push_back (make_try (x1, y1-1, 1, 3));
    queue.push_back (make_try (x1, y1+1, 1, 4));

    while (queue.size ()) {
        try_t t;
        
        t = queue.front ();
        queue.pop_front ();

        if (t.x < 0 || t.y < 0)
            continue;
        if (t.x > w+1 || t.y > h+1)
            continue;

//         printf ("%d: %d\n", best, field[x][y]);

        if (t.x == x2 && t.y == y2) {
            //            printf ("Reached\n");
            if (t.parts < best || best < 0)
                best = t.parts;
        }

        if (field[t.x][t.y])
            continue;
        if (sol[t.x][t.y] > 0 && sol[t.x][t.y] <= t.parts)
            continue;
        sol[t.x][t.y] = t.parts;

        //        print (x1, y1, x2, y2);

        // add all neighbours
        if (t.x > 0)
            queue.push_back (make_try (t.x-1, t.y, t.parts + lev_add (t.dir, 1), 1));
        if (t.x <= w)
            queue.push_back (make_try (t.x+1, t.y, t.parts + lev_add (t.dir, 2), 2));

        if (t.y > 0)
            queue.push_back (make_try (t.x, t.y-1, t.parts + lev_add (t.dir, 3), 3));
        if (t.y <= h)
            queue.push_back (make_try (t.x, t.y+1, t.parts + lev_add (t.dir, 4), 4));
    }

    return best;
}


void print (int x1, int y1, int x2, int y2)
{
    printf ("\n");
    for (int i = 0; i <= h+1; i++) {
        for (int j = 0; j <= w+1; j++) {
            if (j == x1 && i == y1)
                printf ("s");
            else
                if (j == x2 && i == y2)
                    printf ("d");
                else
                    if (field[j][i])
                        printf (" ");
                    else
                        printf ("%d", sol[j][i]);
        }
        printf ("\n");
    }
            
}
