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
unsigned int cnt_b[4], cnt_d[4];
unsigned char pts_a[30000], pts_c[30000];
int pts_cnt_a, pts_cnt_c;


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


inline int get_pt_kind (int x, int y)
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
    for (i = 0; i < 4; i++) {
        printf ("{\n");
        for (j = 0; j < 4; j++) {
            printf ("{ ");
            for (k = 0; k < 4; k++) {
                get_pt_by_kind (i, &xa, &ya);
                get_pt_by_kind (j, &xb, &yb);
                get_pt_by_kind (k, &xc, &yc);
        
                oddity[i][j][k] = is_area_odd (xa, ya, xb, yb, xc, yc);
                printf ("%d", oddity[i][j][k]);
                if (k != 3)
                    putchar (',');
            }
            printf (" },\n");
        }
        printf ("},\n");
    }

    return 0;

    scanf ("%d", &t);
    
    while (t--) {
        scanf ("%d", &n);

        for (i = 0; i < 4; i++)
            cnt_b[i] = cnt_d[i] = 0;
        
        pts_cnt_a = pts_cnt_c = 0;

        for (i = 0; i < n; i++) {
            scanf ("%d %d", &x, &y);
            if (x == 0 || y == 0)
                continue;
            if (x > 0 && y > 0)
                pts_a[pts_cnt_a++] = get_pt_kind (x, y);
            if (x > 0 && y < 0)
                cnt_b[get_pt_kind (x, y)]++;
            if (x < 0 && y < 0)
                pts_c[pts_cnt_c++] = get_pt_kind (x, y);
            if (x < 0 && y > 0)
                cnt_d[get_pt_kind (x, y)]++;
        }

        res = 0;

        for (i = 0; i < pts_cnt_a; i++)
            for (j = 0; j < pts_cnt_c; j++) {
                total1 = odd1 = 0;
                total2 = odd2 = 0;
                for (k = 0; k < 4; k++) {
                    total1 += cnt_b[k];
                    odd1 += cnt_b[k] * oddity[pts_a[i]][k][pts_c[j]];
                    total2 += cnt_d[k];
                    odd2 += cnt_d[k] * oddity[pts_a[i]][k][pts_c[j]];
                }

                res += odd1 * odd2 + (total1 - odd1) * (total2 - odd2);
            }
            
        printf ("%d\n", res);
    }

    return 0;
}
