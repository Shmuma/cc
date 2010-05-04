#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


int cities;
int* inc; /* incidence matrix */
int inc_len[20000];
int p[20000];



void set_inc (int a, int b)
{
/*     printf ("set %d, %d\n", a, b); */
/*     printf ("%d <= %d\n", a * cities + inc_len[a], b); */
/*     printf ("%d <= %d\n", b * cities + inc_len[b], a); */

    inc[a * cities + inc_len[a]++] = b;
    inc[b * cities + inc_len[b]++] = a;
}


int get_inc (int n, int i)
{
    if (i < 0 || i >= inc_len[n]) {
/*         printf ("%d.%d => -1\n", n, i); */
        return -1;
    }

/*     printf ("%d.%d => %d\n", n, i, inc[n * cities + i]); */
    return inc[n * cities + i];
}


void reset_inc (int n, int i)
{
    if (i < 0 || i >= inc_len[n])
        return;

    inc[n * cities + i] = -1;
}



int calc_p (int n, int parent)
{
    int i, res = 0, t;

    if (inc_len[n] == 1) {
        reset_inc (n, 0);
        return 0;
    }

    for (i = 0; i < inc_len[n]; i++) {
        t = get_inc (n, i);
        if (t >= 0) {
            if (t != parent)
                res += calc_p (t, n) + 1;
            else
                reset_inc (n, i);
        }
    }

    p[n] = res;
    return res;
}


unsigned long long calc_im (int n)
{
    unsigned long long res = 1 + 2 * p[n];
    int i, t;

    for (i = 0; i < inc_len[n]; i++) {
        t = get_inc (n, i);
        if (t >= 0)
            res += (p[t]+1) * (p[n] - p[t] - 1);
    }

    return res;
}



int main(int argc, char *argv[])
{
    int t, i;
    int a, b;
    unsigned long long res;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &cities);
        memset (p, 0, sizeof (p));
        memset (inc_len, 0, sizeof (inc_len));
        inc = (int*)calloc (cities * cities, sizeof (int));
        if (!inc)
            kill (0, SIGKILL);

        for (i = 0; i < cities-1; i++) {
            scanf ("%d %d", &a, &b);
            set_inc (a-1, b-1);
        }

        calc_p (0, 0);

        res = 0;
        for (i = 0; i < cities; i++) {
            res += (i+1) * calc_im (i);
            res %= 1000000007;
        }

        printf ("%llu\n", res);
        free (inc);
    }

    return 0;
}
