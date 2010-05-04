#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


struct stack {
    int count, size;
    int* data;
};


int cities;
struct stack *inc; /* incidence matrix */
unsigned long long p[20000];


void push (struct stack *s, int val)
{
    if (s->count == s->size) {
        s->size += 16;
        s->data = realloc (s->data, s->size * sizeof (int));
    }

    s->data[s->count++] = val;
}


void set_inc (int a, int b)
{
    push (&inc[a], b);
    push (&inc[b], a);
}


int get_inc (int n, int i)
{
    if (i < 0 || i >= inc[n].count)
        return -1;
    return inc[n].data[i];
}


void reset_inc (int n, int i)
{
    if (i < 0 || i >= inc[n].count)
        return;

    inc[n].data[i] = -1;
}



int calc_p (int n, int parent)
{
    int i, res = 0, t;

    if (inc[n].count == 1) {
        reset_inc (n, 0);
        return 0;
    }

    for (i = 0; i < inc[n].count; i++) {
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

    for (i = 0; i < inc[n].count; i++) {
        t = get_inc (n, i);
        if (t >= 0)
            res += (p[t]+1) * (p[n]-p[t]-1);
    }

    return res;
}



int main(int argc, char *argv[])
{
    int t;
    int a, b;
    unsigned long long res, i;

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &cities);
        memset (p, 0, sizeof (p));
        inc = calloc (cities, sizeof (struct stack));

        for (i = 0; i < cities-1; i++) {
            scanf ("%d %d", &a, &b);
            set_inc (a-1, b-1);
        }

        calc_p (0, 0);

        res = 0;
        for (i = 0; i < cities; i++)
            res += (i+1)*calc_im (i);

        printf ("%llu\n", res % 1000000007);
        for (i = 0; i < cities; i++)
            if (inc[i].count)
                free (inc[i].data);
        free (inc);
    }

    return 0;
}
