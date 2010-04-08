#include <stdio.h>
#include <stdlib.h>


int n, vol;


int main(int argc, char *argv[])
{
    int i, stops, vars, prev = 0, val, c_vol, d;

    scanf ("%d %d", &n, &vol);

    stops = 0;
    vars = 0;
    c_vol = vol;

    scanf ("%d", &prev);
    
    for (i = 1; i < n; i++) {
        scanf ("%d", &val);
        d = val-prev;
        prev = val;

        if (c_vol < d) {
            stops++;
            stops %= 1000000007;
            c_vol = vol;
        }
        else {
            vars++;
            vars %= 1000000007;
        }
        c_vol -= d;
    }

    printf ("%d %d\n", stops, vars);

    return 0;
}
