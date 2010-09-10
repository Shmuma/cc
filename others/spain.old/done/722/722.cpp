#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char field[100][100];
int sx, sy;

int solve (int x, int y);



int main ()
{
    int n, x, y, i;
    char c;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%d %d", &y, &x);
        getchar ();

        memset (field, 0, sizeof (field));
        // first line blindly
        sx = 0;
        while (1) {
            c = getchar ();
            if (c == '\n')
                break;
            field[0][sx++] = c-'0';
        }

        sy = 1;
        while (1) {
            for (i = 0; i < sx; i++) {
                c = getchar ();
                if (c == '\n' || c == -1)
                    break;
                field[sy][i] = c-'0';
            }

            if (c == '\n' || c == -1)
                break;

            sy++;
            c = getchar ();
        }

        int res = solve (x-1, y-1);
        printf ("%d\n", res);
        if (n > 0)
            printf ("\n");
    }

    return 0;
}


int solve (int x, int y)
{
    if (x < 0 || y < 0)
        return 0;

    if (x == sx || y == sy)
        return 0;

    if (field[y][x])
        return 0;
    
    int res = 1;

    field[y][x] = 2;

    //    printf ("%d %d\n", y+1, x+1);

    res += solve (x-1, y);
    res += solve (x, y-1);
    res += solve (x+1, y);
    res += solve (x, y+1);

    return res;
}
