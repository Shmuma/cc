#include <stdio.h>
#include <stdlib.h>

double places[10001];


double solve (double t, int n, int first_move)
{
    double prev = -t, d = 0.0, new_place;
    int i;

    for (i = 0; i < n; i++) {
        if (places[i] - prev > t) {
            if (places[i] - prev - t < d || (i == 0 && first_move)) {
                new_place = places[i] - (places[i] - prev - t);
                if (i == 0)
                    d = (places[i] - prev - t);
            }
            else
                new_place = places[i] - d;
        }
        else
            if (places[i] - prev < t) {
                if (t - (places[i] - prev) > d)
                    d = t - (places[i] - prev);
                new_place = places[i] + (t - (places[i] - prev));
            }
        prev = new_place;
    }

    return d;
}


int main (int argc, char *argv[])
{
    int cnt, n, i;
    double t, r1, r2;

    scanf ("%d", &cnt);

    while (cnt--) {
        scanf ("%d %lf", &n, &t);
        for (i = 0; i < n; i++)
            scanf ("%lf", &places[i]);
        r1 = solve (t, n, 0);
        r2 = solve (t, n, 1);
        if (r1 < r2)
            printf ("%.4lf\n", r1);
        else
            printf ("%.4lf\n", r2);
    }

    return 0;
}
