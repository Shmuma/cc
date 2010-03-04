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

#ifdef DEBUG
    printf ("Dist from %d:\n", id);
    for (i = 0; i < graph_size; i++)
        printf ("%d: %d\n", i, dist[i]);
    printf ("\n");
#endif
}


/* Check calculated distance that all targets are accessible */
int check_dist ()
{
    int i;
    for (i = 0; i < graph_size; i++)
        if (dist[i] == -1)
            return 0;
    return 1;
}



/* routine recursively searches for minimal way, starting from given */
int find_min_way (int start, int route_length)
{
    int i, dist, min_dist = -1;

    if (route_length == treas_count+1) {
        return dist_matrix[start][treas_count+1];
    }
    else {
        for (i = 0; i < treas_count+1; i++) {
            if (done[i])
                continue;
            if (i == start)
                continue;
            if (dist_matrix[start][i] < 0)
                continue;

            done[i] = 1;
#ifdef DEBUG
            printf ("%d -> %d (%d)\n", start, i, dist_matrix[start][i]);
#endif
            dist = find_min_way (i, route_length+1);
            done[i] = 0;
            if (dist > 0) {
                dist += dist_matrix[start][i];
        
                if (min_dist < 0 || dist < min_dist)
                    min_dist = dist;
            }
        }
    }

    return min_dist;
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
        if (!check_dist ()) {
            printf ("-1\n");
            continue;
        }
        save_dist (0);
        if (graph_size > 0)
            dist_matrix[0][treas_count+1] = dist_matrix[treas_count+1][0] = dist[graph_size-1];

        /* find distance from any treasure to all other treasures */
        flag = 0;
        for (i = 0; i < treas_count; i++) {
            calc_distances (treas[i]);
            if (!check_dist ()) {
                printf ("-1\n");
                flag = 1;
                break;
            }
            save_dist (i+1);
        }
        if (flag)
            continue;

        /* find distance from exit to all treasures */
        calc_distances (maze_size * maze_size - 1);
        if (!check_dist ()) {
            printf ("-1\n");
            continue;
        }
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

        if (!treas_count)
            printf ("%d\n", dist_matrix[0][1]);
        else {
            memset (done, 0, (treas_count+2)*sizeof (done[0]));
            done[0] = 1;
            t = find_min_way (0, 1);
            printf ("%d\n", t);
        }
    }

    return 0;
}
