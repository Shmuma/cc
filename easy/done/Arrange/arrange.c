#include <stdio.h>
#include <stdlib.h>

int inv_table[17][65536];


int invert (int v, int n)
{
    int r = 0, i;

    for (i = 0; i < n; i++) {
        if (!v)
            return r << (n-i);
        r <<= 1;
        if (v % 2)
            r++;
        v >>= 1;
    }
    return r;
}


void build_table ()
{
    int n, i;

    for (n = 1; n <= 16; n++)
        for (i = 0; i < 1 << n; i++)
            inv_table[n][i] = invert (i, n);
}


int main (int argc, char *argv[])
{
    int t, n, i, c, v;
    static char res[70000];

    build_table ();

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        getchar ();             /* space */
        
        for (i = 0; i < 1 << n; i++) {
            c = getchar ();
            res[inv_table[n][i]] = c;
        }

        res[1 << n] = 0;
        puts (res);
    }

    return 0;
}
