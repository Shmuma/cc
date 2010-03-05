#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NDEBUG

int maze_size;
char maze[20][20];

unsigned char treas[20];
int treas_count;

/* distances between treasures */
int incidence[200][5];

/* IDs of graph nodes */
int graph[200];
int dist[200];
int done[200];

int dist_matrix[20][20];
int entry_exit_dist[20][2];



int min_distance ()
{
    int id = -1, i;

    for (i = 0; i < maze_size * maze_size; i++)
        if (!done[i] && dist[i] >= 0) {
            if (id < 0 || dist[id] > dist[i])
                id = i;
        }

    return id;
}


/* calculate minimal distances from given point to all other nodes in graph,
 * saving treasures distances to result array */
void calc_distances (int id, int *res, int *entry_exit)
{
    int i, k, l;
    for (i = 0; i < maze_size*maze_size; i++) {
        done[i] = 0;
        dist[i] = (i == id) ? 0 : -1;
    }

    while ((k = min_distance ()) >= 0) {
        for (i = 0; incidence[k][i] >= 0; i++) {
            l = incidence[k][i];
            if (!done[l]) {
                if (dist[l] < 0 || dist[l] > dist[k]+1)
                    dist[l] = dist[k]+1;
            }
        }
        done[k] = 1;
    }

#ifdef DEBUG
    printf ("Dist from %d:\n", id);
    for (i = 0; i < maze_size*maze_size; i++)
        printf ("%d: %d\n", i, dist[i]);
    printf ("\n");
#endif

    for (i = 0; i < treas_count; i++)
        res[i] = dist[treas[i]];

    entry_exit[0] = dist[0];
    entry_exit[1] = dist[maze_size * maze_size - 1];
}


void indent (int count)
{
    int i;

    for (i = 0; i < count; i++) {
        putchar (' ');
        putchar (' ');
    }
}


/* routine recursively searches for minimal way, starting from given */
int find_min_way (int start, int route_length)
{
    int i, dist, min_dist = -1, t;

    if (route_length <= 1) {
        return entry_exit_dist[start][1];
    }
    else {
        done[start] = 1;
        for (i = 0; i < treas_count; i++) {
            if (done[i])
                continue;
            if (dist_matrix[start][i] < 0)
                continue;

            done[i] = 1;
#ifdef DEBUG
            indent (treas_count - route_length);
            printf ("%d -> %d (%d)\n", start, i, dist_matrix[start][i]);
#endif
            dist = find_min_way (i, route_length-1);
            done[i] = 0;
            if (dist > 0) {
                dist += dist_matrix[start][i];
        
                if (min_dist < 0 || dist < min_dist) {
                    min_dist = dist;
#ifdef DEBUG
                    indent (treas_count - route_length);
                    printf ("Best so far: %d\n", dist);
#endif
                }
            }
        }
        done[start] = 0;
    }

#ifdef DEBUG
    indent (treas_count - route_length);
    printf ("%d\n", min_dist);
#endif
    return min_dist;
}



int find_best_way ()
{
    int i, end, res, best = -1, best_id;

    for (i = 0; i < treas_count; i++) {
        if (entry_exit_dist[i][0] < 0)
            return -1;
        res = find_min_way (i, treas_count);
        if (res < 0)
            return -1;

        res += entry_exit_dist[i][0];
        if (best < 0 || best > res) {
            best = res;
            best_id = i;
        }
    }
#ifdef DEBUG
    printf ("Best ID = %d\n", best_id);
#endif
    return best;
}



int main(int argc, char *argv[])
{
    int n, i, j, id, t, k, flag;

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
                    treas[treas_count] = i*maze_size + j;
                    if (treas[treas_count] != 0 &&
                        treas[treas_count] != maze_size * maze_size - 1)
                        treas_count++;
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

        if (maze_size == 1) {
            printf ("0\n");
            continue;
        }

        /* build graph of the maze */
        for (i = 0; i < maze_size; i++) {
            for (j = 0; j < maze_size; j++) {
                t = 0;
                id = i*maze_size + j;
                if (!maze[i][j]) {
                    if (i > 0 && maze[i-1][j] == 0)
                        incidence[id][t++] = (i-1) * maze_size + j;
                    if (j > 0 && maze[i][j-1] == 0)
                        incidence[id][t++] = i * maze_size + j - 1;
                    if (i < maze_size-1 && maze[i+1][j] == 0)
                        incidence[id][t++] = (i+1) * maze_size + j;
                    if (j < maze_size-1 && maze[i][j+1] == 0)
                        incidence[id][t++] = i * maze_size + j + 1;
                }
                incidence[id][t] = -1;
            }
        }

#ifdef DEBUG
        for (i = 0; i < maze_size*maze_size; i++) {
            printf ("%d:", i);

            for (j = 0; incidence[i][j] >= 0; j++)
                printf ("%d ", incidence[i][j]);
            putchar ('\n');
        }

        printf ("Treasures\n");
        for (i = 0; i < treas_count; i++)
            printf ("%d ", treas[i]);
        printf ("\n");
#endif

        /* prepare distance matrix */
        for (i = 0; i < treas_count; i++) {
            for (j = 0; j < treas_count; j++)
                dist_matrix[i][j] = -1;
            entry_exit_dist[i][0] = entry_exit_dist[i][1] = -1;
        }
            
        /* find distance from any treasure to all other treasures plus entry and exit cell */
        for (i = 0; i < treas_count; i++)
            calc_distances (treas[i], dist_matrix[i], entry_exit_dist[i]);

        /* If there are no treasures, we must find way from start to finish */
        if (!treas_count)
            calc_distances (0, dist_matrix[0], entry_exit_dist[0]);


        /* find optimal way to gather all treasures and exit */
#ifdef DEBUG
        putchar ('\n');
        for (i = 0; i < treas_count; i++) {
            printf ("%d: ", i);

            for (j = 0; j < treas_count; j++)
                printf ("%2d ", dist_matrix[i][j]);

            printf ("Entry: %d, Exit: %d", entry_exit_dist[i][0], entry_exit_dist[i][1]);
            putchar ('\n');
        }
#endif

        if (!treas_count)
            printf ("%d\n", entry_exit_dist[0][1]);
        else {
            memset (done, 0, treas_count * sizeof (done[0]));
            t = find_best_way ();
            printf ("%d\n", t);
        }
    }

    return 0;
}
