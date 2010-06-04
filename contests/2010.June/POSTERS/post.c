#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int crossed_cnt[100];
int crossed[100][100];

int coords[100][4];
int indices[100];


int between (int a, int b, int n1, int n2)
{
    return n1 > a && n1 < b && n2 > a && n2 < b;
}


int is_crosses (int a, int b)
{
    if (between (coords[a][0], coords[a][2], coords[b][0], coords[b][2]) && 
        between (coords[b][1], coords[b][3], coords[a][1], coords[a][3]))
        return 1;

    if (between (coords[b][0], coords[b][2], coords[a][0], coords[a][2]) && 
        between (coords[a][1], coords[a][3], coords[b][1], coords[b][3]))
        return 1;

    return 0;
}


int crosses_count (int n)
{
    int res = 0;

    while (n > 0)
        res += crossed_cnt[--n];

    return res;
}



int compare (const void *a, const void *b)
{
    int aa = *(const int*)a;
    int bb = *(const int*)b;

    return crossed_cnt[aa] - crossed_cnt[bb];
}



int find_best (int n)
{
    int i;

    for (i = 0; i < n; i++)
        indices[i] = i;

    qsort (indices, n, sizeof (int), compare);
    return indices[n-1];
}



void remove_poster (int n, int poster)
{
    int i, j, t, k;

    for (i = 0; i < crossed_cnt[poster]; i++) {
        t = crossed[poster][i];
        j = 0;

        while (j < crossed_cnt[t]) {
            if (crossed[t][j++] == poster)
                break;
        }

        while (j < crossed_cnt[t]) {
            crossed[t][j-1] = crossed[t][j];
            j++;
        }

        crossed_cnt[t]--;
    }

    crossed_cnt[poster] = 0;
}



int main(int argc, char *argv[])
{
    int t, n, i, j, best, rest;

    scanf ("%d", &t);

    while (t--) {
        memset (&crossed, 0, sizeof (crossed));
        memset (&crossed_cnt, 0, sizeof (crossed_cnt));

        scanf ("%d", &n);
        
        for (i = 0; i < n; i++)
            scanf ("%d %d %d %d", coords[i]+0, coords[i]+2, coords[i]+1, coords[i]+3);

        /* calc crosses */
        for (i = 0; i < n; i++) {
            for (j = i+1; j < n; j++) {
                if (is_crosses (i, j)) {
                    crossed[i][crossed_cnt[i]++] = j;
                    crossed[j][crossed_cnt[j]++] = i;
                }
            }
        }

        rest = n;

        while (crosses_count (n)) {
            best = find_best (n);

            /* remove the most crossed poster */
            remove_poster (n, best);
            rest--;
        }

        printf ("%d\n", rest);
    }

    return 0;
}
