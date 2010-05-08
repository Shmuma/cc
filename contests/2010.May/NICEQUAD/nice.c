#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/* fast integers IO */
static char buf[65536];
static int buf_pos = 0;
static int buf_size = 0;


inline int check_buf_data ()
{
    if (buf_pos == buf_size) {
        if (buf_pos == sizeof (buf))
            buf_size = buf_pos = 0;
        buf_size += read (0, buf+buf_pos, sizeof (buf) - buf_pos);
    }

    if (buf_pos == buf_size)
        return 1;
    else
        return 0;
}


int get_int ()
{
    int res, neg = 0;
    char c;

    while (1) {
        if (check_buf_data ())
            return 0;
        c = buf[buf_pos++];
        if (isspace (c))
            continue;
        else
            break;
    }

    res = 0;

    if (c == '-')
        neg = 1;

    if (isdigit (c))
        res = c-'0';

    while (1) {
        if (check_buf_data ())
            return neg ? -res : res;
        c = buf[buf_pos++];
        if (isspace (c))
            return neg ? -res : res;
        if (isdigit (c)) {
            res *= 10;
            res += c-'0';
        }
    }

    return neg ? -res : res;
}



/* we read points data into buffer */
int a[30000][2], b[30000][2], c[30000][2], d[30000][2];
int a_size, b_size, c_size, d_size;

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
    int res, rev;
    int total1, odd1, total2, odd2;

    t = get_int ();
    
    while (t--) {
        n = get_int ();

        for (i = 0; i < 4; i++)
            cnt_b[i] = cnt_d[i] = 0;
        
        pts_cnt_a = pts_cnt_c = 0;
        a_size = b_size = c_size = d_size = 0;

        for (i = 0; i < n; i++) {
            x = get_int ();
            y = get_int ();
            if (x == 0 || y == 0)
                continue;
            if (x > 0 && y > 0) {
                a[a_size][0] = x;
                a[a_size][1] = y;
                a_size++;
            }
            if (x > 0 && y < 0) {
                b[b_size][0] = x;
                b[b_size][1] = y;
                b_size++;
            }
            if (x < 0 && y < 0) {
                c[c_size][0] = x;
                c[c_size][1] = y;
                c_size++;
            }
            if (x < 0 && y > 0) {
                d[d_size][0] = x;
                d[d_size][1] = y;
                d_size++;
            }
        }

        rev = 0;
        if (a_size * c_size > b_size * d_size)
            rev = 1;

        for (i = 0; i < a_size; i++)
            if (!rev)
                pts_a[pts_cnt_a++] = get_pt_kind (a[i][0], a[i][1]);
            else
                cnt_b[get_pt_kind (a[i][0], a[i][1])]++;
        for (i = 0; i < b_size; i++)
            if (!rev)
                cnt_b[get_pt_kind (b[i][0], b[i][1])]++;
            else
                pts_c[pts_cnt_c++] = get_pt_kind (b[i][0], b[i][1]);
        for (i = 0; i < c_size; i++)
            if (!rev)
                pts_c[pts_cnt_c++] = get_pt_kind (c[i][0], c[i][1]);
            else
                cnt_d[get_pt_kind (c[i][0], c[i][1])]++;
        for (i = 0; i < d_size; i++)
            if (!rev)
                cnt_d[get_pt_kind (d[i][0], d[i][1])]++;
            else
                pts_a[pts_cnt_a++] = get_pt_kind (d[i][0], d[i][1]);

        res = 0;

        total1 = cnt_b[0] + cnt_b[1] + cnt_b[2] + cnt_b[3];
        total2 = cnt_d[0] + cnt_d[1] + cnt_d[2] + cnt_d[3];

        for (i = 0; i < pts_cnt_a; i++)
            for (j = 0; j < pts_cnt_c; j++) {
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
