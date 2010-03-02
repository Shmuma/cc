#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int maze_size;
char maze[20][20];

unsigned char treas[20][2];
int treas_count;

int distance[20][20];


int main(int argc, char *argv[])
{
    int n, i, j;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%d", &maze_size);
        getchar ();

        memset (maze, 0, sizeof (maze));
        memset (treas, 0, sizeof (treas));
        treas_count = 0;

        for (i = 0; i < maze_size; i++) {
            for (j = 0; j < maze_size; j++) {
                switch (getchar ()) {
                case '.':
                    break;
                case '*':
                    treas[treas_count][0] = i;
                    treas[treas_count][1] = j;
                    treas_count++;
                    break;
                case '#':
                    maze[i][j] = 1;
                    break;
                }
                distance[i][j] = 0;
            }
            getchar ();
        }

        /* calculate minimal distance from start to each treasure */
        /* calculate minimal distance from each treasure to all others */
    }

    return 0;
}
