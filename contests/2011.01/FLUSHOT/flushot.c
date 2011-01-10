#include <stdio.h>
#include <stdlib.h>

double places[10001];
double t;
int n;

inline double max (double a, double b)
{
    return (a > b) ? a : b;
}

inline double min (double a, double b)
{
//    printf ("min %lf, %lf\n", a, b);
    return (a > b) ? b : a;
}

double solve (double pos, int idx);

double do_solve (double pos, int idx, double delta)
{
    return max (solve (pos, idx), delta);
}

double solve (double pos, int idx)
{
    double d = 0.0, dd;

    if (idx == n)
        return d;

//    printf ("+solve (%lf, %d)\n", pos, idx);

    if (places[idx] - pos > t) {
        /* we have space to make step to the left - find the optimal value */
        d = places[idx] - pos - t;
        dd = //min (solve (places[idx], idx+1), 
                  min (do_solve (places[idx] - d, idx+1, d),
                       do_solve (places[idx] - d/2, idx+1, d/2));
    }
    else
        if (places[idx] - pos < t) {
            d = t - (places[idx] - pos);
            dd = do_solve (places[idx] + d, idx+1, d);
        }
        else
            dd = solve (places[idx], idx+1);
//    printf ("-solve (%lf, %d) => %lf\n", pos, idx, dd);
    return dd;
}


int main (int argc, char *argv[])
{
    int cnt, i;
    double r1, r2;

    scanf ("%d", &cnt);

    while (cnt--) {
        scanf ("%d %lf", &n, &t);
        for (i = 0; i < n; i++)
            scanf ("%lf", &places[i]);
        printf ("%.4lf\n", solve (-t, 0));
    }

    return 0;
}
