#include <stdio.h>
#include <stdlib.h>

/*
 * There are 4 kinds of points:
 * 0 - even x, even y
 * 1 - even x, odd y
 * 2 - odd x, even y
 * 3 - odd x, odd y
 */

unsigned char oddity[4][4][4] = {
    {
        { 0,0,0,0 },
        { 0,0,1,1 },
        { 0,1,0,1 },
        { 0,1,1,0 },
    },
    {
        { 0,0,1,1 },
        { 0,0,0,0 },
        { 1,0,0,1 },
        { 1,0,1,0 },
    },
    {
        { 0,1,0,1 },
        { 1,0,0,1 },
        { 0,0,0,0 },
        { 1,1,0,0 },
    },
    {
        { 0,1,1,0 },
        { 1,0,1,0 },
        { 1,1,0,0 },
        { 0,0,0,0 },
    },
};


unsigned int cnt_b[4], cnt_d[4];
unsigned char pts_a[30000], pts_c[30000];
int pts_cnt_a, pts_cnt_c;


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
    int total1, odd1, total2, odd2;

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
                total1 = cnt_b[0] + cnt_b[1] + cnt_b[2] + cnt_b[3];
                total2 = cnt_d[0] + cnt_d[1] + cnt_d[2] + cnt_d[3];
                odd2 = odd1 = 0;
                if (oddity[pts_a[i]][0][pts_c[j]]) {
                    odd1 += cnt_b[0];
                    odd2 += cnt_d[0];
                }
                if (oddity[pts_a[i]][1][pts_c[j]]) {
                    odd1 += cnt_b[1];
                    odd2 += cnt_d[1];
                }
                if (oddity[pts_a[i]][2][pts_c[j]]) {
                    odd1 += cnt_b[2];
                    odd2 += cnt_d[2];
                }
                if (oddity[pts_a[i]][3][pts_c[j]]) {
                    odd1 += cnt_b[3];
                    odd2 += cnt_d[3];
                }

                res += odd1 * odd2 + (total1 - odd1) * (total2 - odd2);
            }
            
        printf ("%d\n", res);
    }

    return 0;
}
