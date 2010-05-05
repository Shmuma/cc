#include <stdio.h>
#include <stdlib.h>

#define PTS_COUNT 30000

int pa[PTS_COUNT][2], pb[PTS_COUNT][2], pc[PTS_COUNT][2], pd[PTS_COUNT][2];
int pa_cnt, pb_cnt, pc_cnt, pd_cnt;


int is_int_area (int *p1, int* p2, int *p3)
{
    int n;
    int x1, y1, x2, y2;

    x1 = p1[0]-p2[0];
    x2 = p1[0]-p3[0];
    y1 = p1[1]-p2[1];
    y2 = p1[1]-p3[1];

    n = x1*y2 - x2*y1;
    if (n < 0)
        n = -n;
    return n % 2 ? 0 : 1;
}


int is_int_area_abc (int a, int b, int c)
{
    return is_int_area (pa[a], pb[b], pc[c]);
}


int is_int_area_acd (int a, int c, int d)
{
    return is_int_area (pa[a], pc[c], pd[d]);
}



int main(int argc, char *argv[])
{
    int t, n, i, x, y;
    int ia, ic;
    int b_int_cnt, b_nint_cnt;
    int d_int_cnt, d_nint_cnt;
    int res;

    scanf ("%d", &t);
    
    while (t--) {
        scanf ("%d", &n);
        pa_cnt = pb_cnt = pc_cnt = pd_cnt = 0;

        for (i = 0; i < n; i++) {
            scanf ("%d %d", &x, &y);
            if (x == 0 || y == 0)
                continue;
            if (x > 0 && y > 0) {
                pa[pa_cnt][0] = x;
                pa[pa_cnt][1] = y;
                pa_cnt++;
            }
            if (x > 0 && y < 0) {
                pb[pb_cnt][0] = x;
                pb[pb_cnt][1] = y;
                pb_cnt++;
            }
            if (x < 0 && y < 0) {
                pc[pc_cnt][0] = x;
                pc[pc_cnt][1] = y;
                pc_cnt++;
            }
            if (x < 0 && y > 0) {
                pd[pd_cnt][0] = x;
                pd[pd_cnt][1] = y;
                pd_cnt++;
            }
        }

        res = 0;
        for (ia = 0; ia < pa_cnt; ia++) {
            for (ic = 0; ic < pc_cnt; ic++) {
                b_int_cnt = b_nint_cnt = d_int_cnt = d_nint_cnt = 0;

                for (i = 0; i < pb_cnt; i++)
                    if (is_int_area_abc (ia, i, ic))
                        b_int_cnt++;
                    else
                        b_nint_cnt++;
                for (i = 0; i < pd_cnt; i++)
                    if (is_int_area_acd (ia, ic, i))
                        d_int_cnt++;
                    else
                        d_nint_cnt++;

                printf ("%d,%d  %d,%d\n", b_int_cnt, b_nint_cnt, d_int_cnt, d_nint_cnt);

                res += b_int_cnt*d_int_cnt + b_nint_cnt*d_nint_cnt;
            }
        }

        printf ("%d\n", res);
    }

    return 0;
}
