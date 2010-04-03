#include <stdio.h>
#include <stdlib.h>


int n, vol;
int dists[1000000];


void solve (int pos, int rest, int* stops, int* vars)
{
    int a, b, d;
    int v1, v2;

    printf ("solve: %d, %d\n", pos, rest);

    if (pos == n-1) {
        *stops = 0;
        *vars = 1;
        return;
    }
    d = dists[pos+1] - dists[pos];

    if (d <= rest) {
        solve (pos+1, rest - d, &a, &v1);
        solve (pos+1, vol - d, &b, &v2);

        b++;
        if (a > b) {
            v1 = v2;
            a = b;
        }
        else {
            if (a == b)
                v1++;
        }
    }
    else {
        solve (pos+1, vol - d, &a, &v1);
        a++;
    }

    *stops = a;
    *vars = v1;
}


int main(int argc, char *argv[])
{
    int i, stops, vars;

    scanf ("%d %d", &n, &vol);
    
    for (i = 0; i < n; i++)
        scanf ("%d", dists+i);

    solve (0, vol, &stops, &vars);
    printf ("%d %d\n", stops, vars);

    return 0;
}
