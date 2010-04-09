#include <stdio.h>
#include <stdlib.h>


int n, vol;
int deltas[1000001];
int rest[1000001];
int feed[1000001];


int main(int argc, char *argv[])
{
    int i, stops, vars, prev = 0, val, c_vol, j;
    int prev_feed;

    scanf ("%d %d", &n, &vol);

    scanf ("%d", &prev);
    for (i = 1; i < n; i++) {
        scanf ("%d", &val);
        deltas[i-1] = val-prev;
        prev = val;
    }

    prev_feed = 0;
    stops = 0;
    c_vol = vol;

    for (i = 1; i < n; i++) {
        rest[i-1] = c_vol;

        if (c_vol < deltas[i-1]) {
            stops++;
            stops %= 1000000007;
            c_vol = vol;
            prev_feed = i-1;
        }
        c_vol -= deltas[i-1];
        feed[i-1] = prev_feed;
    }

    rest[n-1] = c_vol;

    /* count amount of variables */
    vars = 1;
    for (i = n-1; i >= 0; i--) {
        if (rest[i] > 0 && (feed[i] == i || i == n-1)) {
            c_vol = rest[i];
            /* if we filled our car at this point AND we had fuel, we can move previous filling point c_vol left */
            for (j = feed[i-1]; j > 0; j--) {
                if (c_vol >= deltas[j-1]) {
                    vars++;
                    vars %= 1000000007;
                    c_vol -= deltas[j-1];
                }
                else
                    break;
            }
        }
    }

    printf ("%d %d\n", stops, vars);

    return 0;
}
