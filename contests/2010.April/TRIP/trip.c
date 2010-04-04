#include <stdio.h>
#include <stdlib.h>


int n, vol;
int dists[1000000];


void solve (int pos, int rest, int* stops, int* vars)
{
    int a, b, d;
    int v1, v2;

    //    printf ("solve: %d, %d\n", pos, rest);

    if (pos == n-1) {
        *stops = 0;
        *vars = 1;
        return;
    }
    d = dists[pos+1];

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


void solve2 (int* stops, int* vars)
{
    int s, v, i, d;

    s = 0;
    v = vol;
    *vars = 0;

    for (i = 1; i < n; i++) {
        d = dists[i];
        if (v < d) {
            s++;
            v = vol;
        }
        else
            (*vars)++;
        v -= d;
    }

    *stops = s;
}


int main(int argc, char *argv[])
{
    int i, stops, vars, prev = 0, val;

    scanf ("%d %d", &n, &vol);
    
    for (i = 0; i < n; i++) {
        scanf ("%d", &val);
        dists[i] = val-prev;
        prev = val;
    }

    //    solve (0, vol, &stops, &vars);
    solve2 (&stops, &vars);
    printf ("%d %d\n", stops, vars % 1000000007);

    return 0;
}
