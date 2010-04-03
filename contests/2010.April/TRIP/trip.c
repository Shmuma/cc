#include <stdio.h>
#include <stdlib.h>


int n, vol;
int dists[1000000];

int cache[1000000][2];


void solve (int pos, int rest)
{
    int a, b, d;
    int v1, v2;

    printf ("solve: %d, %d\n", pos, rest);

    if (pos == n-1)
        return;
    d = dists[pos+1] - dists[pos];

    if (d <= rest) {
        solve (pos+1, rest - d);
        a = cache[pos+1][0];
        v1 = cache[pos+1][1];

        solve (pos+1, vol - d);
        b = cache[pos+1][0]+1;
        v2 = cache[pos+1][1];

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
        solve (pos+1, vol - d);
        a = cache[pos+1][0]+1;
        v1 = cache[pos+1][1];
    }

    cache[pos][0] = a;
    cache[pos][1] = v1;
}


int main(int argc, char *argv[])
{
    int i;

    scanf ("%d %d", &n, &vol);
    
    for (i = 0; i < n; i++)
        scanf ("%d", dists+i);

    cache[n-1][0] = 0;
    cache[n-1][1] = 1;
    solve (0, vol);
    printf ("%d %d\n", cache[0][0], cache[0][1]);

    return 0;
}
