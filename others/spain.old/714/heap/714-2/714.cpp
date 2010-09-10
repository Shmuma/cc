#include <stdio.h>
#include <stdlib.h>


int m, k;
int pages[500];
int division[500];


long long solve (int books, int scr);


int main ()
{
    int n, i;

    scanf ("%d", &n);

    while (n--) {
        scanf ("%d %d", &m, &k);
        
        for (i = 0; i < m; i++)
            scanf ("%d", pages+i);

        solve (m, k);

        for (i = 0; i < k; i++)
            printf ("%d ", division[i]);
        printf ("\n\n");
    }

    return 0;
}


long long solve (int books, int scr)
{
    // another approach -- binary search
    int l, r, s, i;
    long long t, p;

    printf ("Solve (%d, %d)\n", books, scr);

    if (books == 1) {
        division[k-scr] = 0;
        return pages[m-1];
    }

    if (scr == 1) {
        p = 0;
        for (i = m-books; i < m; i++)
            p += pages[i];
        division[k-scr] = books-1;
        return p;
    }

    l = m-books;
    r = m-scr;

    p = pages[l];
    t = 0;

    while (l < r) {
        s = (l+r) >> 1;
        printf ("l = %d, s = %d, r = %d\n", l, s, r);
        
        // how many pages should we process?
        p = 0;
        for (i = m-books; i <= s; i++)
            p += pages[i];

        // what if we take s books?
        t = solve (m-s-1, scr-1);
        
        printf ("p = %lld, t = %lld\n", p, t);

        if (p == t) {
            printf ("_set div %d to %d\n", k-scr, s-(m-books));
            division[k-scr] = s-(m-books);
            return p;
        }

        if (p < t)
            l = s+1;
        else
            r = s-1;
    }

    if (p < t)
        p = t;
    printf ("set div %d to %d\n", k-scr, s-(m-books));
    division[k-scr] = s-(m-books);

    return p;
}
