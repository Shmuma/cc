#include <stdio.h>
#include <stdlib.h>

/*
 * There are 4 kinds of points:
 * 0 - even x, even y
 * 1 - even x, odd y
 * 2 - odd x, even y
 * 3 - odd x, odd y
 */

unsigned char oddity[4][4][4];
unsigned int cnt_a[4], cnt_b[4], cnt_c[4], cnt_d[4];

void count (int n, int* even, int* neven)
{
    if (n % 2)
        (*neven)++;
    else
        (*even)++;
}


int min (int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}


inline int abs (int v)
{
    return v < 0 ? -v : v;
}


void get_pt_by_kind (int kind, int* x, int* y)
{
    switch (kind) {
    case 0:
        *x = 2;
        *y = 2;
        break;
    case 1:
        *x = 2;
        *y = 1;
        break;
    case 2:
        *x = 1;
        *y = 2;
        break;
    case 3:
        *x = 1;
        *y = 1;
        break;
    }
}


int is_area_odd (int xa, int ya, int xb, int yb, int xc, int yc)
{
    int area = (xa - xc)*(ya - yb) - (xa - xb)*(ya - yc);

    return abs (area) % 2;
}


int get_pt_kind (int x, int y)
{
    x = abs (x);
    y = abs (y);
    
    if (x % 2)
        if (y % 2)
            return 3;
        else
            return 2;
    else
        if (y % 2)
            return 1;
        else
            return 0;
}


int main(int argc, char *argv[])
{
    int t, n, i, j, k, x, y;
    int res;
    int xa, ya, xb, yb, xc, yc;
    int total1, odd1, total2, odd2;

    /* generate oddity table */
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            for (k = 0; k < 4; k++) {
                get_pt_by_kind (i, &xa, &ya);
                get_pt_by_kind (j, &xb, &yb);
                get_pt_by_kind (k, &xc, &yc);
        
                oddity[i][j][k] = is_area_odd (xa, ya, xb, yb, xc, yc);
            }

    scanf ("%d", &t);
    
    while (t--) {
        scanf ("%d", &n);

        for (i = 0; i < 4; i++)
            cnt_a[i] = cnt_b[i] = cnt_c[i] = cnt_d[i] = 0;

        for (i = 0; i < n; i++) {
            scanf ("%d %d", &x, &y);
            if (x == 0 || y == 0)
                continue;
            if (x > 0 && y > 0)
                cnt_a[get_pt_kind (x, y)]++;
            if (x > 0 && y < 0)
                cnt_b[get_pt_kind (x, y)]++;
            if (x < 0 && y < 0)
                cnt_c[get_pt_kind (x, y)]++;
            if (x < 0 && y > 0)
                cnt_d[get_pt_kind (x, y)]++;
        }

        total1 = odd1 = total2 = odd2 = 0;
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                for (k = 0; k < 4; k++) {
                    printf ("%d,%d,%d => %d\n", i, j, k, oddity[i][j][k] * cnt_a[i] * cnt_b[j] * cnt_c[k]);
                    printf ("%d,%d,%d => %d\n", i, j, k, oddity[i][j][k] * cnt_a[i] * cnt_d[j] * cnt_c[k]);
                    total1 += cnt_a[i] * cnt_b[j] * cnt_c[k];
                    odd1 += oddity[i][j][k] * cnt_a[i] * cnt_b[j] * cnt_c[k];
                    total2 += cnt_a[i] * cnt_d[j] * cnt_c[k];
                    odd2 += oddity[i][j][k] * cnt_a[i] * cnt_d[j] * cnt_c[k];
                }

        printf ("odd1 = %d, total1 = %d, odd2 = %d, total2 = %d\n", odd1, total1, odd2, total2);
        res = odd1 * odd2 + (total1 - odd1) * (total2 - odd2);
        printf ("res = %d\n", res);
    }

    return 0;
}
