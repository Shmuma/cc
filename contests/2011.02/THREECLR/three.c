#include <stdio.h>
#include <stdlib.h>

#include <string.h>


int inc_len[500];
int incidence[500][500];

int color[500];


int is_bipart (int n);
int do_color (int node, int val);


int main(int argc, char *argv[])
{
    int t, n, m, u, v, i;

    scanf ("%d", &t);
    
    while (t--) {
        memset (&inc_len, 0, sizeof (inc_len));
        memset (&incidence, 0, sizeof (incidence));
        memset (&color, 0, sizeof (color));

        scanf ("%d %d", &n, &m);

        for (i = 0; i < m; i++) {
            scanf ("%d %d", &u, &v);
            u--;
            v--;
            incidence[u][inc_len[u]++] = v;
            incidence[v][inc_len[v]++] = u;
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
            if (is_bipart (n)) {
                for (i = 0; i < n; i++) {
                    printf ("%d", color[i]);
                    if (i < n-1)
                        putchar (' ');
                }
                putchar ('\n');
            }
            else {
                for (i = 1; i <= n; i++) {
                    printf ("%d", i);
                    if (i < n)
                        putchar (' ');
                }
                putchar ('\n');
            }
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
        return do_color (con, 1);
    else
        return 1;
}


int do_color (int node, int val)
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
            if (!do_color (incidence[node][i], val))
                return 0;
        }
        else
            if (old != val)
                return 0;           /* found node colored to diff color */
    }

    return 1;
}
