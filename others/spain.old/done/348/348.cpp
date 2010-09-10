#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int count;
int matr[100][2];

int cache[20][20];
long long c_mult[20][20];


int solve (int, int, long long*);
void display (int, int);


int main ()
{
    int n, pos, cas = 1;
    long long mults;

    while (1) {
        scanf ("%d", &n);

        if (!n)
            break;

        count = n;

        for (int i = 0; i < count; i++)
            scanf ("%d %d", &matr[i][0], &matr[i][1]);

        memset (cache, 0, sizeof (cache));
        memset (c_mult, 0, sizeof (c_mult));
        pos = solve (1, count, &mults);
        
        printf ("Case %d: (", cas++);
        display (1, count);
        printf (")\n");
    }

    return 0;
}


// returns optimaldivision of matrices A[i]..A[j]
int solve (int from, int to, long long* mults)
{
    int a, b, kopt;
    long long m1, m2, mopt;

    if (from == to) {
        *mults = 0;
        return from;
    }

    if (cache[from-1][to-1]) {
        *mults = c_mult[from-1][to-1];
        return cache[from-1][to-1];
    }

    mopt = 0;
    kopt = from;

    for (int i = from; i < to; i++) {
        a = solve (from, i, &m1);
        b = solve (i+1, to, &m2);

        m1 += m2 + matr[from-1][0]*matr[i-1][1]*matr[to-1][1];

        if (!mopt) {
            mopt = m1;
            kopt = i;
        }
        else {
            if (m1 < mopt) {
                kopt = i;
                mopt = m1;
            }
        }
    }

    *mults = mopt;
    c_mult[from-1][to-1] = mopt;
    cache[from-1][to-1]  = kopt;
    return kopt;
}


void display (int from, int to)
{
    int d = cache[from-1][to-1];

    if (from != to) {
        if (from != d) {
            printf ("(");
            display (from, d);
            printf (") x ");
        }
        else
            printf ("A%d x ", from);

        if (d+1 != to) {
            printf ("(");
            display (d+1, to);
            printf (")");
        }
        else
            printf ("A%d", to);
    }
    else 
        printf ("A%d", from);
}
