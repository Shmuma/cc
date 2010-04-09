#include <stdio.h>
#include <stdlib.h>


int n, vol;
int deltas[1000001];


int main(int argc, char *argv[])
{
    int i, stops, vars, prev = 0, val, c_vol, j;

    scanf ("%d %d", &n, &vol);

    stops = 0;
    vars = 1;
    c_vol = vol;

    scanf ("%d", &prev);
    
    for (i = 1; i < n; i++) {
        scanf ("%d", &val);
        deltas[i-1] = val-prev;
        prev = val;

        if (c_vol < deltas[i-1]) {
            stops++;
            stops %= 1000000007;
            if (c_vol > 0) {
                int d = c_vol;

                /* step back to find amount of ways to plan */
                for (j = i-1; j >= 0; j++) {
                    if (c_vol > 0) {
                        c_vol -= deltas[j];
                        vars++;
                        vars %= 1000000007;
                        break;
                    }
                }
            }
            c_vol = vol;
        }
        c_vol -= deltas[i-1];
    }

    if (c_vol > 0) {
        int d = c_vol;

        /* step back to find amount of ways to plan */
        for (j = n-2; j >= 0; j++) {
            if (c_vol > 0) {
                c_vol -= deltas[j];
                vars++;
                vars %= 1000000007;
                break;
            }
        }
    }

    printf ("%d %d\n", stops, vars);

    return 0;
}
