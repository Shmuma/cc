#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int t, n, m, u, v, i;

    scanf ("%d", &t);
    
    while (t--) {
        scanf ("%d %d", &n, &m);

        for (i = 0; i < m; i++)
            scanf ("%d %d", &u, &v);
        
        if (m == 0) {            /* trivial - process all */
            for (i = 1; i <= n; i++) {
                putchar ('1');
                if (i < n)
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
    return 0;
}
