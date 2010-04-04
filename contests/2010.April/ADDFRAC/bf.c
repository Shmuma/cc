#include <stdio.h>
#include <stdlib.h>

int frac[100000][2];
unsigned long long dp[100000][2];


int gt (int a1, int b1, int a2, int b2)
{
    unsigned long long aa1, aa2;

    aa1 = a1;
    aa2 = a2;
    aa1 *= b2;
    aa2 *= b1;

    return aa1 > aa2;
}


unsigned long long gcd (unsigned long long a, unsigned long long b)
{
    unsigned long long t;

    if (a < b)
        return gcd (b, a);

    while (b) {
        t = a % b;
        a = b;
        b = t;
    }

    return a;
}


void solve (int n)
{
    int i, j;
    unsigned long long a, b, g, ma, mb;

    for (i = 0; i < n; i++) {
        ma = a = frac[i][0];
        mb = b = frac[i][1];
        for (j = i+1; j < n; j++) {
            a += frac[j][0];
            b += frac[j][1];
            if (gt (a, b, ma, mb)) {
                ma = a;
                mb = b;
            }
        }

        g = gcd (ma, mb);
        printf ("%llu/%llu\n", ma/g, mb/g);
    }
}

int main(int argc, char *argv[])
{
    int t, n, i;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        for (i = 0; i < n; i++) {
            scanf ("%d", &frac[i][0]);
            getchar ();
            scanf ("%d", &frac[i][1]);
            getchar ();
        }

        solve (n);
        putchar ('\n');
    }
    return 0;
}
