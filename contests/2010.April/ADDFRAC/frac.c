#include <stdio.h>
#include <stdlib.h>

unsigned long long frac[100005][2];
unsigned long long dp[100005][2];


unsigned long long gt (unsigned long long a1, unsigned long long b1,
                       unsigned long long a2, unsigned long long b2)
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


void solve_dp (unsigned long long n)
{
    int i;
    unsigned long long g, a, b;

    dp[n-1][0] = frac[n-1][0];
    dp[n-1][1] = frac[n-1][1];

    for (i = n-2; i >= 0; i--) {
        a = dp[i+1][0] + frac[i][0];
        b = dp[i+1][1] + frac[i][1];
        
        if (gt (a, b, frac[i][0], frac[i][1])) {
            dp[i][0] = a;
            dp[i][1] = b;
        }
        else {
            dp[i][0] = frac[i][0];
            dp[i][1] = frac[i][1];           
        }
    }

    for (i = 0; i < n; i++) {
        g = gcd (dp[i][0], dp[i][1]);
        printf ("%llu/%llu\n", dp[i][0]/g, dp[i][1]/g);        
    }
}


int main(int argc, char *argv[])
{
    unsigned long long t, n, i, g;

    scanf ("%llu", &t);
    while (t--) {
        scanf ("%llu", &n);
        for (i = 0; i < n; i++) {
            scanf ("%llu", &frac[i][0]);
            getchar ();
            scanf ("%llu", &frac[i][1]);
            getchar ();
        }

        solve_dp (n);
        if (t > 0)
            putchar ('\n');
    }
    return 0;
}
