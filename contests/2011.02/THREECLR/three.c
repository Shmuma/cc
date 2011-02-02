#include <stdio.h>
#include <stdlib.h>

#include <string.h>


int inc_len[500];
int incidence[500][500];

int color[500];
int degree[500][2];


int is_bipart (int n);
int do_color (int node, int val);
void do_approx_color (int n);

int main(int argc, char *argv[])
{
    int t, n, m, u, v, i;

    scanf ("%d", &t);
    
    while (t--) {
        memset (&inc_len, 0, sizeof (inc_len));
        memset (&incidence, 0, sizeof (incidence));
        memset (&color, 0, sizeof (color));
        memset (&degree, 0, sizeof (degree));

        scanf ("%d %d", &n, &m);

        for (i = 0; i < m; i++) {
            scanf ("%d %d", &u, &v);
            u--;
            v--;
            incidence[u][inc_len[u]++] = v;
            incidence[v][inc_len[v]++] = u;
            degree[u][1]++;
            degree[v][1]++;
        }
        
        if (m == 0) {            /* trivial - process all */
            for (i = 1; i <= n; i++) {
                putchar ('1');
                if (i < n)
                    putchar (' ');
            }
            putchar ('\n');
        }
        else {
            if (!is_bipart (n)) {
                memset (&color, 0, sizeof (color));
                do_approx_color (n);
            }

            for (i = 0; i < n; i++) {
                printf ("%d", color[i]);
                if (i < n-1)
                    putchar (' ');
            }
            putchar ('\n');
        }
    }
    return 0;
}


int is_bipart (int n)
{
    int con = -1, i;

    for (i = 0; i < n; i++)
        if (!inc_len[i])
            color[i] = 1;
        else
            con = i;

    if (con >= 0)
        return do_bi_color (con, 1);
    else
        return 1;
}


int do_bi_color (int node, int val)
{
    int i, res = 1, old;

    color[node] = val;
    if (val == 1)
        val = 2;
    else
        val = 1;

    for (i = 0; i < inc_len[node]; i++) {
        old = color[incidence[node][i]];
        if (old == 0) {
            if (!do_bi_color (incidence[node][i], val))
                return 0;
        }
        else
            if (old != val)
                return 0;           /* found node colored to diff color */
    }

    return 1;
}


int comp_degree (const void* a, const void* b)
{
    int* aa = (int*)a;
    int* bb = (int*)b;

    return bb[1] - aa[1];
}


void do_approx_color (int n)
{
    int i, k, j;
    int count = n, flg, ver;

    for (i = 0; i < n; i++)
        degree[i][0] = i;

    qsort (degree, n, sizeof (degree[0]), comp_degree);

    k = 1;
    while (count) {
        for (i = 0; i < n; i++) {
            ver = degree[i][0];
            if (!color[ver]) {
                flg = 0;
                for (j = 0; !flg && j < inc_len[ver]; j++)
                    flg = color[incidence[ver][j]] == k;
                if (!flg) {
                    color[ver] = k;
                    count--;
                }
            }
        }
        k++;
    }
}
