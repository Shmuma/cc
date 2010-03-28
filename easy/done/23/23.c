#include <stdio.h>
#include <stdlib.h>

int board_size;
char board[2000][2000];
int cache[2000][2000];

const int delta_x[] = {
    2, 1, 2, 1
};

const int delta_y[] = {
    -1, -2, +1, +2
};


int solve (int x, int y)
{
    int res, max, i, dx, dy;

    if (cache[y][x] >= 0)
        return cache[y][x];

    max = 0;

    for (i = 0; i < 4; i++) {
        dx = x+delta_x[i];
        dy = y+delta_y[i];

        if (dx >= board_size || dx < 0)
            continue;
        if (dy >= board_size || dy < 0)
            continue;

        res = solve (dx, dy);
        if (res > max)
            max = res;
    }

    if (board[y][x] == 'P')
        max++;

    cache[y][x] = max;
    return max;
}


int main(int argc, char *argv[])
{
    int t, i, j, c, pos_x, pos_y;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &board_size);
        getchar ();

        for (j = 0; j < board_size; j++) {
            scanf ("%s", &board[j][0]);
            for (i = 0; i < board_size; i++) {
                if (board[j][i] == 'K') {
                    pos_x = i;
                    pos_y = j;
                }
                cache[j][i] = -1;
            }
            getchar ();
        }

        printf ("%d\n", solve (pos_x, pos_y));
    }

    return 0;
}
