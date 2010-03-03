#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG


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


/* /\* routine recursive *\/ */
/* int find_min_way (); */


int main(int argc, char *argv[])
{
    int n, i, j, id, t, k;

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
#ifdef DEBUG
                    putchar ('.');
#endif
                    break;
                case '*':
#ifdef DEBUG
                    putchar ('*');
#endif
                    treas[treas_count++] = i*maze_size + j;
                    break;
                case '#':
#ifdef DEBUG
                    putchar ('#');
#endif
                    maze[i][j] = 1;
                    break;
                }
            }
            getchar ();
#ifdef DEBUG
            putchar ('\n');
#endif
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

#ifdef DEBUG
        for (i = 0; i < maze_size*maze_size; i++) {
            printf ("%d:", i);

            for (j = 0; j < incidence[i][0]; j++)
                printf ("%d ", incidence[i][j+1]);
            putchar ('\n');
        }

        printf ("Treasures\n");
        for (i = 0; i < treas_count; i++)
            printf ("%d ", treas[i]);
        printf ("\n");
#endif

        /* prepare distance matrix */
        for (i = 0; i < treas_count+2; i++)
            for (j = 0; j < treas_count+2; j++)
                dist_matrix[i][j] = -1;
            
        /* find distance from entry to all treasures */
        calc_distances (0);
        save_dist (0);

        /* find distance from any treasure to all other treasures */
        for (i = 0; i < treas_count; i++) {
            calc_distances (treas[i]);
            save_dist (i+1);
        }

        /* find distance from exit to all treasures */
        calc_distances (maze_size * maze_size - 1);
        save_dist (treas_count+1);

        /* find optimal way to gather all treasures and exit */
#ifdef DEBUG
        putchar ('\n');
        for (i = 0; i < treas_count+2; i++) {
            printf ("%d: ", i);

            for (j = 0; j < treas_count+2; j++)
                printf ("%2d ", dist_matrix[i][j]);
            putchar ('\n');
        }
#endif

        memset (done, 0, (treas_count+2)*sizeof (done[0]));
        done[0] = 1;
        /* i - count of collected treasures */
        /* k - current treasure or entry/exit */
        /* t - count of steps performed */
        i = k = t = 0;
        while (k != treas_count+1) {
            id = -1;
            for (j = 0; j < treas_count+2; j++) {
                if (j == treas_count+1 && i != treas_count)
                    break;
                if (done[j])
                    continue;
                if (k == j)
                    continue;
                if (dist_matrix[k][j] < 0)
                    continue;
                if (id < 0 || dist_matrix[k][id] > dist_matrix[k][j])
                    id = j;
            }

            if (id < 0) {
                t = -1;
                break;
            }
            
            done[id] = 1;
#ifdef DEBUG
            printf ("%d -> %d (%d)\n", k, id, dist_matrix[k][id]);
#endif            
            t += dist_matrix[k][id];
            k = id;
            i++;
        }

        printf ("%d\n", t);
    }

    return 0;
}
