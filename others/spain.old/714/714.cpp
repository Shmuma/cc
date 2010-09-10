// problems
// some changes

// in
// 6 3
// 1000000 1 1 1 1 1
// out
// 1000000 / 1 / 1 1 1 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pages[600];
long long p_sum[600];
int m, k;

long long cache[600][600];
int b_cach[600][600];


long long solve (int scr, int book);

void solve_greedy (int scr, int book);


int main ()
{
    int n, i, t, j, pos;
    long long res;


    scanf ("%d", &n);

    while (n--) {
        scanf ("%d %d", &m, &k); // m - books, k - scribes
        
        for (i = 0; i < m; i++)
            scanf ("%d", pages+i);

        p_sum[m-1] = pages[m-1];
        for (i = m-2; i >= 0; i--)
            p_sum[i] = p_sum[i+1]+pages[i];

        memset (cache, 0, sizeof (cache));
        memset (b_cach, 0, sizeof (b_cach));
        res = solve (k, m);

        t = m;
        pos = 0;
        for (i = 0; i < k; i++) {
            for (j = 0; j < b_cach[k-i][t]; j++) {
                printf ("%d", pages[pos++]);
                if (j != b_cach[k-i][t]-1 || i != k-1)
                    printf (" ");
            }
            if (i != k-1)
                printf ("/ ");
            t -= b_cach[k-i][t];
        }
        printf ("\n");
    }

    return 0;
}


long long solve (int scr, int books)
{
    long long p_best, p_cur, p, i, b_best, b_cur;

    if (cache[scr][books])
        return cache[scr][books];

    if (books == 1) {
        b_cach[scr][books] = 1;
        return pages[m-1];
    }

    if (scr == 1) {
        p = 0;
        for (i = m-books; i < m; i++)
            p += pages[i];
        b_cach[scr][books] = books;
        return p;
    }

    b_best = b_cur = 1;
    p_best = p_cur = 0;

    if (pages[m-books] >= p_sum[m-books+1]) {
        b_best = 1;
        p_best = pages[m-books];

        solve_greedy (scr-1, books-1);
    }
    else {
        for (i = m-books; i <= m-scr; i++) {
            p_cur += pages[i];
            p = solve (scr-1, m-i-1);
            cache[scr-1][m-i-1] = p;

            if (p < p_cur)
                p = p_cur;

            if (p < p_best || !p_best) {
                p_best = p;
                b_best = b_cur;
            }

            b_cur++;
        }
    }
    b_cach[scr][books] = b_best;
    return p_best;
}


void solve_greedy (int scr, int book)
{
    int i;

    for (i = 0; i < scr-1; i++)
        b_cach[scr-i][book-i] = 1;

    b_cach[1][book-scr+1] = book-scr+1;
}
