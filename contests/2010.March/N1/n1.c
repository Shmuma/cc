#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int maze_size;
char maze[20][20];

unsigned char treas[20];
int treas_count;

/* distances between treasures */
int incidence[200][5];

/* IDs of graph nodes */
int graph[200];
int graph_rev[200];
int graph_size;
int dist[200];
int done[200];

int dist_matrix[20][20];


void save_dist (int id)
{
    int i;

    dist_matrix[id][0] = 0;
    for (i = 0; i < treas_count; i++)
        dist_matrix[i+1][id] = dist_matrix[id][i+1] = dist[graph_rev[treas[i]]];
}


int min_distance ()
{
    int id = -1, i;

    for (i = 0; i < graph_size; i++)
        if (!done[i] && dist[i] >= 0) {
            if (id < 0 || dist[id] > dist[i])
                id = i;
        }

    return id;
}


/* calculate minimal distances from given point to all other nodes in graph */
void calc_distances (int id)
{
    int i, j, k, l;
    for (i = 0; i < graph_size; i++) {
        done[i] = 0;
        dist[i] = (graph[i] == id) ? 0 : -1;
    }

    while ((k = min_distance ()) >= 0) {
        /* k is graph's index */
        j = graph[k];
        for (i = 0; i < incidence[j][0]; i++) {
            l = graph_rev[incidence[j][i+1]];
            if (!done[l]) {
                if (dist[l] < 0 || dist[l] > dist[k]+1)
                    dist[l] = dist[k]+1;
            }
        }
        done[k] = 1;
    }
}


int main(int argc, char *argv[])
{
    int n, i, j, id, t;

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
                    treas[treas_count++] = i*maze_size + j;
                    break;
                case '#':
                    maze[i][j] = 1;
                    break;
                }
            }
            getchar ();
        }
        getchar ();

        graph_size = 0;

        /* build graph of the maze */
        for (i = 0; i < maze_size; i++) {
            for (j = 0; j < maze_size; j++) {
                t = 0;
                id = i*maze_size + j;
                if (!maze[i][j]) {
                    if (i > 0 && maze[i-1][j] == 0)
                        incidence[id][++t] = (i-1) * maze_size + j;
                    if (j > 0 && maze[i][j-1] == 0)
                        incidence[id][++t] = i * maze_size + j - 1;
                    if (i < maze_size-1 && maze[i+1][j] == 0)
                        incidence[id][++t] = (i+1) * maze_size + j;
                    if (j < maze_size-1 && maze[i][j+1] == 0)
                        incidence[id][++t] = i * maze_size + j + 1;
                }
                incidence[id][0] = t;
                if (t) {
                    graph_rev[id] = graph_size;
                    graph[graph_size++] = id;
                }
                else
                    graph_rev[id] = -1;
            }
        }

        for (i = 0; i < maze_size; i++) {
            for (j = 0; j < maze_size; j++)
                printf ("%d ", i * maze_size + j);
            putchar ('\n');
        }

        for (i = 0; i < maze_size; i++) {
            for (j = 0; j < maze_size; j++) {
                putchar (maze[i][j] ? '#' : '.');
            }
            putchar ('\n');
        }


        for (i = 0; i < maze_size*maze_size; i++) {
            printf ("%d:", i);

            for (j = 0; j < incidence[i][0]; j++)
                printf ("%d ", incidence[i][j+1]);
            putchar ('\n');
        }

        /* find distance from entry to all treasures */
        calc_distances (0);
        save_dist (0);

        /* find distance from any treasure to all other treasures */
        for (i = 0; i < treas_count; i++) {
            calc_distances (treas[i]);
            save_dist (treas[i]);
        }

        /* find distance from exit to all treasures */
        calc_distances (maze_size * maze_size - 1);
        save_dist (maze_size * maze_size - 1);

        /* find optimal way to gather all treasures and exit */
        putchar ('\n');
        for (i = 0; i < treas_count+2; i++) {
            printf ("%d:", i);

            for (j = 0; j < treas_count+2; j++)
                printf ("%d ", dist_matrix[i][j]);
            putchar ('\n');
        }
    }

    return 0;
}
